#include "Statement.h"
#include "AssignStatement.h"
#include "OutputStatement.h"
#include "IfStatement.h"
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"
#include "../errors/MalformedExpressionError.h"

Statement * Statement::GetNext(Tokenizer & program)
{
  Token token = program.Look();
  if(token.GetType() == UNKNOWN)
    MalformedExpressionError::Raise(token);

  Statement * statement;
  if (token.Match(IDENTIFIER))
    statement = new AssignStatement();
  else if(token.Match(OUTPUT))
   statement = new OutputStatement();
  else if(token.Match(IF))
    statement = new IfStatement();
  else
    MalformedExpressionError::Raise(token);
  statement->Read(program);
  return statement;
}

