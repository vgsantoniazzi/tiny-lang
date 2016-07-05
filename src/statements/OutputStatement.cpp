#include <iostream>
#include "OutputStatement.hpp"
#include "../variables/Variables.hpp"
#include "../errors/MalformedExpressionError.hpp"

void OutputStatement::Execute() const {
  if (variable.Match("IDENTIFIER"))
    std::cout << Variables::All()->Find(variable.GetValue()) << std::endl;
  else
    std::cout << string_value;
}

void OutputStatement::Read(Tokenizer &program) {
  program.Match("OUTPUT");
  variable = program.Look();

  if (variable.Match("IDENTIFIER")) {
    program.Match("IDENTIFIER");
    program.Match("SEMICOLON");
  } else if (variable.Match("STRING")) {
    program.Match("STRING");
    while (!program.Look().Match("STRING"))
      string_value = string_value + program.GetToken().GetValue();
    program.Match("STRING");
    program.Match("SEMICOLON");
  } else
    MalformedExpressionError::Raise(variable, __FILE__, __LINE__);
}
