#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Variables.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Evaluate.h"
#include "errors/MalformedExpressionError.h"
#include "Statement.h"

using namespace std;

Statement * Statement::GetNext(Tokenizer & program)
{
  Token token = program.Look();
  if(token.GetType() == UNKNOWN)
    MalformedExpressionError::Raise(token);

  Statement * statement;
  if (token.GetType() == IDENTIFIER)
    statement = new AssignStatement();
  else if(token.GetType() == OUTPUT)
   statement = new OutputStatement();
  else
    MalformedExpressionError::Raise(token);
  statement->Read(program);
  return statement;
}

void AssignStatement::Execute() const
{
  Variables::All()->Update(variable.GetValue(), returnValue);
}

void AssignStatement::Read(Tokenizer & program)
{
  variable = program.GetToken();
  Token operation = program.GetToken();

  if(variable.Match(IDENTIFIER) && operation.Match(ASSIGN))
  {
    returnValue = Evaluate::Calculate(program);
    program.Match(SEMICOLON);
  }
  else
    MalformedExpressionError::Raise(operation);
}

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

