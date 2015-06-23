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
    virtual void Read(Tokenizer & program) = 0;
};

class AssignStatement : public Statement
{
  public:
    void Execute(VarTable & variables) const;
    void Read(Tokenizer & program);
  private:
    Token variable;
    int returnValue;
};

class OutputStatement : public Statement
{
  public:
    void Execute(VarTable & variables) const;
    void Read(Tokenizer & program);
  private:
    Token variable;
};

#endif
