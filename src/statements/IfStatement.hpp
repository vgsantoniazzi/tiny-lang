#ifndef _IF_STATEMENT_
#define _IF_STATEMENT_

#include <vector>
#include "Statement.hpp"
#include "../tokenizer/Tokenizer.hpp"

class IfStatement : public Statement {
public:
  void Execute() const;
  void Read(Tokenizer &program);

private:
  std::vector<Statement *> statements;
  bool condition;
  int test_value;
  int equal_to_value;
};

#endif
