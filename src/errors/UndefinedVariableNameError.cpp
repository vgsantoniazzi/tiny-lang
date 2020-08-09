/**
 * @file src/errors/UndefinedVariableNameError.cpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Implementation of UndefinedVariableNameError
 */
#include "../logs/logging.hpp"
#include "../token/Token.hpp"
#include "UndefinedVariableNameError.hpp"

void UndefinedVariableNameError::Raise(std::string variable_name) {
  LOG(ERROR) << "Undefined variable name '" << variable_name << "'.";
  exit(1);
}
