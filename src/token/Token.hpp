#ifndef _TOKEN_
#define _TOKEN_

#include <string>

class Token {
public:
  Token(std::string value = "", std::string type = "UNKNOWN");
  std::string GetValue() const;
  void SetValue(std::string value);
  std::string GetFilename() const;
  void SetFilename(std::string file_name);
  int GetLine() const;
  void SetLine(int line);
  int GetColumn() const;
  void SetColumn(int column);
  std::string GetType() const;
  void SetType(std::string type);
  bool Match(std::string type) const;

private:
  std::string value;
  std::string type;
  std::string file_name;
  int line;
  int column;
};
#endif
