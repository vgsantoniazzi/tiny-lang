#include <string>
#include <iostream>
#include <map>
#include "../logs/logging.h"
#include "../token/Token.h"
#include "../errors/UndefinedVariableNameError.h"
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

void Variables::Update(TOKEN_TYPE type, string name, string value)
{
  LOG(DEBUG) << "Variable update " << type << " " << name << " to " << value;
  vars[name] = make_pair(type, value);
}


string Variables::FindStr(string name)
{
  VarTable::iterator variableIterator = vars.find(name);
  if (variableIterator != vars.end())
  {
    pair<TOKEN_TYPE, string> variable = vars[name];
    if (variable.first != STRING_TYPE)
      LOG(WARNING) << "Trying parse '" << name << "' to string that is not the declared type";
    return variable.second;
  }
  UndefinedVariableNameError::Raise(name);
}

int Variables::FindInt(string name)
{
  VarTable::iterator variableIterator = vars.find(name);
  if (variableIterator != vars.end())
  {
    pair<TOKEN_TYPE, string> variable = vars[name];
    if (variable.first != INTEGER_TYPE)
      LOG(WARNING) << "Trying parse '" << name << "' to integer that is not the declared type";
    return std::stoi(variable.second);
  }
  UndefinedVariableNameError::Raise(name);
}
