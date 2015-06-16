#ifndef _VARTABLE_H
#define _VARTABLE_H

#include <string>
#include <map>
using namespace std;

class VarTable
{
  public:
    VarTable();
    void Update(string varName, int varValue);
    int Find(string varName);
  private:
    map<string, int> vars;
};

#endif

