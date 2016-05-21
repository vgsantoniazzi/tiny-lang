#ifndef _SPAWN_STATEMENT_
#define _SPAWN_STATEMENT_

#include "Statement.hpp"
#include "../token/Token.hpp"
#include "../tokenizer/Tokenizer.hpp"

class SpawnStatement : public Statement {
public:
  void Execute() const;
  void Read(Tokenizer &program);

private:
  Statement *statement;
};

#endif
