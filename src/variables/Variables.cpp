/**
 * @file src/variables/Variables.cpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Implements Variables
 */
#include "../logs/logging.hpp"
#include "../token/Token.hpp"
#include "../errors/UndefinedVariableNameError.hpp"
#include "Variables.hpp"

/**
* @brief Singleton object
*/
Variables *Variables::single = NULL;

/**
* @brief Singleton logic
*/
Variables *Variables::All() {
  if (single == NULL) {
    single = new Variables();
  }
  return single;
}

Variables::Variables() {}

/**
* @brief Updates a variable
*
* @param type the type of the variable: string, integer, etc
* @param variable_name the variable name
* @param variable_value the value of the variable
*/
void Variables::Update(std::string variable_type, std::string variable_name,
                       std::string variable_value) {
  LOG(DEBUG) << "Variable update " << variable_type << " " << variable_name
             << ": " << variable_value;
  vars[variable_name] = std::make_pair(variable_type, variable_value);
}

/**
* @brief Search for a String variable.
*
* @warning If variable not found, raises an error and stop the execution.
* @param variable_name The name of any variable
* @return string with the value.
* @todo return any kind of data, not just string
*/
std::string Variables::Find(std::string variable_name) {
  var_table::iterator variable_iterator = vars.find(variable_name);
  if (variable_iterator != vars.end()) {
    std::pair<std::string, std::string> variable = vars[variable_name];
    return variable.second;
  }
  UndefinedVariableNameError::Raise(variable_name);
}

/**
* @brief Search for a String variable.
*
* @warning If variable not found, raises an error and stop the execution.
* @param variable_name The name of string variable.
* @return string with the value.
*/
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

/**
* @brief Search for a Int variable.
*
* @warning If variable not found, raises an error and stop the execution.
* @param variable_name The name of int variable.
* @return integer with the value.
*/
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
