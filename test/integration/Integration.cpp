#include "../../src/variables/Variables.h"
#include "../../src/tokenizer/Tokenizer.h"
#include "../../src/statements/Statement.h"
#include "gtest/gtest.h"

TEST (Statement, IntegrationFullTest)
{
  Tokenizer program("../test/programs/full.tl");
  EXPECT_EQ (Variables::All()->Find("simple"), 0);
  EXPECT_EQ (Variables::All()->Find("complex"), 0);
  Statement *statement = Statement::GetNext(program);
  statement->Execute();
  EXPECT_EQ (Variables::All()->Find("simple"), 16);
  EXPECT_EQ (Variables::All()->Find("complex"), 0);
  statement = Statement::GetNext(program);
  statement->Execute();
  EXPECT_EQ (Variables::All()->Find("simple"), 16);
  EXPECT_EQ (Variables::All()->Find("complex"), 21);
  statement = Statement::GetNext(program);
  statement->Execute();
  EXPECT_EQ (Variables::All()->Find("simple"), 16);
  EXPECT_EQ (Variables::All()->Find("complex"), 37);
  EXPECT_EQ (Variables::All()->Find("recursive"), 0);
  statement = Statement::GetNext(program);
  statement->Execute();
  EXPECT_EQ (Variables::All()->Find("recursive"), 272);
  statement = Statement::GetNext(program);
  statement->Execute();
  EXPECT_EQ (Variables::All()->Find("x"), 0);
  statement = Statement::GetNext(program);
  statement->Execute();
  EXPECT_EQ (Variables::All()->Find("x"), 0);
  statement = Statement::GetNext(program);
  statement->Execute();
  EXPECT_EQ (Variables::All()->Find("x"), 10);
}
