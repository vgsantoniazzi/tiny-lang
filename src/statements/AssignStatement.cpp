#include "AssignStatement.hpp"
#include <iostream>
#include "../variables/Variables.hpp"
#include "../token/Token.hpp"
#include "../tokenizer/Tokenizer.hpp"
#include "../evaluates/Evaluate.hpp"
#include "../errors/MalformedExpressionError.hpp"

void AssignStatement::Execute() const {
  Variables::All()->Update(strongType.GetType(), variable.GetValue(),
                           returnValue);
}

void AssignStatement::Read(Tokenizer &program) {
  strongType = program.MatchStrongType();
  variable = program.GetToken();
  Token operation = program.GetToken();

  if (variable.Match(IDENTIFIER) && operation.Match(ASSIGN)) {
    Token define = program.Look();
    if (define.Match(STRING)) {
      program.Match(STRING);
      while (!program.Look().Match(STRING)) {
        returnValue = returnValue + program.GetToken().GetValue();
      }
      program.Match(STRING);
      program.Match(SEMICOLON);
    } else {
      returnValue = std::to_string(Evaluate::Calculate(program));
      program.Match(SEMICOLON);
    }
  } else
    MalformedExpressionError::Raise(operation, __FILE__, __LINE__);
}
