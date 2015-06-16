#include <iostream>
#include <string>
#include "Token.h"
#include "Tokenizer.h"
#include "VarTable.h"
using namespace std;

int main(int argc, char *argv[])
{

  string filename = argv[1];
  Tokenizer program(filename);
  VarTable variables;

  Token token;
  while(program.Remaining()){
    token = program.GetToken();
    cout << "token: '" << token.GetValue() << "' type: " << token.GetType() << endl;
  }
  return 0;
}

