#include <regex>
#include "Tokenizer.hpp"
#include "../logs/logging.hpp"
#include "../errors/FileNotFoundError.hpp"
#include "../errors/MalformedExpressionError.hpp"

Tokenizer::Tokenizer(const std::string &file_name, const std::string &tokens_file) : file(file_name.c_str()) {
  if (!file)
    FileNotFoundError::Raise(file_name);
  this->file_name = file_name;
  LoadTokens(tokens_file);
  line = 1;
  column = -1;
  remaining_tokens = 3;
  string_into = false;
  NextChar();
  NextToken(token);
  NextToken(next_token);
}

void Tokenizer::LoadTokens(const std::string &file_name) {
  int line = 0;
  std::string lineText;
  std::ifstream tokensFile(file_name);
  if (tokensFile.is_open()) {
    LOG(DEBUG) << "Tokens file opened successfully!";
    while (getline(tokensFile, lineText)) {
      if (lineText.at(0) == '#')
        continue;
      std::string regex = lineText.substr(0, lineText.find(": "));
      std::string varName =
          lineText.substr(lineText.find(": ") + 2, lineText.length() - 1);
      token_table[regex] = varName;
      line++;
    }
  } else {
    FileNotFoundError::Raise(file_name);
  }
}

Token Tokenizer::GetToken() {
  Token retToken = token;
  token = next_token;
  NextToken(next_token);
  if (!string_into && (token.Match("SPACE") || token.Match("NEW_LINE")))
    GetToken();
  LOG(DEBUG) << "Token: " << retToken.GetType() << ": " << retToken.GetValue();
  return retToken;
}

Token Tokenizer::Look() { return token; }

bool Tokenizer::Remaining() { return remaining_tokens != 0; }

void Tokenizer::Match(std::string t) {
  if (t == "STRING")
    string_into = !string_into;
  if (!GetToken().Match(t))
    MalformedExpressionError::Raise(token, __FILE__, __LINE__);
}

Token Tokenizer::MatchStrongType() {
  if (Look().Match("INTEGER_TYPE") || Look().Match("STRING_TYPE"))
    return GetToken();
  MalformedExpressionError::Raise(token, __FILE__, __LINE__);
}

void Tokenizer::MatchIf(std::string t) {
  if (token.Match(t))
    Match(t);
}

void Tokenizer::NextToken(Token &token) {
  std::string lexeme;
  token.SetValue(lexeme);
  token.SetType("UNKNOWN");
  if (IsWord(current_char)) {
    lexeme += GetWord();
    token.SetType(GetTokenType(lexeme));
    if (token.Match("UNKNOWN"))
      token.SetType("IDENTIFIER");
  } else {
    lexeme += GetSpecial();
    token.SetType(GetTokenType(lexeme));
  }
  token.SetValue(lexeme);
  token.SetLine(GetLine());
  token.SetColumn(GetColumn());
  token.SetFilename(file_name);
}

bool Tokenizer::IsWord(char c) {
  return isdigit(c) || isalpha(c) || (int)c < 0;
}

std::string Tokenizer::GetSpecial() {
  std::string special;
  char nextChar;
  while (!IsWord(current_char) && Remaining()) {
    special += current_char;
    nextChar = NextChar();
    if (!MatchTokenWithNext(special, nextChar))
      return special;
  }
  return special;
}

std::string Tokenizer::GetWord() {
  std::string word;
  while (IsWord(current_char)) {
    word += current_char;
    NextChar();
  }
  return word;
}

int Tokenizer::GetLine() {
  if (column == 0 && line > 1)
    return line - 1;
  return line;
}

int Tokenizer::GetColumn() {
  if (column == 0 && line > 1)
    return previous_column - 1;
  return column;
}

bool Tokenizer::MatchTokenWithNext(std::string lexeme, char nextChar) {
  std::string match = lexeme + nextChar;
  if (GetTokenType(match) == "UNKNOWN")
    return false;
  return true;
}

char Tokenizer::NextChar() {
  column++;
  previous_char = current_char;
  if (file.get(current_char)) {
    if ((int)current_char - 48 == -16 && current_char == previous_char) {
      if (!string_into)
        NextChar();
      else
        LOG(WARNING) << "Strings with \\n (new line)";
    }
    if (current_char == '\n') {
      if (!string_into && previous_char == current_char) {
        NextChar();
      }
      previous_column = column;
      column = 0;
      line++;
    }
  } else {
    remaining_tokens--;
  }
  return current_char;
}

std::string Tokenizer::GetTokenType(std::string l) {
  for (auto const &token : token_table) {
    if (regex_match(l, std::regex(token.first))) {
      return token.second;
    }
  }
  return "UNKNOWN";
}
