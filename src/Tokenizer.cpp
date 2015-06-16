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
  this->filename = filename;
  line = 1;
  column = -2;
  NextChar();
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
    lexeme += currentChar;
    token.SetType(GetTokenType());
    NextChar();
  }
  token.SetValue(lexeme);
  token.SetLine(line);
  token.SetColumn(column);
  token.SetFilename(filename);
  return token;
}

TOKEN_TYPE Tokenizer::GetTokenType()
{
  switch(currentChar){
    case '+':
      return ADD;
    case '-':
      return SUB;
    case '*':
      return MULT;
    case '/':
      return DIVIDE;
    case '=':
      return ASSIGN;
    case ';':
      return SEMICOLON;
    case '(':
      return OPEN_PARENTHESYS;
    case ')':
      return CLOSE_PARENTHESYS;
  }
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
  remaining = true;
  column++;
  if (file.get(currentChar))
  {
    if(currentChar == '\n')
    {
      NextChar();
      column = 1;
      line++;
    }
    if((int)currentChar - 48 == -16)
      NextChar();
  } else {
    remaining = false;
  }
}

