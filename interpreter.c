/*
 Author: Victor Antoniazzi <vgsantoniazzi@gmail.com>

 Interpreter for a tiny language. The scope is learn how interpreters work and
 build one. Math expressions and control sctructure (if and else);
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

/*
  Define array and size of variables.
*/
#define MAXVAR 26
int var[MAXVAR];

/*
  Define current token and array with all tokens.
*/
char token;
char *tokens;

/*
  Define counter for all tokens in a file.
*/
size_t column = 0;

void init(char *file_name);
void readFile(char *file_name);
void assignment();
void nextToken();
void match(char c);
void expected(char *message, ...);
char getName();
bool isAddOp(char c);
bool isMulOp(char c);
int factor();
int getNum();
int expression();
int term();

/*
  Initialize interpreter.

  @receive int argc: counter of args received.
  @receive char argv: Array with all arguments received.
*/
int main(int argc, char **argv){
  init(argv[1]);
  printf("%d", expression());
  return 0;
}
/*
  First step to start to interpreting. Read an file and get the first char
*/
void init(char *file_name){
  readFile(file_name);
  nextToken();
}

/*
  Assign an math expression to a one alphabet letter.
*/
void assignment(){
  char name;
  name = getName();
  match('=');
  var[name] = expression();
}

/*
  Read received file_name and put all chars to array of tokens.
*/
void readFile(char *file_name){
  char c;
  FILE *file = fopen(file_name, "r");
  if(file == NULL)
    expected("file not found: %s", file_name);
  tokens = malloc(1000);
  while ((c = fgetc(file)) != EOF){
    if(c > 0)
      tokens[column++] = (char) c;
  }
  fclose(file);
  column = 0;
}

/*
 Read next token from array of them.
*/
void nextToken(){
  token = (char) tokens[column++];
}

/*
  Validate if has an parentesys. Execute them before commom expression.
*/
int factor(){
  int val;
  if(token == '('){
    match('(');
    val = expression();
    match(')');
  } else {
    val = getNum();
  }
  return val;
}

/*
  Validate if expression is an multiplication or division and execute them
  before add and subtract operation.
*/
int term(){
  int val = factor();
  while(isMulOp(token)){
    switch(token){
      case '*':
        match('*');
        val *= term();
        break;
      case '/':
        match('/');
        val /= term();
        break;
    }
  }
  return val;
}

/*
  Process expression received in the right order (parentesys, multiplication and
  add operations).
*/
int expression(){
  int val;
  if(isAddOp(token)){
    val = 0;
  } else {
    val = term();
  }
  while(isAddOp(token)){
    switch(token) {
      case '+':
        match('+');
        val += term();
        break;
      case '-':
        match('-');
        val -= term();
        break;
    }
  }
  return val;
}
/*
  Validate if received char is for multiplication or division.
*/
bool isMulOp(char c) {
  return (c == '/' || c == '*');
}

/*
  Validate if received char is for add or substract.
*/
bool isAddOp(char c) {
  return (c == '+' || c == '-');
}

/*
 Validate if the received token matches with expected and read next.
*/
void match(char c) {
  if(token != c)
    expected("'%c'", c);
  nextToken();
}

/*
 Validate if the received token matches with an number and read all tokens
 after, until is not a digit.
*/
int getNum(){
  int num = 0;
  if (!isdigit(token))
    expected("Integer");
  while(isdigit(token)) {
    num *= 10;
    num += token - '0';
    nextToken();
  }
  return num;
}

/*
 Validate if the token is an alpha(letter) and return with uppercase.
*/
char getName(){
  char name;
  if(!isalpha(token))
    expected("Name");
  name = toupper(token);
  nextToken();
  return name;
}
/*
 Raises an message and exit program.

 Used when an token is expected and doesn't matches with received.
*/
void expected(char *message, ...){
  va_list(args);
  fputs("Error: ", stderr);
  va_start(args, message);
  vfprintf(stderr, message, args);
  va_end(args);
  fputs(" Expected!\n", stderr);
  exit(1);
}
