#ifndef _IF_STATEMENT_
#define _IF_STATEMENT_

#include <vector>
#include "Statement.h"
#include "../evaluates/Evaluate.h"
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"

class IfStatement : public Statement {
public:
  void Execute() const;
  void Read(Tokenizer &program);

private:
  vector<Statement *> statements;
  bool condition;
  int testValue;
  int equalToValue;
};

#endif
