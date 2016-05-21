#ifndef _READLINE_STATEMENT_
#define _READLINE_STATEMENT_

#include "Statement.h"
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"

class ReadLineStatement : public Statement {
public:
  void Execute() const;
  void Read(Tokenizer &program);

private:
  Token variable;
  Token strongType;
};

#endif
