#ifndef _ASSIGN_STATEMENT_
#define _ASSIGN_STATEMENT_

#include "Statement.hpp"
#include "../token/Token.hpp"
#include "../tokenizer/Tokenizer.hpp"

class AssignStatement : public Statement {
public:
  void Execute() const;
  void Read(Tokenizer &program);

private:
  Token variable;
  Token strong_type;
  std::string return_value;
};

#endif
