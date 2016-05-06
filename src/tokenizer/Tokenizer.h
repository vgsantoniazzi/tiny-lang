#ifndef _TOKENIZER_
#define _TOKENIZER_

#include <fstream>
#include <string>
#include "../token/Token.h"

class Tokenizer
{
  public:
    Tokenizer(const string & filename);
    Token GetToken();
    Token Look();
    bool Remaining();
    void Match(TOKEN_TYPE t);
    void MatchStrongType();
    void MatchCast();
    void MatchIf(TOKEN_TYPE t);
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
    bool MatchTokenWithNext(string lexeme, char nextChar);
    string GetInteger();
    string GetWord();
    string GetSpecial();
    int GetLine();
    int GetColumn();
    char NextChar();
    void NextToken(Token & token);
    TOKEN_TYPE GetTokenType(string lexeme);
};

#endif

