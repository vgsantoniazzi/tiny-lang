#include <iostream>
#include <string>
#include "Token.h"
#include "Tokenizer.h"
#include "VarTable.h"
#include "Statement.h"
using namespace std;

int main(int argc, char *argv[])
{
  Tokenizer program(argv[1]);
  VarTable variables;
  Statement *statement = Statement::GetNext(program);
  while(statement != NULL)
  {
    statement->Execute(variables);
    statement = Statement::GetNext(program);
  }
  return 0;
}

