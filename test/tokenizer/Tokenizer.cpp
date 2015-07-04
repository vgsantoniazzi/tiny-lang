#include "../../src/tokenizer/Tokenizer.h"
#include "gtest/gtest.h"

TEST (Tokenizer, ValidateAssignmentTokenByToken)
{
  Tokenizer program("../test/programs/assignment.tl");
  Token token = program.GetToken();
  ASSERT_TRUE (program.Remaining());
  ASSERT_EQ (token.GetValue(), "expression");
  ASSERT_EQ (token.GetType(), IDENTIFIER);
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
  ASSERT_EQ (token.GetColumn(), 14);
  ASSERT_EQ (token.GetLine(), 1);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "3");
  ASSERT_EQ (token.GetType(), INTEGER);
  ASSERT_EQ (token.GetColumn(), 15);
  ASSERT_EQ (token.GetLine(), 1);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "+");
  ASSERT_EQ (token.GetType(), ADD);
  ASSERT_EQ (token.GetColumn(), 16);
  ASSERT_EQ (token.GetLine(), 1);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "2");
  ASSERT_EQ (token.GetType(), INTEGER);
  ASSERT_EQ (token.GetColumn(), 17);
  ASSERT_EQ (token.GetLine(), 1);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), ")");
  ASSERT_EQ (token.GetType(), CLOSE_PARENTHESYS);
  ASSERT_EQ (token.GetColumn(), 18);
  ASSERT_EQ (token.GetLine(), 1);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "*");
  ASSERT_EQ (token.GetType(), MULT);
  ASSERT_EQ (token.GetColumn(), 19);
  ASSERT_EQ (token.GetLine(), 1);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "5");
  ASSERT_EQ (token.GetType(), INTEGER);
  ASSERT_EQ (token.GetColumn(), 20);
  ASSERT_EQ (token.GetLine(), 1);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), ";");
  ASSERT_EQ (token.GetType(), SEMICOLON);
  ASSERT_EQ (token.GetColumn(), 20);
  ASSERT_EQ (token.GetLine(), 1);
  ASSERT_FALSE (program.Remaining());
}

TEST (Tokenizer, ValidateEqualToTokenByToken)
{
  Tokenizer program("../test/programs/equal_to.tl");
  Token token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "if");
  ASSERT_EQ (token.GetType(), IF);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "(");
  ASSERT_EQ (token.GetType(), OPEN_PARENTHESYS);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "x");
  ASSERT_EQ (token.GetType(), IDENTIFIER);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "==");
  ASSERT_EQ (token.GetType(), EQUAL_TO);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "x");
  ASSERT_EQ (token.GetType(), IDENTIFIER);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), ")");
  ASSERT_EQ (token.GetType(), CLOSE_PARENTHESYS);
  ASSERT_FALSE (program.Remaining());
}

TEST (Tokenizer, OutputToTokenByToken)
{
  Tokenizer program("../test/programs/output.tl");
  Token token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "i");
  ASSERT_EQ (token.GetType(), IDENTIFIER);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "=");
  ASSERT_EQ (token.GetType(), ASSIGN);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "2");
  ASSERT_EQ (token.GetType(), INTEGER);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), ";");
  ASSERT_EQ (token.GetType(), SEMICOLON);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "print");
  ASSERT_EQ (token.GetType(), OUTPUT);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), "i");
  ASSERT_EQ (token.GetType(), IDENTIFIER);
  token = program.GetToken();
  ASSERT_EQ (token.GetValue(), ";");
  ASSERT_EQ (token.GetType(), SEMICOLON);
  ASSERT_FALSE (program.Remaining());
}
