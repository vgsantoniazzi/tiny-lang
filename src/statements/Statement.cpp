#include <typeinfo>
#include "AssignStatement.h"
#include "OutputStatement.h"
#include "IfStatement.h"
#include "SpawnStatement.h"
#include "ReadLineStatement.h"
#include "../logs/logging.h"
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"
#include "../errors/MalformedExpressionError.h"

Statement * Statement::GetNext(Tokenizer & program)
{
  Token token = program.Look();
  if(token.GetType() == UNKNOWN)
    MalformedExpressionError::Raise(token, __FILE__, __LINE__);

  Statement * statement;
  if (token.MatchStrongType())
    statement = new AssignStatement();
  else if(token.Match(OUTPUT))
   statement = new OutputStatement();
  else if(token.Match(IF))
    statement = new IfStatement();
  else if(token.Match(SPAWN))
    statement = new SpawnStatement();
  else if(token.Match(READ_LINE))
    statement = new ReadLineStatement();

  statement->Read(program);

  LOG(INFO) << (string)typeid(*statement).name() << " load";
  return statement;
}

