#ifndef _READLINE_STATEMENT_
#define _READLINE_STATEMENT_

#include "Statement.hpp"
#include "../token/Token.hpp"
#include "../tokenizer/Tokenizer.hpp"

class ReadLineStatement : public Statement {
public:
  void Execute() const;
  void Read(Tokenizer &program);

private:
  Token variable;
  Token strong_type;
};

#endif
