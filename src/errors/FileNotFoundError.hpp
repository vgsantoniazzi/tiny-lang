/**
 * @file src/errors/FileNotFoundError.hpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Error class called in case of file not found.
 */
#ifndef _FILE_NOT_FOUND_
#define _FILE_NOT_FOUND_

class FileNotFoundError {
public:
  /**
  * @brief Log the error using LOG library as ERROR level and stops the execution
  *
  * @param file_name The file name that the language was not able to find.
  * @warning Once called, it will stop language execution.
  */
  static void Raise(std::string file_name);
};

#endif
