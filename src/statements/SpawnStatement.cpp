#include <iostream>
#include <thread>
#include "../variables/Variables.hpp"
#include "SpawnStatement.hpp"
#include "Statement.hpp"

void ExecuteStatement(Statement *statement) { statement->Execute(); }

void SpawnStatement::Execute() const {
  std::thread t(ExecuteStatement, statement);
  t.join();
}

void SpawnStatement::Read(Tokenizer &program) {
  Token spawn = program.GetToken();
  statement = Statement::GetNext(program);
}
