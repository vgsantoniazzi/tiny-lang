/**
 * @file src/statements/SpawnStatement.hpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Implements threads.
 *
 * @details Spawn statement will run inside a thread. It will load only the
 * next statement.
 */
#ifndef _SPAWN_STATEMENT_
#define _SPAWN_STATEMENT_

#include "Statement.hpp"
#include "../token/Token.hpp"
#include "../tokenizer/Tokenizer.hpp"

class SpawnStatement : public Statement {
public:
  /**
  * @brief Read a Spawn Statement.
  *
  * @code
  * > spawn < int x = 10;
  * @endcode
  *
  * @param program The tokenizer to understand next steps and eat some tokens.
  */
  void Read(Tokenizer &program);

  /**
  * @brief execute spawn statement.
  */
  void Execute() const;

private:
  /**
  * @brief the statement to be executed in a new thread.
  */
  Statement *statement;
};

#endif
