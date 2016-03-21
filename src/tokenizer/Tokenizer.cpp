#include <iostream>
#include <cstdlib>
#include "Tokenizer.h"
#include "../token/Token.h"
#include "../errors/MalformedExpressionError.h"

Tokenizer::Tokenizer(const string & filename) : file(filename.c_str())
{
  if (!file)
  {
    cout << "File not found: " << filename << endl;
    exit(1);
  }
  this->filename = filename;
  line = 1;
  column = -1;
  remaining = 3;
  NextChar();
  NextToken(token);
  NextToken(nextToken);
}

Token Tokenizer::GetToken()
{
  Token retToken = token;
  token = nextToken;
  NextToken(nextToken);
  if(token.Match(SPACE) || token.Match(NEW_LINE))
    GetToken();
  return retToken;
}

Token Tokenizer::Look()
{
  return token;
}

bool Tokenizer::Remaining()
{
  return remaining != 0;
}

void Tokenizer::Match(TOKEN_TYPE t)
{
  if(!GetToken().Match(t))
    MalformedExpressionError::Raise(token);
}

void Tokenizer::MatchIf(TOKEN_TYPE t)
{
  if(token.Match(t))
    Match(t);
}

void Tokenizer::NextToken(Token & token)
{
  string lexeme;
  token.SetValue(lexeme);
  token.SetType(UNKNOWN);

  if(isdigit(currentChar))
  {
    lexeme += GetInteger();
    token.SetType(INTEGER);
  }
    else if(isalpha(currentChar))
  {
    lexeme += GetWord();
    token.SetType(GetTokenType(lexeme));
      if(token.Match(UNKNOWN))
    token.SetType(IDENTIFIER);
  }
    else
  {
    lexeme += GetSpecial();
    token.SetType(GetTokenType(lexeme));
  }
  token.SetValue(lexeme);
  token.SetLine(GetLine());
  token.SetColumn(GetColumn());
  token.SetFilename(filename);
}

string Tokenizer::GetSpecial()
{
  string special;
  char nextChar;
  while(!isdigit(currentChar) && !isalpha(currentChar) && Remaining())
  {
    special += currentChar;
    nextChar = NextChar();
    if(!MatchTokenWithNext(special, nextChar))
      return special;
  }
  return special;
}

string Tokenizer::GetInteger()
{
  string integer;
  while(isdigit(currentChar))
  {
    integer += currentChar;
    NextChar();
  }
  return integer;
}

string Tokenizer::GetWord()
{
  string word;
  while(isalpha(currentChar))
  {
    word += currentChar;
    NextChar();
  }
  return word;
}

int Tokenizer::GetLine()
{
  if(column == 0 && line > 1)
    return line - 1;
  return line;
}

int Tokenizer::GetColumn()
{
  if(column == 0 && line > 1)
    return previousColumn - 1;
  return column;
}

bool Tokenizer::MatchTokenWithNext(string lexeme, char nextChar)
{
 string match = lexeme + nextChar;
  if(GetTokenType(match) == UNKNOWN)
    return false;
  return true;
}

char Tokenizer::NextChar()
{
  column++;
  previousChar = currentChar;
  if (file.get(currentChar))
  {
    if(currentChar == '\n')
    {
      if(previousChar == currentChar)
        NextChar();
      previousColumn = column;
      column = 0;
      line++;
    }
    if((int)currentChar - 48 == -16 && currentChar == previousChar)
      NextChar();
  } else {
    remaining--;
  }
  return currentChar;
}

TOKEN_TYPE Tokenizer::GetTokenType(string lexeme)
{
  if(lexeme == "+")
    return ADD;
  if(lexeme == "-")
    return SUB;
  if(lexeme == "*")
    return MULT;
  if(lexeme == "/")
    return DIVIDE;
  if(lexeme == "=")
    return ASSIGN;
  if(lexeme == ";")
    return SEMICOLON;
  if(lexeme == "(")
    return OPEN_PARENTHESYS;
  if(lexeme == ")")
    return CLOSE_PARENTHESYS;
  if(lexeme == "==")
    return EQUAL_TO;
  if(lexeme == "print")
    return OUTPUT;
  if(lexeme == " ")
    return SPACE;
  if(lexeme == "\n")
    return NEW_LINE;
  if(lexeme == "if")
    return IF;
  if(lexeme == "end")
    return END;
  if(lexeme == "spawn")
    return SPAWN;
  return UNKNOWN;
}

