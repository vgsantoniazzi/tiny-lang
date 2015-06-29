#ifndef _ASSIGN_STATEMENT_
#define _ASSIGN_STATEMENT_

#include <string>
#include <vector>
#include "Statement.h"
#include "../variables/Variables.h"
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"

class AssignStatement : public Statement
{
  public:
    void Execute() const;
    void Read(Tokenizer & program);
  private:
    Token variable;
    int returnValue;
};

#endif
