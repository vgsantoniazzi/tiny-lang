/**
 * @file src/errors/MalformedExpressionError.hpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Error class called in case of any error in @c .tl program.
 */
#ifndef _MALFORMED_EXPRESSION_
#define _MALFORMED_EXPRESSION_

#include "../token/Token.hpp"

class MalformedExpressionError {
public:

  /**
  * @brief Log the error using LOG library as ERROR level and stops the execution
  *
  * @param token The token that raise the error.
  * @param file_name The file loaded with tiny format.
  * @param line The line where the program found the error.
  * @warning Once called, it will stop language execution.
  */
  static void Raise(Token &token, std::string file_name, int line);
};

#endif
