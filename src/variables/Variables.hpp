#ifndef _VARTABLE_H
#define _VARTABLE_H

#include <string>
#include <map>

using namespace std;

class Variables {
public:
  Variables();
  void Update(string type, string varName, string varValue);
  string FindStr(string varName);
  string Find(string varName);
  int FindInt(string varName);
  static Variables *All();

private:
  typedef map<string, pair<string, string> > VarTable;
  VarTable vars;
  static Variables *single;
};

#endif
