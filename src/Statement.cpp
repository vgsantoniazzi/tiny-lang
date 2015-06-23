#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "VarTable.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Statement.h"

using namespace std;

Statement * Statement::GetNext(Tokenizer & program)
{
  Token token = program.Look();
  if(token.GetType() == UNKNOWN)
    return NULL;

  Statement * statement;
  if (token.GetType() == IDENTIFIER)
  {
    statement = new AssignStatement();
  }
  else if(token.GetType() == OUTPUT)
  {
   statement = new OutputStatement();
  }
    else
  {
    cout << "Malformed expression" << endl;
    exit(1);
  }
  statement->Read(program);
  return statement;
}

void AssignStatement::Execute(VarTable & variables) const
{
  variables.Update(variable.GetValue(), returnValue);
}

void AssignStatement::Read(Tokenizer & program)
{
  variable = program.GetToken();
  Token operation = program.GetToken();

  if(variable.Match(IDENTIFIER) && operation.Match(ASSIGN))
  {
    returnValue = atoi(program.GetToken().GetValue().c_str());
    program.Match(SEMICOLON);
  }
    else
  {
    cout << "Malformed expression" << endl;
    exit(1);
  }
}

void OutputStatement::Execute(VarTable & variables) const
{
  cout << variables.Find(variable.GetValue()) << endl;
}

void OutputStatement::Read(Tokenizer & program)
{
  Token output = program.GetToken();
  variable = program.GetToken();

  if(output.GetType() == OUTPUT && variable.GetType() == IDENTIFIER)
  {
    program.Match(SEMICOLON);
  }
  else
  {
    cout << "Malformed expression" << endl;
    exit(1);
  }

}

