#ifndef _ASSIGN_STATEMENT_
#define _ASSIGN_STATEMENT_

#include "Statement.h"
#include <iostream>
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"

using namespace std;

class AssignStatement : public Statement
{
  public:
    void Execute() const;
    void Read(Tokenizer & program);
  private:
    Token variable;
    string returnValue;
};

#endif
