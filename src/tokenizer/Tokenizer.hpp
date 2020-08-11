/**
 * @file src/tokenizer/Tokenizer.hpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Implements the lexis and sematic analysis.
 */
#ifndef _TOKENIZER_
#define _TOKENIZER_

#include <fstream>
#include <map>
#include "../token/Token.hpp"

class Tokenizer {
public:
  /**
  * @brief Initializer the program.
  *
  * @param file_name The @c .tl file to read.
  * @param tokens_file The @c .yml file containing the tokens to parse.
  */
  Tokenizer(const std::string &file_name, const std::string &tokens_file);

  /**
  * @brief return the next token. Eats a token.
  *
  * @return Next token to be analyzed.
  */
  Token GetToken();

  /**
  * @brief return the current token. Do not eat anything.
  *
  * @return The current token to be analyzed
  */
  Token Look();

  /**
  * @brief Forces to match the current token as strong type.
  *
  * @warning In case of not found, stops the execution.
  *
  * @return The current token to be analyzed
  */
  Token MatchStrongType();

  /**
  * @brief Checks if there are any remaining token.
  *
  * Used to check if there are something to run, used in case of cannot get the next char.
  *
  * @return The boolean variable to check if there are any token to run.
  */
  bool Remaining();

  /**
  * @brief Matches the current token with a argument.
  *
  * @warning It also eats a token and load the next one
  *
  * @param type the string to check.
  */
  void Match(std::string type);

  /**
  * @brief Eats the next token only if matches with specified.
  *
  * @note used when parenthesys are optional.
  *
  * @param type the string to check.
  */
  void MatchIf(std::string type);

private:
  /**
  * @brief the @c .tl file, opened to and ready to read.
  */
  std::ifstream file;

  /**
  * @brief the previous char in order to build a token.
  */
  char previous_char;

  /**
  * @brief the current char in order to build a token.
  */
  char current_char;

  /**
  * @brief how many remaining tokens there are until reach the end of the program.
  */
  int remaining_tokens;

  /**
  * @brief the current token.
  */
  Token token;

  /**
  * @brief the next token in order to undestand what came next.
  */
  Token next_token;

  /**
  * @brief the string with filename.
  */
  std::string file_name;

  /**
  * @brief the current line.
  */
  int line;

  /**
  * @brief the current column.
  */
  int column;

  /**
  * @brief the previous column.
  */
  int previous_column;

  /**
  * @brief To check if we are parsing a string.
  *
  * @code
  * " <- this char.
  * @endcode
  */
  bool string_into;

  /**
  * @brief the parsed tokens table.
  *
  * Ability to support multiple idioms.
  */
  std::map <std::string, std::string> token_table;

  /**
  * @brief Check if current lexeme plus next char matches with anything.
  *
  * @return boolean containing if matches or not.
  */
  bool MatchTokenWithNext(std::string lexeme, char next_char);

  /**
  * @brief Check if current char is a word, or is a special char.
  *
  * @return boolean containing if is a word or not
  */
  bool IsWord(char c);

  /**
  * @brief Get next word. Matches chars until reach to the end.
  *
  * @return string with the current word.
  */
  std::string GetWord();

  /**
  * @brief Get a special char. Matches chars until reach to the end.
  *
  * @return string with the current special char, e.g ( ) + - =
  */
  std::string GetSpecial();

  /**
  * @brief Get the current line.
  *
  * @return integer containing the current line.
  */
  int GetLine();

  /**
  * @brief Get the current column.
  *
  * @return integer containing the current column.
  */
  int GetColumn();

  /**
  * @brief Loads the next char from file.
  *
  * @return the next char.
  */
  char NextChar();

  /**
  * @brief Get the next token.
  *
  * @param token the pointer to update.
  */
  void NextToken(Token &token);

  /**
  * @brief Loads the tokens @c .yml file
  *
  * @param file_name the path of the file.
  */
  void LoadTokens(const std::string &file_name);

  /**
  * @brief Updates the token with the correct type.
  *
  * @param lexeme the string to search by.
  */
  std::string GetTokenType(std::string lexeme);
};

#endif
