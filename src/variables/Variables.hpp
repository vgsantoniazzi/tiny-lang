#ifndef _VARTABLE_H
#define _VARTABLE_H

#include <map>

class Variables {
public:
  Variables();
  void Update(std::string type, std::string variable_name, std::string variable_value);
  std::string FindStr(std::string variable_name);
  std::string Find(std::string variable_name);
  int FindInt(std::string variable_name);
  static Variables *All();

private:
  typedef std::map<std::string, std::pair<std::string, std::string> > var_table;
  var_table vars;
  static Variables *single;
};

#endif
