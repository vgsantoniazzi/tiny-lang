/**
 * @file src/statements/AssignStatement.hpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Implements variables assignment.
 *
 * @details Ability to create variables.
 */
#ifndef _ASSIGN_STATEMENT_
#define _ASSIGN_STATEMENT_

#include "Statement.hpp"
#include "../token/Token.hpp"
#include "../tokenizer/Tokenizer.hpp"

class AssignStatement : public Statement {
public:
  /**
  * @brief Read a AssignStatement.
  *
  * @code
  * > int x = 10; ;
  * @endcode
  *
  * It will read a string or evaluate the program until reach the end of eval.
  *
  * @param program The tokenizer to understand next steps and eat some tokens.
  */
  void Read(Tokenizer &program);

  /**
  * @brief execute AssignStatement.
  *
  * Assign a value to a variable.
  */
  void Execute() const;

private:

  /**
  * @brief the variable name. @c x in the example.
  */
  Token variable;

  /**
  * @brief The type of a variable. String, Integer, etc.
  */
  Token strong_type;

  /**
  * @brief The value to assign to a variable.
  */
  std::string return_value;
};

#endif
