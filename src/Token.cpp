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

TOKEN_TYPE Token::GetType() const
{
  return type;
}

void Token::SetType(TOKEN_TYPE t)
{
  type = t;
}
