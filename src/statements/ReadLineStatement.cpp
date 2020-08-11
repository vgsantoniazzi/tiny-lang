/**
 * @file src/statements/ReadLineStatement.cpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Implements ReadLineStatement
 */
#include <iostream>
#include <thread>
#include "../variables/Variables.hpp"
#include "ReadLineStatement.hpp"

/**
* @brief Wait for the user input and update the variable.
*/
void ReadLineStatement::Execute() const {
  std::string enter;
  std::cin >> enter;
  Variables::All()->Update(strong_type.GetType(), variable.GetValue(), enter);
}

/**
* @brief Get the variable to update when reading the line.
*
* @param program The tokenizer to understand next steps and eat some tokens.
*/
void ReadLineStatement::Read(Tokenizer &program) {
  program.Match("READ_LINE");
  program.Match("ASSIGN");
  strong_type = program.MatchStrongType();
  variable = program.GetToken();
  program.Match("SEMICOLON");
}
