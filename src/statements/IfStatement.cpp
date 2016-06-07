#include "../evaluates/Evaluate.hpp"
#include "../token/Token.hpp"
#include "IfStatement.hpp"

void IfStatement::Execute() const {
  if ((!condition && test_value != 0) ||
      (condition && test_value == equal_to_value)) {
    for (int i = 0; i < statements.size(); i++)
      statements[i]->Execute();
  }
}

void IfStatement::Read(Tokenizer &program) {
  condition = false;
  program.Match("IF");
  program.MatchIf("OPEN_PARENTHESYS");
  test_value = Evaluate::Calculate(program);
  if (program.Look().Match("EQUAL_TO")) {
    condition = true;
    program.Match("EQUAL_TO");
    equal_to_value = Evaluate::Calculate(program);
  }
  program.MatchIf("CLOSE_PARENTHESYS");
  while (!program.Look().Match("END"))
    statements.push_back(GetNext(program));
  program.Match("END");
}
