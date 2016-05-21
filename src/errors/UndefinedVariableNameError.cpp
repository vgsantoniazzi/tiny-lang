#include <cstdlib>
#include <iostream>
#include "../logs/logging.hpp"
#include "../token/Token.hpp"
#include "UndefinedVariableNameError.hpp"

void UndefinedVariableNameError::Raise(string name) {
  LOG(ERROR) << "Undefined variable name '" << name << "'.";
  exit(1);
}
