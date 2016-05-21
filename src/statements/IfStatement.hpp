#ifndef _IF_STATEMENT_
#define _IF_STATEMENT_

#include <vector>
#include "Statement.hpp"
#include "../evaluates/Evaluate.hpp"
#include "../token/Token.hpp"
#include "../tokenizer/Tokenizer.hpp"

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
