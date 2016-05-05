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
  int enter;
  cin >> enter;
  Variables::All()->Update(variable.GetValue(), enter);

}

void ReadLineStatement::Read(Tokenizer & program)
{
  Token _readLineToken = program.GetToken();
  Token _assignToken = program.GetToken();
  variable = program.GetToken();
  program.Match(SEMICOLON);
}

