#include <iostream>
#include <thread>
#include "SpawnStatement.h"
#include "Statement.h"
#include "../variables/Variables.h"
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"
#include "../errors/MalformedExpressionError.h"

void ExecuteStatement(Statement *statement)
{
  statement->Execute();
}

void SpawnStatement::Execute() const
{
  std::thread t(ExecuteStatement, statement);
  t.join();
}

void SpawnStatement::Read(Tokenizer & program)
{
  Token spawn = program.GetToken();
  statement = Statement::GetNext(program);
}

