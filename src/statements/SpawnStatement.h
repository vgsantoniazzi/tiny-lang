#ifndef _SPAWN_STATEMENT_
#define _SPAWN_STATEMENT_

#include "Statement.h"
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"

class SpawnStatement : public Statement {
public:
  void Execute() const;
  void Read(Tokenizer &program);

private:
  Statement *statement;
};

#endif
