#include <string>
#include <cstdlib>
#include <iostream>
#include "../Token.h"
#include "MalformedExpressionError.h"

using namespace std;

void MalformedExpressionError::Raise(Token & token)
{
  cout << "Malformed expression near: '" << token.GetValue() << "' line: " <<
    token.GetLine() << " column: " << token.GetColumn() << " on file:" <<
    token.GetFilename() << endl;
  exit(1);
}
