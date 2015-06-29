#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "Evaluate.h"
#include "../token/Token.h"
#include "../tokenizer/Tokenizer.h"
#include "../variables/Variables.h"
#include "../errors/MalformedExpressionError.h"

using namespace std;

int Evaluate::Calculate(Tokenizer & program)
{
  Evaluate ev;
  return ev.Expression(program);
}

int Evaluate::Expression(Tokenizer & program)
{
  int val;
  if(program.Look().GetType() == ADD || program.Look().GetType() == SUB)
    val = 0;
  else
    val = Term(program);
  while(program.Look().GetType() == ADD || program.Look().GetType() == SUB)
  {
    if(program.Look().GetType() == ADD)
    {
      program.Match(ADD);
      val += Term(program);
    }
    else if(program.Look().GetType() == SUB)
    {
      program.Match(SUB);
      val -= Term(program);
    }
  }
  return val;
}

int Evaluate::Term(Tokenizer & program)
{
  int val = Factor(program);

  while(program.Look().GetType() == MULT || program.Look().GetType() == DIVIDE)
  {
    if(program.Look().GetType() == MULT)
    {
      program.Match(MULT);
      val *= Term(program);
    }
    else if(program.Look().GetType() == DIVIDE)
    {
      program.Match(DIVIDE);
      val /= Term(program);
    }
  }
  return val;
}

int Evaluate::Factor(Tokenizer & program)
{
  int val;
  if(program.Look().GetType() == OPEN_PARENTHESYS)
  {
    program.Match(OPEN_PARENTHESYS);
    val = Expression(program);
    program.Match(CLOSE_PARENTHESYS);
  }
  else if(program.Look().GetType() == IDENTIFIER)
  {
    val = Variables::All()->Find(program.GetToken().GetValue());
  }
  else
  {
    Token token = program.GetToken();
    string value = token.GetValue();
    if (atoi(value.c_str())>0 || isdigit(value.c_str()[0]))
      val = atoi(value.c_str());
    else
      MalformedExpressionError::Raise(token);
  }
  return val;
}

