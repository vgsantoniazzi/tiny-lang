#include <cstdlib>
#include <iostream>
#include "../logs/logging.h"
#include "../token/Token.h"
#include "MalformedExpressionError.h"

void MalformedExpressionError::Raise(Token & token)
{
  LOG(ERROR) << "Malformed expression near: '" << token.GetValue() << "' line: " <<
    token.GetLine() << " column: " << token.GetColumn() << " on file:" <<
    token.GetFilename() << endl;
  exit(1);
}
