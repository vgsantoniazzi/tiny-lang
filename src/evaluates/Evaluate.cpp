/**
 * @file src/evaluates/Evaluate.cpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Implements Evaluate
 */
#include "Evaluate.hpp"
#include "../token/Token.hpp"
#include "../variables/Variables.hpp"
#include "../errors/MalformedExpressionError.hpp"

/**
* @brief Initialize the evaluate, and search for a expression.
*
* @param program The tokenizer to understand next steps and eat some tokens.
*/
int Evaluate::Calculate(Tokenizer &program) {
  Evaluate evaluate;
  return evaluate.Expression(program);
}

/**
* @brief Execute a Expression.
*
* In case of real Expression (+, -) found, initialize a value with zero.
* If a program did not match with a Expression search for Term, and get the value of
* the execution.
*
* The order of execution is Expression < Term < Factor.
*
* @note variables are get in the Factor function.
*
* @param program The tokenizer to understand next steps and eat some tokens.
*/
int Evaluate::Expression(Tokenizer &program) {
  int value_integer;
  if (program.Look().Match("ADD") || program.Look().Match("SUB"))
    value_integer = 0;
  else
    value_integer = Term(program);
  while (program.Look().Match("ADD") || program.Look().Match("SUB")) {
    if (program.Look().Match("ADD")) {
      program.Match("ADD");
      value_integer += Term(program);
    } else if (program.Look().Match("SUB")) {
      program.Match("SUB");
      value_integer -= Term(program);
    }
  }
  return value_integer;
}

/**
* @brief Execute a Term.
*
* Executes a Term, but first look for a factor, because the priority order.
* Terms are, by definition, math Multiplication or Division in math.
*
* @note variables are get in the Factor function.
*
* @param program The tokenizer to understand next steps and eat some tokens.
*/
int Evaluate::Term(Tokenizer &program) {
  int value_integer = Factor(program);
  while (program.Look().Match("MULT") || program.Look().Match("DIVIDE")) {
    if (program.Look().Match("MULT")) {
      program.Match("MULT");
      value_integer *= Term(program);
    } else if (program.Look().Match("DIVIDE")) {
      program.Match("DIVIDE");
      value_integer /= Term(program);
    }
  }
  return value_integer;
}

/**
* @brief Execute a Factor.
*
* The order of execution is:
* 1. Look for parenthesys. If found, Go to @see Expression and evaluate
*    inside the parenthesis.
* 2. If the token is a identifier, return the value.
* 3. Otherwise, return the number.
*
* @param program The tokenizer to understand next steps and eat some tokens.
*/
int Evaluate::Factor(Tokenizer &program) {
  int value_integer;
  if (program.Look().Match("OPEN_PARENTHESYS")) {
    program.Match("OPEN_PARENTHESYS");
    value_integer = Expression(program);
    program.Match("CLOSE_PARENTHESYS");
  } else if (program.Look().Match("IDENTIFIER")) {
    value_integer = Variables::All()->FindInt(program.GetToken().GetValue());
  } else {
    Token token = program.GetToken();
    std::string value_string = token.GetValue();
    if (atoi(value_string.c_str()) > 0 || isdigit(value_string.c_str()[0]))
      value_integer = atoi(value_string.c_str());
    else
      MalformedExpressionError::Raise(token, __FILE__, __LINE__);
  }
  return value_integer;
}
