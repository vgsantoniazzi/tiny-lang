#include <iostream>
#include <string>
#include <vector>
#include "VarTable.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Statement.h"

using namespace std;

Statement * Statement::GetNext(Tokenizer & program)
{
  Token token = program.Look();
  if(token.GetType() == UNKNOWN)
    return NULL;

  Statement * statement;
  if (token.GetType() == IDENTIFIER)
  {
    statement = new AssignStatement();
  }
  else if(token.GetType() == OUTPUT)
  {
   statement = new OutputStatement();
  }
  exit(0);
}


