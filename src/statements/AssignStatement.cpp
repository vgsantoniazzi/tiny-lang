#include "AssignStatement.h"
#include "../variables/Variables.h"
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"
#include "../evaluates/Evaluate.h"
#include "../errors/MalformedExpressionError.h"

void AssignStatement::Execute() const
{
  Variables::All()->Update(variable.GetValue(), returnValue);
}

void AssignStatement::Read(Tokenizer & program)
{
  variable = program.GetToken();
  Token operation = program.GetToken();

  if(variable.Match(IDENTIFIER) && operation.Match(ASSIGN))
  {
    returnValue = Evaluate::Calculate(program);
    program.Match(SEMICOLON);
  }
  else
    MalformedExpressionError::Raise(operation);
}
