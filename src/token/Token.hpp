#ifndef _TOKEN_
#define _TOKEN_

#include <string>

using namespace std;

class Token {
public:
  Token(string v = "", string t = "UNKNOWN");
  string GetValue() const;
  void SetValue(string v);
  string GetFilename() const;
  void SetFilename(string f);
  int GetLine() const;
  void SetLine(int l);
  int GetColumn() const;
  void SetColumn(int c);
  string GetType() const;
  void SetType(string t);
  bool Match(string t) const;

private:
  string value;
  string filename;
  int line;
  int column;
  string type;
};
#endif
