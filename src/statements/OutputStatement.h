#ifndef _OUTPUT_STATEMENT_
#define _OUTPUT_STATEMENT_

#include <string>
#include <vector>
#include "Statement.h"
#include "../variables/Variables.h"
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"

class OutputStatement : public Statement
{
  public:
    void Execute() const;
    void Read(Tokenizer & program);
  private:
    Token variable;
};

#endif
