#include "Token.h"
#include "Tokenizer.h"
#include "Evaluate.h"

int Evaluate::Calculate(Tokenizer & program)
{
  Evaluate ev;
  return ev.Expression(program);
}

int Evaluate::Expression(Tokenizer & program)
{
  int val;
  if(program.Look().GetType() == ADD)
  {
    val = 0;
  }
    else
  {
    val = atoi(program.GetToken().GetValue().c_str());
  }
  return val;
}

int Evaluate::Term(Tokenizer & program)
{
  return 1;
}

int Evaluate::Factor(Tokenizer & program)
{
  return 1;
}

