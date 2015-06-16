#include <string>
#include <map>
#include "VarTable.h"

using namespace std;

VarTable::VarTable(){}

void VarTable::Update(string varName, int varValue)
{
  vars[varName] = varValue;
}


int VarTable::Find(string varName)
{
  if (vars.find(varName) == vars.end()) {
    vars[varName] = 0;
  }
  return vars[varName];
}

