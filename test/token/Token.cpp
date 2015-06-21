#include "../../src/Token.h"
#include "../../src/Tokenizer.h"
#include "gtest/gtest.h"

TEST (Token, GetAndSetLine) {
    Token t = Token();
    t.SetLine(10);
    ASSERT_EQ (t.GetLine(), 10);
}

TEST (Token, GetAndSetColumn) {
    Token t = Token();
    t.SetColumn(15);
    ASSERT_EQ (t.GetColumn(), 15);
}
TEST (Token, GetAndSetFilename) {
    Token t = Token();
    t.SetFilename("../examples/full.tl");
    ASSERT_EQ (t.GetFilename(), "../examples/full.tl");
}
TEST (Token, GetAndSetValue) {
    Token t = Token();
    t.SetValue("==");
    ASSERT_EQ (t.GetValue(), "==");
}
TEST (Token, GetAndSetType) {
    Token t = Token();
    t.SetType(EQUAL_TO);
    ASSERT_EQ (t.GetType(), EQUAL_TO);
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
