#include "Token.hpp"

Token::Token(string v, string t) {
  value = v;
  type = t;
}

string Token::GetValue() const { return value; }

void Token::SetValue(string v) { value = v; }

string Token::GetFilename() const { return filename; }

void Token::SetFilename(string f) { filename = f; }

int Token::GetLine() const { return line; }

void Token::SetLine(int l) { line = l; }

int Token::GetColumn() const { return column; }

void Token::SetColumn(int c) { column = c; }

string Token::GetType() const { return type; }

void Token::SetType(string t) { type = t; }

bool Token::Match(string t) const { return GetType() == t; }
