#include <iostream>
#include <cstdlib>
#include "Tokenizer.hpp"
#include "../logs/logging.hpp"
#include "../token/Token.hpp"
#include "../errors/FileNotFoundError.hpp"
#include "../errors/MalformedExpressionError.hpp"

Tokenizer::Tokenizer(const string &filename) : file(filename.c_str()) {
  if (!file)
    FileNotFoundError::Raise(filename);
  this->filename = filename;
  line = 1;
  column = -1;
  remaining = 3;
  stringInto = false;
  NextChar();
  NextToken(token);
  NextToken(nextToken);
}

Token Tokenizer::GetToken() {
  Token retToken = token;
  token = nextToken;
  NextToken(nextToken);
  if (!stringInto && (token.Match(SPACE) || token.Match(NEW_LINE)))
    GetToken();
  LOG(DEBUG) << "Token: " << retToken.GetTypeText();
  return retToken;
}

Token Tokenizer::Look() { return token; }

bool Tokenizer::Remaining() { return remaining != 0; }

void Tokenizer::Match(TOKEN_TYPE t) {
  if (t == STRING)
    stringInto = !stringInto;
  if (!GetToken().Match(t))
    MalformedExpressionError::Raise(token, __FILE__, __LINE__);
}

Token Tokenizer::MatchStrongType() {
  if (Look().Match(INTEGER_TYPE) || Look().Match(STRING_TYPE))
    return GetToken();
  MalformedExpressionError::Raise(token, __FILE__, __LINE__);
}

void Tokenizer::MatchIf(TOKEN_TYPE t) {
  if (token.Match(t))
    Match(t);
}

void Tokenizer::NextToken(Token &token) {
  string lexeme;
  token.SetValue(lexeme);
  token.SetType(UNKNOWN);

  if (isdigit(currentChar)) {
    lexeme += GetInteger();
    token.SetType(INTEGER);
  } else if (isalpha(currentChar)) {
    lexeme += GetWord();
    token.SetType(GetTokenType(lexeme));
    if (token.Match(UNKNOWN))
      token.SetType(IDENTIFIER);
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

string Tokenizer::GetInteger() {
  string integer;
  while (isdigit(currentChar)) {
    integer += currentChar;
    NextChar();
  }
  return integer;
}

string Tokenizer::GetWord() {
  string word;
  while (isalpha(currentChar)) {
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
  if (GetTokenType(match) == UNKNOWN)
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

TOKEN_TYPE Tokenizer::GetTokenType(string l) {
  if (l == "+")
    return ADD;
  if (l == "-")
    return SUB;
  if (l == "*")
    return MULT;
  if (l == "/")
    return DIVIDE;
  if (l == "=")
    return ASSIGN;
  if (l == ";")
    return SEMICOLON;
  if (l == "(")
    return OPEN_PARENTHESYS;
  if (l == ")")
    return CLOSE_PARENTHESYS;
  if (l == "==")
    return EQUAL_TO;
  if (l == "print")
    return OUTPUT;
  if (l == " ")
    return SPACE;
  if (l == "\n")
    return NEW_LINE;
  if (l == "if")
    return IF;
  if (l == "end")
    return END;
  if (l == "spawn")
    return SPAWN;
  if (l == "readLine")
    return READ_LINE;
  if (l == "to")
    return ASSIGN;
  if (l == "int")
    return INTEGER_TYPE;
  if (l == "str")
    return STRING_TYPE;
  if (l == "\"")
    return STRING;
  return UNKNOWN;
}
