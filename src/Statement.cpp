#include <iostream>
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
  cout << "Execute AssignStatement" << endl;
}

void AssignStatement::Read(Tokenizer & program)
{
  Token value = program.GetToken();
  Token operation = program.GetToken();

  if(value.GetType() == IDENTIFIER && operation.GetType() == ASSIGN)
  {
  }
    else
  {
    cout << "Malformed expression" << endl;
    exit(1);
  }
}

void OutputStatement::Execute(VarTable & variables) const
{
  cout << "OutputStatement" << endl;
}

void OutputStatement::Read(Tokenizer & program)
{
  Token output = program.GetToken();
  Token variable = program.GetToken();
  Token statementEnd = program.GetToken();

  if(output.GetType() == OUTPUT && variable.GetType() == IDENTIFIER &&
    statementEnd.GetType() == SEMICOLON)
  {
    cout << "Execute OutputStatement" << endl;
  }
  else
  {
    cout << "Malformed expression" << endl;
    exit(1);
  }

}

