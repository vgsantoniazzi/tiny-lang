#ifndef _ASSIGN_STATEMENT_
#define _ASSIGN_STATEMENT_

#include "Statement.hpp"
#include <iostream>
#include "../token/Token.hpp"
#include "../tokenizer/Tokenizer.hpp"

using namespace std;

class AssignStatement : public Statement {
public:
  void Execute() const;
  void Read(Tokenizer &program);

private:
  Token variable;
  Token strongType;
  string returnValue;
};

#endif
