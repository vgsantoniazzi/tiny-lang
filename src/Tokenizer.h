#ifndef _TOKENIZER_
#define _TOKENIZER_

#include <fstream>
#include <string>
#include "Token.h"
using namespace std;

class Tokenizer
{
  public:
    Tokenizer(const string & filename);
    Token GetToken();
    Token LookAhead();
    Token Look();
    bool Remaining();
  private:
    ifstream file;
    char currentChar;
    int remaining;
    Token token;
    Token nextToken;
    string filename;
    int line;
    int column;
    bool MatchTokenWithNext(string lexeme, char nextChar);
    string GetInteger();
    string GetWord();
    string GetSpecial();
    char NextChar();
    void NextToken(Token & token);
    TOKEN_TYPE GetTokenType(string lexeme);
};

#endif

