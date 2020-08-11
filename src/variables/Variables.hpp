/**
 * @file src/variables/Variables.hpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Variables management
 *
 * @details Store variables with types.
 */
#ifndef _VARTABLE_H
#define _VARTABLE_H

#include <map>

class Variables {
public:
  /**
  * @brief Initializer
  */
  Variables();

  /**
  * @brief Updates a variable
  *
  * @param type the type of the variable: string, integer, etc
  * @param variable_name the variable name
  * @param variable_value the value of the variable
  */
  void Update(std::string type, std::string variable_name, std::string variable_value);

  /**
  * @brief Search for a String variable.
  *
  * @warning If variable not found, raises an error and stop the execution.
  * @param variable_name The name of string variable.
  * @return string with the value.
  */
  std::string FindStr(std::string variable_name);

  /**
  * @brief Search for a String variable.
  *
  * @warning If variable not found, raises an error and stop the execution.
  * @param variable_name The name of any variable
  * @return string with the value.
  * @todo return any kind of data, not just string
  */
  std::string Find(std::string variable_name);

  /**
  * @brief Search for a Int variable.
  *
  * @warning If variable not found, raises an error and stop the execution.
  * @param variable_name The name of int variable.
  * @return integer with the value.
  */
  int FindInt(std::string variable_name);

  /**
  * @brief Singleton pattern to store variables.
  */
  static Variables *All();

private:
  /**
  * @brief new definition to store variables
  */
  typedef std::map<std::string, std::pair<std::string, std::string> > var_table;

  /**
  * @brief variables
  */
  var_table vars;

  /**
  * @brief Singleton object
  */
  static Variables *single;
};

#endif
