#include <iostream>
#include <thread>
#include "ReadLineStatement.hpp"
#include "Statement.hpp"
#include "../variables/Variables.hpp"
#include "../token/Token.hpp"
#include "../tokenizer/Tokenizer.hpp"
#include "../errors/MalformedExpressionError.hpp"

void ReadLineStatement::Execute() const {
  string enter;
  cin >> enter;
  Variables::All()->Update(strongType.GetType(), variable.GetValue(), enter);
}

void ReadLineStatement::Read(Tokenizer &program) {
  program.Match(READ_LINE);
  program.Match(ASSIGN);
  strongType = program.MatchStrongType();
  variable = program.GetToken();
  program.Match(SEMICOLON);
}
