/**
 * @file src/evaluates/Evaluate.hpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Implements the program evaluation.
 */
#ifndef _EVALUATE_
#define _EVALUATE_

#include "../tokenizer/Tokenizer.hpp"

class Evaluate {
public:
  /**
  * @brief Calculates and return the value of a eval execution.
  *
  * It will execute a eval inside a @c If statement, @c Assign statement and so on.
  *
  * @param program The tokenizer to understand next steps and eat some tokens.
  */
  static int Calculate(Tokenizer &program);

private:
  /**
  * @brief Calculates an Expression. Before check for Term.
  *
  * A Expression is SUB or ADD, in order to decrement or increment any kind of value.
  *
  * @param program The tokenizer to understand next steps and eat some tokens.
  */
  int Expression(Tokenizer &program);

  /**
  * @brief Calculates a Term. Before check for Factor.
  *
  * A Expression is MULT or DIV.
  *
  * @param program The tokenizer to understand next steps and eat some tokens.
  */
  int Term(Tokenizer &program);

  /**
  * @brief Calculates a Factor.
  *
  * If Open Parentesys is found, re-call the Expression function.
  * If Identifier is found, get the variable.
  * Otherwise get the value and return it.
  *
  * @param program The tokenizer to understand next steps and eat some tokens.
  */
  int Factor(Tokenizer &program);
};

#endif
