#ifndef _TOKENIZER_
#define _TOKENIZER_

#include <fstream>
#include <string>
#include <map>
#include "../token/Token.hpp"

class Tokenizer {
public:
  Tokenizer(const string &filename);
  Token GetToken();
  Token Look();
  Token MatchStrongType();
  bool Remaining();
  void Match(string t);
  void MatchIf(string t);

private:
  ifstream file;
  char previousChar;
  char currentChar;
  int remaining;
  Token token;
  Token nextToken;
  string filename;
  int line;
  int column;
  int previousColumn;
  bool stringInto;
  map <string, string> tokenTable;
  bool MatchTokenWithNext(string lexeme, char nextChar);
  string GetInteger();
  string GetWord();
  string GetSpecial();
  int GetLine();
  int GetColumn();
  char NextChar();
  void NextToken(Token &token);
  void LoadTokens();
  string GetTokenType(string lexeme);
};

#endif
