#include <iostream>
#include <thread>
#include "../variables/Variables.hpp"
#include "ReadLineStatement.hpp"

void ReadLineStatement::Execute() const {
  std::string enter;
  std::cin >> enter;
  Variables::All()->Update(strong_type.GetType(), variable.GetValue(), enter);
}

void ReadLineStatement::Read(Tokenizer &program) {
  program.Match("READ_LINE");
  program.Match("ASSIGN");
  strong_type = program.MatchStrongType();
  variable = program.GetToken();
  program.Match("SEMICOLON");
}
