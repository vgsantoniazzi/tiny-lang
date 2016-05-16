#include <iostream>
#include "OutputStatement.h"
#include "../variables/Variables.h"
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"
#include "../errors/MalformedExpressionError.h"

void OutputStatement::Execute() const {
  if (variable.Match(IDENTIFIER))
    cout << Variables::All()->Find(variable.GetValue()) << endl;
  else
    cout << stringValue;
}

void OutputStatement::Read(Tokenizer &program) {
  program.Match(OUTPUT);
  variable = program.Look();

  if (variable.Match(IDENTIFIER)) {
    program.Match(IDENTIFIER);
    program.Match(SEMICOLON);
  } else if (variable.Match(STRING)) {
    program.Match(STRING);
    while (!program.Look().Match(STRING))
      stringValue = stringValue + program.GetToken().GetValue();
    program.Match(STRING);
    program.Match(SEMICOLON);
  } else
    MalformedExpressionError::Raise(variable, __FILE__, __LINE__);
}
