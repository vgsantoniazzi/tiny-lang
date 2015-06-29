#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Statement.h"
#include "AssignStatement.h"
#include "OutputStatement.h"
#include "../variables/Variables.h"
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"
#include "../evaluates/Evaluate.h"
#include "../errors/MalformedExpressionError.h"

using namespace std;

Statement * Statement::GetNext(Tokenizer & program)
{
  Token token = program.Look();
  if(token.GetType() == UNKNOWN)
    MalformedExpressionError::Raise(token);

  Statement * statement;
  if (token.GetType() == IDENTIFIER)
    statement = new AssignStatement();
  else if(token.GetType() == OUTPUT)
   statement = new OutputStatement();
  else
    MalformedExpressionError::Raise(token);
  statement->Read(program);
  return statement;
}

