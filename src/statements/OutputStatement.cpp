#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "OutputStatement.h"
#include "../variables/Variables.h"
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"
#include "../evaluates/Evaluate.h"
#include "../errors/MalformedExpressionError.h"

using namespace std;

void OutputStatement::Execute() const
{
  cout << Variables::All()->Find(variable.GetValue()) << endl;
}

void OutputStatement::Read(Tokenizer & program)
{
  Token output = program.GetToken();
  variable = program.GetToken();

  if(output.GetType() == OUTPUT && variable.GetType() == IDENTIFIER)
    program.Match(SEMICOLON);
  else
    MalformedExpressionError::Raise(variable);
}

