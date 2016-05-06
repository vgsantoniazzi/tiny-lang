#ifndef _VARTABLE_H
#define _VARTABLE_H

#include <string>
#include <map>

using namespace std;

class Variables
{
  public:
    Variables();
    void Update(string varName, string varValue);
    string FindStr(string varName);
    int FindInt(string varName);
    static Variables* All();
  private:
    map<string, string> vars;
    static Variables *single;
};

#endif

