#ifndef _TOKEN_
#define _TOKEN_

#include <string>

using namespace std;

enum TOKEN_TYPE {
  OUTPUT,
  UNKNOWN,
  INTEGER,
  IDENTIFIER,
  STRING,
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
  SPAWN,
  READ_LINE,
  INTEGER_TYPE,
  STRING_TYPE,
  INTEGER_PARSER
};

const string TOKEN_TYPE_TEXT[] = {
  "OUTPUT",
  "UNKNOWN",
  "INTEGER",
  "IDENTIFIER",
  "STRING",
  "ASSIGN",
  "ADD",
  "SUB",
  "SEMICOLON",
  "MULT",
  "DIVIDE",
  "OPEN_PARENTHESYS",
  "CLOSE_PARENTHESYS",
  "EQUAL_TO",
  "SPACE",
  "NEW_LINE",
  "IF",
  "END",
  "SPAWN",
  "READ_LINE",
  "INTEGER_TYPE",
  "STRING_TYPE",
  "INTEGER_PARSER"
};

class Token
{
  public:
    Token(string v = "", TOKEN_TYPE t = UNKNOWN);
    static string GetTypeText(TOKEN_TYPE t);
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
    bool MatchStrongType() const;
    bool MatchCast() const;
    string GetTypeText() const;
    TOKEN_TYPE GetType() const;
  private:
    string value;
    string filename;
    int line;
    int column;
    TOKEN_TYPE type;
};
#endif

