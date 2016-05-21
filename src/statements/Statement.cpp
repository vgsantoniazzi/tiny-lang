#include <typeinfo>
#include "AssignStatement.hpp"
#include "OutputStatement.hpp"
#include "IfStatement.hpp"
#include "SpawnStatement.hpp"
#include "ReadLineStatement.hpp"
#include "../logs/logging.hpp"
#include "../token/Token.hpp"
#include "../tokenizer/Tokenizer.hpp"
#include "../errors/MalformedExpressionError.hpp"

Statement *Statement::GetNext(Tokenizer &program) {
  Token token = program.Look();
  if (token.GetType() == UNKNOWN)
    MalformedExpressionError::Raise(token, __FILE__, __LINE__);

  Statement *statement;
  if (token.Match(INTEGER_TYPE) || token.Match(STRING_TYPE))
    statement = new AssignStatement();
  else if (token.Match(OUTPUT))
    statement = new OutputStatement();
  else if (token.Match(IF))
    statement = new IfStatement();
  else if (token.Match(SPAWN))
    statement = new SpawnStatement();
  else if (token.Match(READ_LINE))
    statement = new ReadLineStatement();

  statement->Read(program);

  LOG(INFO) << (string) typeid(*statement).name() << " load";
  return statement;
}
