#include <cstdlib>
#include <iostream>
#include "../logs/logging.h"
#include "../token/Token.h"
#include "UndefinedVariableNameError.h"

void UndefinedVariableNameError::Raise(string name)
{
  LOG(ERROR) << "Undefined variable name '" << name << "'.";
  exit(1);
}
