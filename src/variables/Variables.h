#ifndef _VARTABLE_H
#define _VARTABLE_H

#include <string>
#include <map>

using namespace std;

class Variables
{
  public:
    Variables();
    void Update(string varName, int varValue);
    int Find(string varName);
    static Variables* All();
  private:
    map<string, int> vars;
    static Variables *single;
};

#endif

