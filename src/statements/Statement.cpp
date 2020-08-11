/**
 * @file src/statements/Statement.cpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Implements the default interface for the Statement.
 */
#include <typeinfo>
#include "../logs/logging.hpp"
#include "../token/Token.hpp"
#include "../errors/MalformedExpressionError.hpp"
#include "AssignStatement.hpp"
#include "OutputStatement.hpp"
#include "IfStatement.hpp"
#include "SpawnStatement.hpp"
#include "ReadLineStatement.hpp"

/**
* @brief Look the token and addresses to the correct statement.
*
* It also read the program with the correct statement, but it not executes it.
*
* @param program The tokenizer to understand next steps and eat some tokens.
*/
Statement *Statement::GetNext(Tokenizer &program) {
  Token token = program.Look();
  if (token.GetType() == "UNKNOWN")
    MalformedExpressionError::Raise(token, __FILE__, __LINE__);

  Statement *statement;
  if (token.Match("INTEGER_TYPE") || token.Match("STRING_TYPE"))
    statement = new AssignStatement();
  else if (token.Match("OUTPUT"))
    statement = new OutputStatement();
  else if (token.Match("IF"))
    statement = new IfStatement();
  else if (token.Match("SPAWN"))
    statement = new SpawnStatement();
  else if (token.Match("READ_LINE"))
    statement = new ReadLineStatement();

  statement->Read(program);

  LOG(INFO) << (std::string) typeid(*statement).name() << " load";
  return statement;
}
