#ifndef _MALFORMED_EXPRESSION_
#define _MALFORMED_EXPRESSION_

#include "../token/Token.hpp"

class MalformedExpressionError {
public:
  static void Raise(Token &token, std::string file_name, int line);
};

#endif
