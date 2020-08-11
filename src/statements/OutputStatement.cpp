/**
 * @file src/statements/OutputStatement.cpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Implements OutputStatement.
 */
#include <iostream>
#include "OutputStatement.hpp"
#include "../variables/Variables.hpp"
#include "../errors/MalformedExpressionError.hpp"

/**
* @brief Send a value to stdout.
*
* The values can be strings or identifiers.
*/
void OutputStatement::Execute() const {
  if (variable.Match("IDENTIFIER"))
    std::cout << Variables::All()->Find(variable.GetValue()) << std::endl;
  else
    std::cout << string_value;
}

/**
* @brief Look the token and addresses to the correct statement.
*
* It also Read the program with the correct statement, but it not executes it.
*
* @param program The tokenizer to understand next steps and eat some tokens.
*/
void OutputStatement::Read(Tokenizer &program) {
  program.Match("OUTPUT");
  variable = program.Look();

  if (variable.Match("IDENTIFIER")) {
    program.Match("IDENTIFIER");
    program.Match("SEMICOLON");
  } else if (variable.Match("STRING")) {
    program.Match("STRING");
    while (!program.Look().Match("STRING"))
      string_value = string_value + program.GetToken().GetValue();
    program.Match("STRING");
    program.Match("SEMICOLON");
  } else
    MalformedExpressionError::Raise(variable, __FILE__, __LINE__);
}
