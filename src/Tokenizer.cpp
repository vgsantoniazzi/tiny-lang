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
    cout << "Input file not found." << endl;
    exit(1);
  }
  NextChar();
  this->filename = filename;
  line = 1;
  column = -2;
}

Token Tokenizer::GetToken()
{
  return ReadToken(token);
}

bool Tokenizer::Remaining()
{
  return remaining;
}

Token Tokenizer::ReadToken(Token & token)
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
  return token;
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
  return UNKNOWN;
}

string Tokenizer::GetSpecial()
{
  string special;
  special += currentChar;
  NextChar();
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

void Tokenizer::NextChar()
{
  column++;
  remaining = true;
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
    remaining = false;
  }
}

