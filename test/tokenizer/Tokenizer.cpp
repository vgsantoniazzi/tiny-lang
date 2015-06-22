#include "../../src/Tokenizer.h"
#include "gtest/gtest.h"

TEST (Tokenizer, ValidateAssignmentTokenByToken)
{
  Tokenizer program("../test/programs/assignment.tl");
  Token token = program.GetToken();
  ASSERT_TRUE (program.Remaining());
  ASSERT_EQ (token.GetValue(), "expression");
  ASSERT_EQ (token.GetType(), WORD);
  ASSERT_EQ (token.GetColumn(), 10);
  ASSERT_EQ (token.GetLine(), 1);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "=");
  ASSERT_EQ (token.GetType(), ASSIGN);
  ASSERT_EQ (token.GetColumn(), 12);
  ASSERT_EQ (token.GetLine(), 1);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "(");
  ASSERT_EQ (token.GetType(), OPEN_PARENTHESYS);
  ASSERT_EQ (token.GetColumn(), 13);
  ASSERT_EQ (token.GetLine(), 1);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "3");
  ASSERT_EQ (token.GetType(), INTEGER);
  ASSERT_EQ (token.GetColumn(), 14);
  ASSERT_EQ (token.GetLine(), 1);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "+");
  ASSERT_EQ (token.GetType(), ADD);
  ASSERT_EQ (token.GetColumn(), 15);
  ASSERT_EQ (token.GetLine(), 1);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "2");
  ASSERT_EQ (token.GetType(), INTEGER);
  ASSERT_EQ (token.GetColumn(), 16);
  ASSERT_EQ (token.GetLine(), 1);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), ")");
  ASSERT_EQ (token.GetType(), CLOSE_PARENTHESYS);
  ASSERT_EQ (token.GetColumn(), 17);
  ASSERT_EQ (token.GetLine(), 1);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "*");
  ASSERT_EQ (token.GetType(), MULT);
  ASSERT_EQ (token.GetColumn(), 18);
  ASSERT_EQ (token.GetLine(), 1);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "5");
  ASSERT_EQ (token.GetType(), INTEGER);
  ASSERT_EQ (token.GetColumn(), 19);
  ASSERT_EQ (token.GetLine(), 1);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), ";");
  ASSERT_EQ (token.GetType(), SEMICOLON);
  ASSERT_EQ (token.GetColumn(), 0);
  ASSERT_EQ (token.GetLine(), 2);
  ASSERT_FALSE (program.Remaining());
}

TEST (Tokenizer, ValidateEqualToTokenByToken)
{
  Tokenizer program("../test/programs/equal_to.tl");
  Token token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "if");
  ASSERT_EQ (token.GetType(), WORD);
  ASSERT_EQ (token.GetLine(), 1);
  ASSERT_EQ (token.GetColumn(), 1);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "(");
  ASSERT_EQ (token.GetType(), OPEN_PARENTHESYS);
  ASSERT_EQ (token.GetLine(), 1);
  ASSERT_EQ (token.GetColumn(), 2);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "x");
  ASSERT_EQ (token.GetType(), WORD);
  ASSERT_EQ (token.GetLine(), 1);
  ASSERT_EQ (token.GetColumn(), 3);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "==");
  ASSERT_EQ (token.GetType(), EQUAL_TO);
  ASSERT_EQ (token.GetLine(), 1);
  ASSERT_EQ (token.GetColumn(), 5);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "x");
  ASSERT_EQ (token.GetType(), WORD);
  ASSERT_EQ (token.GetLine(), 1);
  ASSERT_EQ (token.GetColumn(), 6);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), ")");
  ASSERT_EQ (token.GetType(), CLOSE_PARENTHESYS);
  ASSERT_EQ (token.GetLine(), 2);
  ASSERT_EQ (token.GetColumn(), 0);
  ASSERT_FALSE (program.Remaining());
}
