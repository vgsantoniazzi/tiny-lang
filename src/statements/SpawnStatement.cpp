#include <iostream>
#include <thread>
#include "SpawnStatement.h"
#include "Statement.h"
#include "../variables/Variables.h"
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"
#include "../errors/MalformedExpressionError.h"

void SpawnStatement::Execute() const
{
  std::thread(statement, Execute());
}

void SpawnStatement::Read(Tokenizer & program)
{
  Token spawn = program.GetToken();
  statement = Statement::GetNext(program);
}

