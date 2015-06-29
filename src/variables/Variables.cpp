#include <string>
#include <map>
#include "Variables.h"

Variables *Variables::single = NULL;

Variables *Variables::All()
{
  if(single == NULL)
  {
    single = new Variables();
  }
  return single;
}

Variables::Variables(){}

void Variables::Update(string varName, int varValue)
{
  vars[varName] = varValue;
}


int Variables::Find(string varName)
{
  if (vars.find(varName) == vars.end()) {
    vars[varName] = 0;
  }
  return vars[varName];
}

