#include "../logs/logging.hpp"
#include "FileNotFoundError.hpp"

void FileNotFoundError::Raise(std::string file_name) {
  LOG(ERROR) << "File not found: '" << file_name;
  exit(1);
}
