#include <string>
#include <iostream>
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

void Variables::Update(string varName, string varValue)
{
  vars[varName] = varValue;
}


string Variables::FindStr(string varName)
{
  if (vars.find(varName) != vars.end()) {
    return vars[varName];
  }
  return "";
}

int Variables::FindInt(string varName)
{
  if (vars.find(varName) != vars.end()) {
    string var = vars[varName];
    return std::stoi(var);
  }
  return 0;
}
