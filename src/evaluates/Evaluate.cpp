#include "Evaluate.hpp"
#include "../token/Token.hpp"
#include "../variables/Variables.hpp"
#include "../errors/MalformedExpressionError.hpp"

int Evaluate::Calculate(Tokenizer &program) {
  Evaluate evaluate;
  return evaluate.Expression(program);
}

int Evaluate::Expression(Tokenizer &program) {
  int value_integer;
  if (program.Look().Match("ADD") || program.Look().Match("SUB"))
    value_integer = 0;
  else
    value_integer = Term(program);
  while (program.Look().Match("ADD") || program.Look().Match("SUB")) {
    if (program.Look().Match("ADD")) {
      program.Match("ADD");
      value_integer += Term(program);
    } else if (program.Look().Match("SUB")) {
      program.Match("SUB");
      value_integer -= Term(program);
    }
  }
  return value_integer;
}

int Evaluate::Term(Tokenizer &program) {
  int value_integer = Factor(program);
  while (program.Look().Match("MULT") || program.Look().Match("DIVIDE")) {
    if (program.Look().Match("MULT")) {
      program.Match("MULT");
      value_integer *= Term(program);
    } else if (program.Look().Match("DIVIDE")) {
      program.Match("DIVIDE");
      value_integer /= Term(program);
    }
  }
  return value_integer;
}

int Evaluate::Factor(Tokenizer &program) {
  int value_integer;
  if (program.Look().Match("OPEN_PARENTHESYS")) {
    program.Match("OPEN_PARENTHESYS");
    value_integer = Expression(program);
    program.Match("CLOSE_PARENTHESYS");
  } else if (program.Look().Match("IDENTIFIER")) {
    value_integer = Variables::All()->FindInt(program.GetToken().GetValue());
  } else {
    Token token = program.GetToken();
    std::string value_string = token.GetValue();
    if (atoi(value_string.c_str()) > 0 || isdigit(value_string.c_str()[0]))
      value_integer = atoi(value_string.c_str());
    else
      MalformedExpressionError::Raise(token, __FILE__, __LINE__);
  }
  return value_integer;
}
