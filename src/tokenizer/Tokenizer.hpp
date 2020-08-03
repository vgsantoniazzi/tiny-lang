#ifndef _TOKENIZER_
#define _TOKENIZER_

#include <fstream>
#include <map>
#include "../token/Token.hpp"

class Tokenizer {
public:
  Tokenizer(const std::string &file_name, const std::string &tokens_file);
  Token GetToken();
  Token Look();
  Token MatchStrongType();
  bool Remaining();
  void Match(std::string type);
  void MatchIf(std::string type);

private:
  std::ifstream file;
  char previous_char;
  char current_char;
  int remaining_tokens;
  Token token;
  Token next_token;
  std::string file_name;
  int line;
  int column;
  int previous_column;
  bool string_into;
  std::map <std::string, std::string> token_table;
  bool MatchTokenWithNext(std::string lexeme, char next_char);
  bool IsWord(char c);
  std::string GetInteger();
  std::string GetWord();
  std::string GetSpecial();
  int GetLine();
  int GetColumn();
  char NextChar();
  void NextToken(Token &token);
  void LoadTokens(const std::string &file_name);
  std::string GetTokenType(std::string lexeme);
};

#endif
