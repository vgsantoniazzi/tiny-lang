#ifndef _OUTPUT_STATEMENT_
#define _OUTPUT_STATEMENT_

#include "Statement.hpp"
#include "../token/Token.hpp"
#include "../tokenizer/Tokenizer.hpp"

class OutputStatement : public Statement {
public:
  void Execute() const;
  void Read(Tokenizer &program);

private:
  Token variable;
  string stringValue;
};

#endif
