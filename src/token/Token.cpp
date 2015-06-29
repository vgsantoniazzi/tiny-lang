#include <string>
#include "Token.h"

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

string Token::GetFilename() const
{
  return filename;
}

void Token::SetFilename(string f)
{
  filename = f;
}

int Token::GetLine() const
{
  return line;
}

void Token::SetLine(int l)
{
  line = l;
}

int Token::GetColumn() const
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

bool Token::Match(TOKEN_TYPE t) const
{
  return GetType() == t;
}

