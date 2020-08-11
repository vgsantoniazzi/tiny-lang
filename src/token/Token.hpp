/**
 * @file src/token/Token.hpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Implements token management.
 *
 * @details Get and set Token data, type, line, column, filename and etc.
 */
#ifndef _TOKEN_
#define _TOKEN_

#include <string>

class Token {
public:
  /**
  * @brief Contructor of Token.
  *
  * Token is a pair consisting of a token name and an optional token value.
  * In this language, tokens also have type, filename, separators, and column.
  *
  * @param value The token itself.
  * @param type The type. Most used types can be found on YML token files.
  */
  Token(std::string value = "", std::string type = "UNKNOWN");

  /**
  * @brief Getter for Value
  *
  * @return the string value
  */
  std::string GetValue() const;

  /**
  * @brief Setter for Value
  *
  * @param value value to set.
  */
  void SetValue(std::string value);

  /**
  * @brief Getter for Filename
  *
  * @return the string filename
  */
  std::string GetFilename() const;

  /**
  * @brief Setter for Filename
  *
  * @param file_name value to set.
  */
  void SetFilename(std::string file_name);

  /**
  * @brief Getter for Line
  *
  * @return the integer line
  */
  int GetLine() const;

  /**
  * @brief Setter for Line
  *
  * @param line value to set.
  */
  void SetLine(int line);

  /**
  * @brief Getter for Column
  *
  * @return the integer column
  */
  int GetColumn() const;

  /**
  * @brief Setter for Column
  *
  * @param column value to set.
  */
  void SetColumn(int column);

  /**
  * @brief Getter for Type
  *
  * @return the string type
  */
  std::string GetType() const;

  /**
  * @brief Setter for Type
  *
  * @param type value to set.
  */
  void SetType(std::string type);

  /**
  * @brief Check if Token match with found
  *
  * This is probably the most used function in the implementation
  * of the language.
  *
  * @param type the type value to check
  * @return boolean if type matches or not.
  */
  bool Match(std::string type) const;

private:
  /**
  * @brief the string value to store
  */
  std::string value;

  /**
  * @brief the string type to store
  */
  std::string type;

  /**
  * @brief the string file_name to store
  */
  std::string file_name;

  /**
  * @brief the integer line to store
  */
  int line;

  /**
  * @brief the integer column to store
  */
  int column;
};
#endif
