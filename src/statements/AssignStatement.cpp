/**
 * @file src/statements/AssignStatement.cpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Implements AssignStatement.
 */
#include "../variables/Variables.hpp"
#include "../evaluates/Evaluate.hpp"
#include "../errors/MalformedExpressionError.hpp"
#include "AssignStatement.hpp"

/**
* @brief Updates a variable name.
*
* @note By now, it only supports global variables.
*/
void AssignStatement::Execute() const {
  Variables::All()->Update(strong_type.GetType(), variable.GetValue(),
                           return_value);
}

/**
* @brief Loads the variable names and the values to be assigned.
*
* @warning Only string or evaluation if valid for assignment. We do not support
* nullify variables yet.
*
* Check if the program if string and load it, or send to Evaluate to be executed.
*/
void AssignStatement::Read(Tokenizer &program) {
  strong_type = program.MatchStrongType();
  variable = program.GetToken();
  Token operation = program.GetToken();

  if (variable.Match("IDENTIFIER") && operation.Match("ASSIGN")) {
    Token define = program.Look();
    if (define.Match("STRING")) {
      program.Match("STRING");
      while (!program.Look().Match("STRING")) {
        return_value = return_value + program.GetToken().GetValue();
      }
      program.Match("STRING");
      program.Match("SEMICOLON");
    } else {
      return_value = std::to_string(Evaluate::Calculate(program));
      program.Match("SEMICOLON");
    }
  } else
    MalformedExpressionError::Raise(operation, __FILE__, __LINE__);
}
