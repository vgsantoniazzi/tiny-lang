#include <iostream>
#include <thread>
#include "ReadLineStatement.h"
#include "Statement.h"
#include "../variables/Variables.h"
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"
#include "../errors/MalformedExpressionError.h"

void ReadLineStatement::Execute() const
{
  string enter;
  cin >> enter;
  Variables::All()->Update(variable.GetValue(), enter);

}

void ReadLineStatement::Read(Tokenizer & program)
{
  program.Match(READ_LINE);
  program.Match(ASSIGN);
  program.MatchStrongType();
  variable = program.GetToken();
  program.Match(SEMICOLON);
}

