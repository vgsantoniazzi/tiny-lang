/**
 * @file src/errors/FileNotFoundError.cpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Implements FileNotFoundError
 */
#include "../logs/logging.hpp"
#include "FileNotFoundError.hpp"

void FileNotFoundError::Raise(std::string file_name) {
  LOG(ERROR) << "File not found: '" << file_name;
  exit(1);
}
