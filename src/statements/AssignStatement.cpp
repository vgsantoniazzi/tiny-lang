#include "AssignStatement.h"
#include <iostream>
#include "../variables/Variables.h"
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"
#include "../evaluates/Evaluate.h"
#include "../errors/MalformedExpressionError.h"

void AssignStatement::Execute() const
{
  Variables::All()->Update(strongType.GetType(), variable.GetValue(), returnValue);
}

void AssignStatement::Read(Tokenizer & program)
{
  strongType = program.GetStrongType();
  variable = program.GetToken();
  Token operation = program.GetToken();

  if(variable.Match(IDENTIFIER) && operation.Match(ASSIGN))
  {
    Token define = program.Look();
    if (define.Match(STRING))
    {
      program.Match(STRING);
      while(!program.Look().Match(STRING))
      {
        returnValue = returnValue + program.GetToken().GetValue();
      }
      program.Match(STRING);
      program.Match(SEMICOLON);
    }
    else
    {
      returnValue = std::to_string(Evaluate::Calculate(program));
      program.Match(SEMICOLON);
    }
  }
  else
    MalformedExpressionError::Raise(operation, __FILE__, __LINE__);
}
