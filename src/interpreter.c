/*
 Author: Victor Antoniazzi <vgsantoniazzi@gmail.com>

 Interpreter for a tiny language. The scope is learn how interpreters work and
 build one. Math expressions and control sctructure (if and else);
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

#include <sys/stat.h>

/*
  Define array and size of variables.
*/
#define MAXVAR 26
int var[MAXVAR];

#define END_OF_FILE '\0'

/* struct defining how we must walk on the text */
struct {
  /* contains the current line */
  int current_line;

  /* contains the current position in the line */
  int current_pos;

  /* global position in the string */
  int position;

  /* buffer size */
  int size;

  /* chars */
  char *buffer;
} string_buffer;


/*
  Define current token and array with all tokens.
*/
char token;

void init(char *file_name);
void readFile(char *file_name);
void assignment();
void nextToken();
void nextStatement();
void output();
void match(char c);
void expected(char *message, ...);
char getName();
bool isAddOp(char c);
bool isMulOp(char c);
int factor();
int getNum();
int expression();
int term();


int end_of_file() {
  return string_buffer.size < string_buffer.position;
}

/*
  Initialize interpreter.

  @receive int argc: counter of args received.
  @receive char argv: Array with all arguments received.
*/
int main(int argc, char **argv){
  init(argv[1]);

  while(!end_of_file()) {
    switch(token){
      case '?':
        output();
        break;
      default:
        assignment();
        break;
    }
    nextStatement();
  }
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
 Validate if the char is for output variable value.
*/
void output(){
  match('?');
  char name = getName();
  printf("%d \n", var[name]);
}


/*
  get the size of the source code
 */
long filesize(char *filename) {
  FILE *fp = fopen(filename, "rb");

  if (fp == NULL)
    expected("file not found: %s", filename);

  fseek(fp, 0, SEEK_END);
  long fsize = ftell(fp);
  fclose(fp);

  return fsize;
}

/*
  Read received file_name and put all chars to array of tokens.
*/
void readFile(char *file_name) {
  long fsize = filesize(file_name);

  FILE *fp = fopen(file_name, "rb");
  
  if(fp == NULL)
    expected("file not found: %s", file_name);

  char *buffer = malloc(fsize + 1);
  fread((void *)buffer, 1, fsize, fp);
  buffer[fsize] = '\0';

  fclose(fp);

  string_buffer.buffer = buffer;
  string_buffer.size   = fsize;
  string_buffer.position = 0;

  string_buffer.current_pos  = 1;
  string_buffer.current_line = 1;
}

/*
 Read next token from array of them.
*/
void nextToken(){
  char chr;

  while (!end_of_file()) {
    chr = string_buffer.buffer[string_buffer.position];
    
    switch (chr) {

      /* ignore spaces and break lines */
      case '\n':
        string_buffer.current_line++;
        string_buffer.current_pos = 0;
      case ' ':
      case '\t':
      case '\r':
        string_buffer.position++;
        string_buffer.current_pos++;
        break;

      default:
        token = chr;
        string_buffer.position++;
        string_buffer.current_pos++;
        return;
    }
  }

  token = END_OF_FILE;
}

/*
 Go to the next line.
 Do not support multiple lines expression.
*/
void nextStatement(){
  if(token == ';'){
    match(';');
  }
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
  fprintf(stderr, " Expected! Found: %c (line: %d, column: %d) \n", token, string_buffer.current_line, string_buffer.current_pos);
  exit(1);
}
