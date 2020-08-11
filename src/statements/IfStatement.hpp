/**
 * @file src/statements/IfStatement.hpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Implements if.
 *
 * @details Create a flow control.
 */
#ifndef _IF_STATEMENT_
#define _IF_STATEMENT_

#include <vector>
#include "Statement.hpp"
#include "../tokenizer/Tokenizer.hpp"

class IfStatement : public Statement {
public:
  /**
  * @brief Read a IfStatement.
  *
  * @code
  * > if(x == 10) <
  * @endcode
  * It will read the condition and take decision based on it.
  *
  * @param program The tokenizer to understand next steps and eat some tokens.
  */
  void Read(Tokenizer &program);

  /**
  * @brief execute IfStatement.
  */
  void Execute() const;

private:
  /**
  * @brief All statements in case of true returned.
  *
  * It will read the condition and take decision based on it.
  */
  std::vector<Statement *> statements;

  /**
  * @brief The tested condition.
  *
  * The default value is false.
  */
  bool condition;

  /**
  * @brief Left side of a IfStatement.
  */
  int test_value;

  /**
  * @brief Right side of a IfStatement.
  */
  int equal_to_value;
};

#endif
