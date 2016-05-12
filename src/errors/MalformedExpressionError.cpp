#include <cstdlib>
#include <iostream>
#include "../logs/logging.h"
#include "../token/Token.h"
#include "MalformedExpressionError.h"

void MalformedExpressionError::Raise(Token & token, string file, int line)
{
  LOG(ERROR) << "Malformed expression near: '" << token.GetValue() << "' line: " <<
    token.GetLine() << " column: " << token.GetColumn() << " on file:" <<
    token.GetFilename() << " raised from " << file << ":" << line << endl;
  exit(1);
}
