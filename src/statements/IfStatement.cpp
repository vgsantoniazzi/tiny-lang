/**
 * @file src/statements/IfStatement.cpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Implements IfStatement.
 */
#include "../evaluates/Evaluate.hpp"
#include "../token/Token.hpp"
#include "IfStatement.hpp"

/**
* @brief Test the values and execute if true.
*
* If reads all the statements until the end and executes in the correct order.
*/
void IfStatement::Execute() const {
  if ((!condition && test_value != 0) ||
      (condition && test_value == equal_to_value)) {
    for (int i = 0; i < statements.size(); i++)
      statements[i]->Execute();
  }
}

/**
* @brief Read the Statement, Evaluate and Wait to execute.
*
* Add to statements vector, the statements to be run.
*
* @param program The tokenizer to understand next steps and eat some tokens.
*/
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
