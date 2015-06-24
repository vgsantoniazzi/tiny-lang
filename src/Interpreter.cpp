#include <iostream>
#include <string>
#include "Token.h"
#include "Tokenizer.h"
#include "Variables.h"
#include "Statement.h"
using namespace std;

int main(int argc, char *argv[])
{
  Tokenizer program(argv[1]);
  Variables variables;
  Statement *statement = Statement::GetNext(program);
  while(statement != NULL)
  {
    statement->Execute();
    statement = Statement::GetNext(program);
  }
  return 0;
}

