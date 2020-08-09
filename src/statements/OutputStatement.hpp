/**
 * @file src/statements/OutputStatement.hpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Header file for OutputStatement
 *
 * @details Send anything to stdout.
 */
#ifndef _OUTPUT_STATEMENT_
#define _OUTPUT_STATEMENT_

#include "Statement.hpp"
#include "../token/Token.hpp"
#include "../tokenizer/Tokenizer.hpp"

class OutputStatement : public Statement {
public:
  /**
  * @brief Read a Output Statement.
  *
  * @code
  * > print < x;
  * @endcode
  * It will read what should be send to stdout.
  *
  * @param program The tokenizer to understand next steps and eat some tokens.
  */
  void Read(Tokenizer &program);

  /**
  * @brief execute Output Statement.
  *
  * Forces the output.
  */
  void Execute() const;

private:
  /**
  * @brief Get what should be sent to stdout.
  *
  * In case of identifier, load it;
  * In case of string, load all next tokens untill match string.
  */
  Token variable;

  /**
  * @brief Store the string to go to output in case of string.
  *
  * If is a variable, this @c string_value will be null;
  */
  std::string string_value;
};
#endif
