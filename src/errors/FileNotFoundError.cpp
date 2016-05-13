#include <cstdlib>
#include <iostream>
#include "../logs/logging.h"
#include "../token/Token.h"
#include "FileNotFoundError.h"

void FileNotFoundError::Raise(string filename)
{
  LOG(ERROR) << "File not found: '" << filename;
  exit(1);
}
