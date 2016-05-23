#include <iostream>
#include <fstream>
#include <cstdlib>
#include <regex>
#include "Tokenizer.hpp"
#include "../logs/logging.hpp"
#include "../token/Token.hpp"
#include "../errors/FileNotFoundError.hpp"
#include "../errors/MalformedExpressionError.hpp"

Tokenizer::Tokenizer(const string &filename) : file(filename.c_str()) {
  if (!file)
    FileNotFoundError::Raise(filename);
  this->filename = filename;
  LoadTokens();
  line = 1;
  column = -1;
  remaining = 3;
  stringInto = false;
  NextChar();
  NextToken(token);
  NextToken(nextToken);
}

void Tokenizer::LoadTokens() {
  string filename = "tokens.yml";
  int line = 0;
  string lineText;
  ifstream tokensFile(filename);
  if (tokensFile.is_open()) {
    LOG(DEBUG) << "Tokens file opened successfully!";
    while (getline(tokensFile, lineText)) {
      if(lineText.at(0) == '#')
        continue;
      string regex = lineText.substr(0, lineText.find(": "));
      string varName =
          lineText.substr(lineText.find(": ") + 2, lineText.length() - 1);
      tokenTable[regex] = varName;
      line++;
    }
  } else {
    FileNotFoundError::Raise(filename);
  }
}

Token Tokenizer::GetToken() {
  Token retToken = token;
  token = nextToken;
  NextToken(nextToken);
  if (!stringInto && (token.Match("SPACE") || token.Match("NEW_LINE")))
    GetToken();
  LOG(DEBUG) << "Token: " << retToken.GetType() << ": " << retToken.GetValue();
  return retToken;
}

Token Tokenizer::Look() { return token; }

bool Tokenizer::Remaining() { return remaining != 0; }

void Tokenizer::Match(string t) {
  if (t == "STRING")
    stringInto = !stringInto;
  if (!GetToken().Match(t))
    MalformedExpressionError::Raise(token, __FILE__, __LINE__);
}

Token Tokenizer::MatchStrongType() {
  if (Look().Match("INTEGER_TYPE") || Look().Match("STRING_TYPE"))
    return GetToken();
  MalformedExpressionError::Raise(token, __FILE__, __LINE__);
}

void Tokenizer::MatchIf(string t) {
  if (token.Match(t))
    Match(t);
}

void Tokenizer::NextToken(Token &token) {
  string lexeme;
  token.SetValue(lexeme);
  token.SetType("UNKNOWN");
  if (isdigit(currentChar) || isalpha(currentChar)) {
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
  token.SetFilename(filename);
}

string Tokenizer::GetSpecial() {
  string special;
  char nextChar;
  while (!isdigit(currentChar) && !isalpha(currentChar) && Remaining()) {
    special += currentChar;
    nextChar = NextChar();
    if (!MatchTokenWithNext(special, nextChar))
      return special;
  }
  return special;
}

string Tokenizer::GetWord() {
  string word;
  while (isdigit(currentChar) || isalpha(currentChar)) {
    word += currentChar;
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
    return previousColumn - 1;
  return column;
}

bool Tokenizer::MatchTokenWithNext(string lexeme, char nextChar) {
  string match = lexeme + nextChar;
  if (GetTokenType(match) == "UNKNOWN")
    return false;
  return true;
}

char Tokenizer::NextChar() {
  column++;
  previousChar = currentChar;
  if (file.get(currentChar)) {
    if ((int)currentChar - 48 == -16 && currentChar == previousChar) {
      if (!stringInto)
        NextChar();
      else
        LOG(WARNING) << "Strings with \\n (new line)";
    }
    if (currentChar == '\n') {
      if (!stringInto && previousChar == currentChar) {
        NextChar();
      }
      previousColumn = column;
      column = 0;
      line++;
    }
  } else {
    remaining--;
  }
  return currentChar;
}

string Tokenizer::GetTokenType(string l) {
  for (auto const &token : tokenTable) {
    if (regex_match(l, regex(token.first))) {
      return token.second;
    }
  }
  return "UNKNOWN";
}
