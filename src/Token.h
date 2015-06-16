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
    string GetValue() const;
    void SetValue(string v);
    string GetFilename();
    void SetFilename(string f);
    int GetLine();
    void SetLine(int l);
    int GetColumn();
    void SetColumn(int c);
    void SetType(TOKEN_TYPE t);
    TOKEN_TYPE GetType() const;

  private:
    string value;
    string filename;
    int line;
    int column;
    TOKEN_TYPE type;
};

#endif

