#ifndef _TOKEN_
#define _TOKEN_

#include <string>

using namespace std;

enum TOKEN_TYPE {
  OUTPUT,
  UNKNOWN,
  INTEGER,
  IDENTIFIER,
  ASSIGN,
  ADD,
  SUB,
  SEMICOLON,
  MULT,
  DIVIDE,
  OPEN_PARENTHESYS,
  CLOSE_PARENTHESYS,
  EQUAL_TO,
  SPACE,
  NEW_LINE,
  IF,
  END,
  SPAWN
};

class Token
{
  public:
    Token(string v = "", TOKEN_TYPE t = UNKNOWN);
    string GetValue() const;
    void SetValue(string v);
    string GetFilename() const;
    void SetFilename(string f);
    int GetLine() const;
    void SetLine(int l);
    int GetColumn() const;
    void SetColumn(int c);
    void SetType(TOKEN_TYPE t);
    bool Match(TOKEN_TYPE t) const;
    TOKEN_TYPE GetType() const;
  private:
    string value;
    string filename;
    int line;
    int column;
    TOKEN_TYPE type;
};
#endif

