#include "../logs/logging.hpp"
#include "../token/Token.hpp"
#include "UndefinedVariableNameError.hpp"

void UndefinedVariableNameError::Raise(std::string variable_name) {
  LOG(ERROR) << "Undefined variable name '" << variable_name << "'.";
  exit(1);
}
