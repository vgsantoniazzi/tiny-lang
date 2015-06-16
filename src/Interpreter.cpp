#include <iostream>
#include <string>
#include "Token.h"
#include "Tokenizer.h"
#include "VarTable.h"
using namespace std;

int main(int argc, char *argv[])
{
  Tokenizer program(argv[1]);
  VarTable variables;
  Token token;

  while(program.Remaining()){
    token = program.GetToken();
    cout << "token: '" << token.GetValue() << "' type: " << token.GetType() <<
      " column: " << token.GetColumn() << " line: " << token.GetLine() <<
      " file: " << token.GetFilename() << endl;
  }
  return 0;
}

