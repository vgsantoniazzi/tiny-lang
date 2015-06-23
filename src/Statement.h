#ifndef _STATEMENT_
#define _STATEMENT_

#include <string>
#include <vector>
#include "VarTable.h"
#include "Token.h"
#include "Tokenizer.h"

class Statement
{
  public:
    static Statement * GetNext(Tokenizer & program);
    virtual void Execute(VarTable & variables) const = 0;
};

class OutputStatement : public Statement
{
  public:
    void Execute(VarTable & variables) const;
};

class AssignStatement : public Statement
{
  public:
    void Execute(VarTable & variables) const;
};

#endif
