/**
 * @file src/statements/ReadLineStatement.hpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Header file for ReadLineStatement
 *
 * @details Wait for user input, and stores in a variable.
 */
#ifndef _READLINE_STATEMENT_
#define _READLINE_STATEMENT_

#include "Statement.hpp"
#include "../token/Token.hpp"
#include "../tokenizer/Tokenizer.hpp"

class ReadLineStatement : public Statement {
public:

  /**
  * @brief Read a ReadLine Statement.
  *
  * @code
  * > readLine < to int x;
  * @endcode
  * It will store the user input to a variable.
  *
  * @param program The tokenizer to understand next steps and eat some tokens.
  */
  void Read(Tokenizer &program);

  /**
  * @brief execute ReadLine Statement
  *
  * Ask the user input;
  * Store to a variable.
  */
  void Execute() const;

private:
  /**
  * @brief Token (identifier) to store the value;
  */
  Token variable;

  /**
  * @brief Token (identifier) with the strong type (str, int, etc)
  */
  Token strong_type;
};

#endif
