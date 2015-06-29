#include <cstdlib>
#include <iostream>
#include "../token/Token.h"
#include "MalformedExpressionError.h"

void MalformedExpressionError::Raise(Token & token)
{
  cout << "Malformed expression near: '" << token.GetValue() << "' line: " <<
    token.GetLine() << " column: " << token.GetColumn() << " on file:" <<
    token.GetFilename() << endl;
  exit(1);
}
