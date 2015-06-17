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
    bool Remaining();
  private:
    ifstream file;
    char currentChar;
    bool remaining;
    Token token;
    string filename;
    int line;
    int column;
    string GetInteger();
    string GetWord();
    string GetSpecial();
    void NextChar();
    Token ReadToken(Token & token);
    TOKEN_TYPE GetTokenType(string lexeme);
};

#endif

