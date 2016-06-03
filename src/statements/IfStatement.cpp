#include "IfStatement.hpp"
#include "../evaluates/Evaluate.hpp"
#include "../token/Token.hpp"
#include "../tokenizer/Tokenizer.hpp"

void IfStatement::Execute() const {
  if ((!condition && testValue != 0) ||
      (condition && testValue == equalToValue)) {
    for (int i = 0; i < statements.size(); i++)
      statements[i]->Execute();
  }
}

void IfStatement::Read(Tokenizer &program) {
  condition = false;
  program.Match("IF");
  program.MatchIf("OPEN_PARENTHESYS");
  testValue = Evaluate::Calculate(program);
  if (program.Look().Match("EQUAL_TO")) {
    condition = true;
    program.Match("EQUAL_TO");
    equalToValue = Evaluate::Calculate(program);
  }
  program.MatchIf("CLOSE_PARENTHESYS");
  while (!program.Look().Match("END"))
    statements.push_back(GetNext(program));
  program.Match("END");
}
