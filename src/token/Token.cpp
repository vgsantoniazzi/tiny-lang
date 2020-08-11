/**
 * @file src/token/Token.cpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Implements Token
 */
#include "Token.hpp"

Token::Token(std::string value, std::string type) {
  this->value = value;
  this->type = type;
}

std::string Token::GetValue() const { return value; }

void Token::SetValue(std::string value) { this->value = value; }

std::string Token::GetFilename() const { return file_name; }

void Token::SetFilename(std::string file_name) { this->file_name = file_name; }

int Token::GetLine() const { return line; }

void Token::SetLine(int line) { this->line = line; }

int Token::GetColumn() const { return column; }

void Token::SetColumn(int column) { this->column = column; }

std::string Token::GetType() const { return type; }

void Token::SetType(std::string type) { this->type = type; }

bool Token::Match(std::string t) const { return GetType() == t; }
