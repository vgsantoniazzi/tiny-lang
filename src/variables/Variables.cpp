#include "../logs/logging.hpp"
#include "../token/Token.hpp"
#include "../errors/UndefinedVariableNameError.hpp"
#include "Variables.hpp"

Variables *Variables::single = NULL;

Variables *Variables::All() {
  if (single == NULL) {
    single = new Variables();
  }
  return single;
}

Variables::Variables() {}

void Variables::Update(std::string variable_type, std::string variable_name,
                       std::string variable_value) {
  LOG(DEBUG) << "Variable update " << variable_type << " " << variable_name
             << ": " << variable_value;
  vars[variable_name] = std::make_pair(variable_type, variable_value);
}

std::string Variables::Find(std::string variable_name) {
  var_table::iterator variable_iterator = vars.find(variable_name);
  if (variable_iterator != vars.end()) {
    std::pair<std::string, std::string> variable = vars[variable_name];
    return variable.second;
  }
  UndefinedVariableNameError::Raise(variable_name);
}

std::string Variables::FindStr(std::string variable_name) {
  var_table::iterator variable_iterator = vars.find(variable_name);
  if (variable_iterator != vars.end()) {
    std::pair<std::string, std::string> variable = vars[variable_name];
    if (variable.first != "STRING_TYPE")
      LOG(WARNING) << "Trying parse '" << variable_name
                   << "' to std::string that is not the declared type";
    return variable.second;
  }
  UndefinedVariableNameError::Raise(variable_name);
}

int Variables::FindInt(std::string variable_name) {
  var_table::iterator variable_iterator = vars.find(variable_name);
  if (variable_iterator != vars.end()) {
    std::pair<std::string, std::string> variable = vars[variable_name];
    if (variable.first != "INTEGER_TYPE")
      LOG(WARNING) << "Trying parse '" << variable_name
                   << "' to integer that is not the declared type";
    return std::stoi(variable.second);
  }
  UndefinedVariableNameError::Raise(variable_name);
}
