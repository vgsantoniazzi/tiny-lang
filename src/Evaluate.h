#ifndef _EVALUATE_
#define _EVALUATE_

#include "Token.h"
#include "Tokenizer.h"

class Evaluate
{
  public:
    static int Calculate(Tokenizer & program);
  private:
    int Expression(Tokenizer & program);
    int Term(Tokenizer & program);
    int Factor(Tokenizer & program);
};

#endif
