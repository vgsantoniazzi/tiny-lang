#ifndef _VARTABLE_H
#define _VARTABLE_H

#include <string>
#include <map>

using namespace std;


class Variables
{
  public:
    Variables();
    void Update(TOKEN_TYPE type, string varName, string varValue);
    string FindStr(string varName);
    int FindInt(string varName);
    static Variables* All();
  private:
    typedef map<string, pair<TOKEN_TYPE, string>> VarTable;
    VarTable vars;
    static Variables *single;
};



#endif

