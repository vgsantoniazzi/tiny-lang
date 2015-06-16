#ifndef _TOKEN_
#define _TOKEN_

#include <string>
using namespace std;

enum TOKEN_TYPE {INTEGER, WORD, ASSIGN, ADD, SUB, SEMICOLON,
  MULT, DIVIDE, OPEN_PARENTHESYS, CLOSE_PARENTHESYS, UNKNOWN};

class Token
{
  public:
    Token(string v = "", TOKEN_TYPE t = UNKNOWN);
    TOKEN_TYPE GetType() const;
    string GetValue() const;
    void SetType(TOKEN_TYPE t);
    void SetValue(string v);

  private:
    string value;
    TOKEN_TYPE type;
};

#endif
