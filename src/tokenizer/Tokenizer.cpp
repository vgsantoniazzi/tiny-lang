/**
 * @file src/tokenizer/Tokenizer.cpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Implements Tokenizer
 */
#include <regex>
#include "Tokenizer.hpp"
#include "../logs/logging.hpp"
#include "../errors/FileNotFoundError.hpp"
#include "../errors/MalformedExpressionError.hpp"

/**
* @brief Initialize the program.
*
* Load the tokens @c .yml file.
* Intiitalize line, column and remaining_tokens.
* Loads the token and the next token, in order to always have tokens to check
* the current statement.
*
* @param file_name The @c .tl file to read.
* @param tokens_file The @c .yml file containing the tokens to parse.
*/
Tokenizer::Tokenizer(const std::string &file_name, const std::string &tokens_file) : file(file_name.c_str()) {
  if (!file)
    FileNotFoundError::Raise(file_name);
  this->file_name = file_name;
  LoadTokens(tokens_file);
  line = 1;
  column = -1;
  // Means 3 chars in the end of the file.get(). It does have nothing
  // with the tokens or the program. It's about C++.
  remaining_tokens = 3;
  string_into = false;
  NextChar();
  NextToken(token);
  NextToken(next_token);
}

/**
* @brief Loads the tokens @c .yml file
*
* Stores the result in @c token_table.
*
* @param file_name the path of the file.
*/
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

/**
* @brief Load next token and updat the current one.
*
* Now the same next_token is the token and load a new token for next_token.
*
* @param Token the current token. Next token must be called directly.
*/
Token Tokenizer::GetToken() {
  Token retToken = token;
  token = next_token;
  NextToken(next_token);
  if (!string_into && (token.Match("SPACE") || token.Match("NEW_LINE")))
    GetToken();
  LOG(DEBUG) << "Token: " << retToken.GetType() << ": " << retToken.GetValue();
  return retToken;
}

/**
* @brief Look the token without eating it
*
* @return the current token
*/
Token Tokenizer::Look() { return token; }

/**
* @brief If there are any tokens to read.
*
* @return if there are anything to read.
*/
bool Tokenizer::Remaining() { return remaining_tokens != 0; }

/**
* @brief Matches the current token with the input.
*
* Eat a token and if does not match, stops the execution.
*
* @param t the string to match the type.
*/
void Tokenizer::Match(std::string t) {
  if (t == "STRING")
    string_into = !string_into;
  if (!GetToken().Match(t))
    MalformedExpressionError::Raise(token, __FILE__, __LINE__);
}

/**
* @brief Matches the strong type with next.
*
* Eat a token and if does not match, stops the execution.
*
* @return the token match.
*/
Token Tokenizer::MatchStrongType() {
  if (Look().Match("INTEGER_TYPE") || Look().Match("STRING_TYPE"))
    return GetToken();
  MalformedExpressionError::Raise(token, __FILE__, __LINE__);
}

/**
* @brief Eats a token only if it matches.
*
* Used for optional parenthesys.
*
* @param t to match.
*/
void Tokenizer::MatchIf(std::string t) {
  if (token.Match(t))
    Match(t);
}

/**
* @brief Loads the next token.
*
* Initialize as empty token.
* Checks if current char is a word.
*   If true loads it and the the token type.
*     If token type is unknown, set it as identifier (variable)
*
* Otherwise get special char and forces a match with type (addition, parenthesys, equal_to)
*
* @param token pointer token to update.
*/
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

/**
* @brief Check if current char matches with a word
*
* Cyrilic alphabet, like russian, the integer of a char is negative.
*
* @param c char to test.
*/
bool Tokenizer::IsWord(char c) {
  return isdigit(c) || isalpha(c) || (int)c < 0;
}

/**
* @brief Get the special char
*
* @return string with the lexeme.
*/
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

/**
* @brief Get the a word.
*
* @return string with the lexeme.
*/
std::string Tokenizer::GetWord() {
  std::string word;
  while (IsWord(current_char)) {
    word += current_char;
    NextChar();
  }
  return word;
}

/**
* @brief Get the line
*
* @return the integer of a line.
*/
int Tokenizer::GetLine() {
  if (column == 0 && line > 1)
    return line - 1;
  return line;
}

/**
* @brief Get the column
*
* @return the integer of a column.
*/
int Tokenizer::GetColumn() {
  if (column == 0 && line > 1)
    return previous_column - 1;
  return column;
}

/**
* @brief Check if the lexeme plus a char matches with anything.
*
* @return boolean if it matches.
*/
bool Tokenizer::MatchTokenWithNext(std::string lexeme, char nextChar) {
  std::string match = lexeme + nextChar;
  if (GetTokenType(match) == "UNKNOWN")
    return false;
  return true;
}

/**
* @brief Loads the next char from the file and update the line, column and remaining tokens
*
* @return the next char.
*/
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

/**
* @brief Loads the token type by @c .yml file
*
* @return the string matching.
*/
std::string Tokenizer::GetTokenType(std::string l) {
  for (auto const &token : token_table) {
    if (regex_match(l, std::regex(token.first))) {
      return token.second;
    }
  }
  return "UNKNOWN";
}
