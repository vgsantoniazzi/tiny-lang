#include "Statement.h"
#include "AssignStatement.h"
#include "OutputStatement.h"
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"
#include "../errors/MalformedExpressionError.h"

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

