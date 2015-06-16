#include "Token.h"
#include <string>
using namespace std;

Token::Token(string v, TOKEN_TYPE t)
{
  value = v;
  type = t;
}

string Token::GetValue() const
{
  return value;
}

void Token::SetValue(string v)
{
  value = v;
}

string Token::GetFilename()
{
  return filename;
}

void Token::SetFilename(string f)
{
  filename = f;
}

int Token::GetLine()
{
  return line;
}

void Token::SetLine(int l)
{
  line = l;
}

int Token::GetColumn()
{
  return column;
}

void Token::SetColumn(int c)
{
  column = c;
}

TOKEN_TYPE Token::GetType() const
{
  return type;
}

void Token::SetType(TOKEN_TYPE t)
{
  type = t;
}

