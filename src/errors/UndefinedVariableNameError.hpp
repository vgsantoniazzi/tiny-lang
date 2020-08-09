/**
 * @file src/errors/UndefinedVariableNameError.hpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Error class called in case of any variable not defined.
 */
#ifndef _UNDEFINED_VARIABLE_NAME_
#define _UNDEFINED_VARIABLE_NAME_

class UndefinedVariableNameError {
public:

  /**
  * @brief Log the error using LOG library as ERROR level and stops the execution
  *
  * @param variable_name The name of the variable that raised the error.
  * @warning Once called, it will stop language execution.
  */
  static void Raise(std::string variable_name);
};

#endif
