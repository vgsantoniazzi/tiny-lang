#include <cstdlib>
#include <iostream>
#include "Evaluate.hpp"
#include "../token/Token.hpp"
#include "../tokenizer/Tokenizer.hpp"
#include "../variables/Variables.hpp"
#include "../errors/MalformedExpressionError.hpp"

int Evaluate::Calculate(Tokenizer &program) {
  Evaluate ev;
  return ev.Expression(program);
}

int Evaluate::Expression(Tokenizer &program) {
  int val;
  if (program.Look().Match("ADD") || program.Look().Match("SUB"))
    val = 0;
  else
    val = Term(program);
  while (program.Look().Match("ADD") || program.Look().Match("SUB")) {
    if (program.Look().Match("ADD")) {
      program.Match("ADD");
      val += Term(program);
    } else if (program.Look().Match("SUB")) {
      program.Match("SUB");
      val -= Term(program);
    }
  }
  return val;
}

int Evaluate::Term(Tokenizer &program) {
  int val = Factor(program);

  while (program.Look().Match("MULT") || program.Look().Match("DIVIDE")) {
    if (program.Look().Match("MULT")) {
      program.Match("MULT");
      val *= Term(program);
    } else if (program.Look().Match("DIVIDE")) {
      program.Match("DIVIDE");
      val /= Term(program);
    }
  }
  return val;
}

int Evaluate::Factor(Tokenizer &program) {
  int val;
  if (program.Look().Match("OPEN_PARENTHESYS")) {
    program.Match("OPEN_PARENTHESYS");
    val = Expression(program);
    program.Match("CLOSE_PARENTHESYS");
  } else if (program.Look().Match("IDENTIFIER")) {
    val = Variables::All()->FindInt(program.GetToken().GetValue());
  } else {
    Token token = program.GetToken();
    string value = token.GetValue();
    if (atoi(value.c_str()) > 0 || isdigit(value.c_str()[0]))
      val = atoi(value.c_str());
    else
      MalformedExpressionError::Raise(token, __FILE__, __LINE__);
  }
  return val;
}
