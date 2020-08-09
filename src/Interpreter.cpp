/**
 * @file src/Interpreter.cpp
 * @author Victor Antoniazzi <vgsantoniazzi@gmail.com>
 * @brief Interpreter main file
 *
 * @details This file contains the main function call stats the interpreter.
 */
#include "tokenizer/Tokenizer.hpp"
#include "statements/Statement.hpp"

/**
 * @brief The function Initialize the Lexer (Tokenizer), and load & execute each
 * statement in order that they are loaded.
 *
 * Everything is loaded and executed in sequence. The interpreter will raise
 * any kind while executing the expression. It will not search by any
 * kind of error before start execution.
 *
 * @param argc The default argument received by C++ applications
 * @param argv The array containing two files. The first element is
 * the @c file.tl (program) and the second one is the token file @c english.yml
 * @warning Both file references are required. Otherwise will return an error.
 */
int main(int argc, char *argv[]) {
  Tokenizer program(argv[1], argv[2]);
  Statement *statement;
  while (program.Remaining()) {
    statement = Statement::GetNext(program);
    statement->Execute();
  }
  return 0;
}
