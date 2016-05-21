#include <cstdlib>
#include <iostream>
#include "../logs/logging.hpp"
#include "../token/Token.hpp"
#include "FileNotFoundError.hpp"

void FileNotFoundError::Raise(string filename) {
  LOG(ERROR) << "File not found: '" << filename;
  exit(1);
}
