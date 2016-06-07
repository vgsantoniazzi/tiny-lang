#include "../variables/Variables.hpp"
#include "../evaluates/Evaluate.hpp"
#include "../errors/MalformedExpressionError.hpp"
#include "AssignStatement.hpp"

void AssignStatement::Execute() const {
  Variables::All()->Update(strong_type.GetType(), variable.GetValue(),
                           return_value);
}

void AssignStatement::Read(Tokenizer &program) {
  strong_type = program.MatchStrongType();
  variable = program.GetToken();
  Token operation = program.GetToken();

  if (variable.Match("IDENTIFIER") && operation.Match("ASSIGN")) {
    Token define = program.Look();
    if (define.Match("STRING")) {
      program.Match("STRING");
      while (!program.Look().Match("STRING")) {
        return_value = return_value + program.GetToken().GetValue();
      }
      program.Match("STRING");
      program.Match("SEMICOLON");
    } else {
      return_value = std::to_string(Evaluate::Calculate(program));
      program.Match("SEMICOLON");
    }
  } else
    MalformedExpressionError::Raise(operation, __FILE__, __LINE__);
}
