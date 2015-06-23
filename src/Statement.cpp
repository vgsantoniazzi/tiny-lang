#include <iostream>
#include <string>
#include <vector>
#include "VarTable.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Statement.h"

using namespace std;

Statement * Statement::GetNext(Tokenizer & program)
{
  Token next = program.LookAhead();
  if(next.GetType() == UNKNOWN)
  {
    return NULL;
  }
  cout << next.GetValue() << endl;
}
