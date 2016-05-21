#include <cstdlib>
#include <iostream>
#include "../logs/logging.hpp"
#include "../token/Token.hpp"
#include "MalformedExpressionError.hpp"

void MalformedExpressionError::Raise(Token &token, string file, int line) {
  LOG(ERROR) << "Malformed expression near: '" << token.GetValue()
             << "' line: " << token.GetLine()
             << " column: " << token.GetColumn()
             << " on file:" << token.GetFilename() << " raised from " << file
             << ":" << line << endl;
  exit(1);
}
