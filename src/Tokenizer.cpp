#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include "Token.h"
#include "Tokenizer.h"
using namespace std;

Tokenizer::Tokenizer(const string & filename) : file(filename.c_str())
{
  if (!file)
  {
    cout << "File not found: " << filename << endl;
    exit(1);
  }
  this->filename = filename;
  line = 1;
  column = -2;
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
  return retToken;
}

Token Tokenizer::LookAhead()
{
  return nextToken;
}

bool Tokenizer::Remaining()
{
  return remaining != 0;
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
    token.SetType(WORD);
  }
    else
  {
    lexeme += GetSpecial();
    token.SetType(GetTokenType(lexeme));
  }
  token.SetValue(lexeme);
  token.SetLine(line);
  token.SetColumn(column);
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
  if (file.get(currentChar))
  {
    if(currentChar == '\n')
    {
      NextChar();
      column = 0;
      line++;
    }
    if((int)currentChar - 48 == -16)
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
  return UNKNOWN;
}

