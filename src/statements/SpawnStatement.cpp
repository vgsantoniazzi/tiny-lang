#include <iostream>
#include <thread>
#include "SpawnStatement.hpp"
#include "Statement.hpp"
#include "../variables/Variables.hpp"
#include "../token/Token.hpp"
#include "../tokenizer/Tokenizer.hpp"
#include "../errors/MalformedExpressionError.hpp"

void ExecuteStatement(Statement *statement) { statement->Execute(); }

void SpawnStatement::Execute() const {
  std::thread t(ExecuteStatement, statement);
  t.join();
}

void SpawnStatement::Read(Tokenizer &program) {
  Token spawn = program.GetToken();
  statement = Statement::GetNext(program);
}
