/**
 * @file src/errors/MalformedExpressionError.cpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Implementation of MalformedExpressionError
 */
#include "../logs/logging.hpp"
#include "../token/Token.hpp"
#include "MalformedExpressionError.hpp"

void MalformedExpressionError::Raise(Token &token, std::string file_name, int line) {
  LOG(ERROR) << "Malformed expression near: '" << token.GetValue()
             << "' line: " << token.GetLine()
             << " column: " << token.GetColumn()
             << " on file:" << token.GetFilename() << " raised from "
             << file_name << ":" << line;
  exit(1);
}
