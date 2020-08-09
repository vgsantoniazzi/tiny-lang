/**
 * @file src/statements/Statement.hpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Header file for the default interface for the statements.
 *
 * @details This is a interpreter. So it will not compile the code before.
 * The correct order is read a statement and execute if after.
 */
#ifndef _STATEMENT_
#define _STATEMENT_

#include "../tokenizer/Tokenizer.hpp"

class Statement {
public:
  /**
  * @brief Identifies the next statement to be executed.
  *
  * Check the current token to understand which statement will be
  * loaded and executed in sequence.
  *
  * @param program The tokenizer to understand next steps and eat some tokens.
  */
  static Statement *GetNext(Tokenizer &program);

  /**
  * @brief Interface to read a program execution.
  *
  * All statements must implement this funtion in order to load it properly.
  *
  * @param program The tokenizer to understand next steps and eat some tokens.
  */
  virtual void Read(Tokenizer &program) = 0;

  /**
  * @brief Interface to execute a loaded Statement.
  *
  * All statements must implement this funtion in order to execute.
  */
  virtual void Execute() const = 0;
};

#endif
