#include <iostream>
#include <string>
#include "Token.h"
#include "Tokenizer.h"
#include "Variables.h"
#include "statements/Statement.h"
using namespace std;

int main(int argc, char *argv[])
{
  Tokenizer program(argv[1]);
  Statement *statement;
  while(program.Remaining())
  {
    statement = Statement::GetNext(program);
    statement->Execute();
  }
  return 0;
}

