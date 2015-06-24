#ifndef _MALFORMED_EXPRESSION_
#define _MALFORMED_EXPRESSION_

class MalformedExpressionError
{
  public:
    static void Raise(Token & token);
};

#endif
