#ifndef _STATEMENT_
#define _STATEMENT_

#include "../tokenizer/Tokenizer.h"

class Statement {
public:
  static Statement *GetNext(Tokenizer &program);
  virtual void Execute() const = 0;
  virtual void Read(Tokenizer &program) = 0;
};

#endif
