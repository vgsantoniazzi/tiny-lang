#include "IfStatement.h"
#include "../evaluates/Evaluate.h"
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"

void IfStatement::Execute() const
{
  if(testValue != 0)
  {
    for (int i = 0; i < statements.size(); i++)
    {
      statements[i]->Execute();
    }
  }
}

void IfStatement::Read(Tokenizer & program)
{
  program.Match(IF);
  testValue = Evaluate::Calculate(program);
  while(!program.Look().Match(END))
    statements.push_back(GetNext(program));
  program.Match(END);
}

