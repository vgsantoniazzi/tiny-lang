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

/* token types */
#define TOKEN_VARIABLE      1
#define TOKEN_INTEGER       2
#define TOKEN_ASSIGNMENT    3
#define TOKEN_OPEN_PARENS   4
#define TOKEN_CLOSE_PARENS  5
#define TOKEN_PLUS          6
#define TOKEN_MINUS         7
#define TOKEN_TIMES         8
#define TOKEN_DIVIDE        9
#define TOKEN_END_OF_STAT   32
#define TOKEN_OUTPUT        64
#define TOKEN_END_OF_FILE   128

#define STR_ASSIGNMENT "="
#define STR_OPEN_PARENTHESYS "("
#define STR_CLOSE_PARENTHESYS ")"
#define STR_PLUS "+"
#define STR_MINUS "-"
#define STR_TIMES "*"
#define STR_DIVIDE "/"
#define STR_END_OF_STATMENT ";"
#define STR_OUTPUT "?"


struct token_type {
  int type;
  char *name;
} token;


struct variable {
  int value;
  char *name;
} variables[MAXVAR];


void init(char *file_name);
void readFile(char *file_name);
void assignment();
void nextToken();
void nextStatement();
void output();
void match(char *str);
void expected(char *message, ...);
char *getName();
bool isAddOp(struct token_type tk);
bool isMulOp(struct token_type tk);
int factor();
int getNum();
int expression();
int term();


int end_of_file() {
  return string_buffer.size <= string_buffer.position;
}

/*
  Initialize interpreter.

  @receive int argc: counter of args received.
  @receive char argv: Array with all arguments received.
*/
int main(int argc, char **argv){
  init(argv[1]);

  while(!end_of_file()) {
    switch(token.type){
      case TOKEN_OUTPUT:
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


int get_value(char *variable) {
  int i;

  for (i = 0; i < MAXVAR; i++) {
    if (variables[i].name != NULL && 
        strcmp(variables[i].name, variable) == 0)
      return variables[i].value;
  }

  return 0;
}

void put_value(char *variable, int value) {
  int i = 0;

  /* if we already have this variable, change the value */
  int found = 0;

  for (i = 0; i < MAXVAR; i++) {
    if (variables[i].name != NULL && 
        strcmp(variables[i].name, variable) == 0) {
      variables[i].value = value;
      found = 1;
    }
  }

  /* if we haven't, add to the list */
  if (!found) {
    for (i = 0; i < MAXVAR; i++) {
      if (variables[i].name == NULL) {
        
        variables[i].name  = strdup(variable);
        variables[i].value = value;

        break;
      }
    }
  }
}

void init_symbol_table() {
  int i;
  for (i = 0; i < MAXVAR; i++) {
    variables[i].name = NULL;
    variables[i].value = 0;
  }
}

/*
  First step to start to interpreting. Read an file and get the first char
*/
void init(char *file_name){
  init_symbol_table();

  readFile(file_name);
  nextToken();
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

void variable() {
  char *token_name;
  char chr;

  int token_size;
  int begin_token;
  int end_token;

  begin_token = string_buffer.position;
  end_token   = string_buffer.position;

  do {
    chr = string_buffer.buffer[end_token++];
  } while(isalpha(chr));

  //if (token.name != NULL)
  //  free(token.name);

  token_size = (end_token - begin_token) - 1;
  token_name = (char *)malloc(token_size + 1);

  memcpy((void *)token_name, (void *)((string_buffer.buffer) + begin_token), token_size);
  token_name[token_size] = '\0';

  token.name = token_name;
  token.type = TOKEN_VARIABLE;

  string_buffer.position += token_size;
  string_buffer.current_pos += token_size;
}


void number() {
  char *token_name;
  char chr;

  int token_size;
  int begin_token;
  int end_token;

  begin_token = string_buffer.position;
  end_token   = string_buffer.position;

  do
  {
    chr = string_buffer.buffer[end_token++];
  } while(isdigit(chr));

  //if (token.name != NULL)
  //  free(token.name);

  token_size = (end_token - begin_token) - 1;

  token_name = (char *)malloc(token_size + 1);

  memcpy((void *)token_name, (void *)((string_buffer.buffer) + begin_token), token_size);
  token_name[token_size] = '\0';

  token.name = token_name;
  token.type = TOKEN_INTEGER;

  string_buffer.position += token_size;
  string_buffer.current_pos += token_size;
}

/*
 Read next token from array of them.
*/
void nextToken(){
  char chr;
  
  while (!end_of_file()) {

    chr = string_buffer.buffer[string_buffer.position];
 
    if (isalpha(chr)) {
      variable();
      return;
    }

    if (isdigit(chr)) {
      number();
      return;
    }

    switch (chr) {

      case '+':
        token.type = TOKEN_PLUS;
        token.name = STR_PLUS;
        break;

      case '-':
        token.type = TOKEN_MINUS;
        token.name = STR_MINUS;
        break;

      case '/':
        token.type = TOKEN_DIVIDE;
        token.name = STR_DIVIDE;
        break;

      case '*':
        token.type = TOKEN_TIMES;
        token.name = STR_TIMES;
        break;

      case '=':
        token.type = TOKEN_ASSIGNMENT;
        token.name = STR_ASSIGNMENT;
        break;

      case '(':
        token.type = TOKEN_OPEN_PARENS;
        token.name = STR_OPEN_PARENTHESYS;
        break;

      case ')':
        token.type = TOKEN_CLOSE_PARENS;
        token.name = STR_CLOSE_PARENTHESYS;
        break;

      case ';':
        token.type = TOKEN_END_OF_STAT;
        token.name = STR_END_OF_STATMENT;
        break;

      case '?':
        token.type = TOKEN_OUTPUT;
        token.name = STR_OUTPUT;
        break;

      /* ignore spaces and break lines */
      case '\n':
        string_buffer.current_line++;
        string_buffer.current_pos = 0;
      case ' ':
      case '\t':
      case '\r':
        string_buffer.position++;
        string_buffer.current_pos++;
        continue;

      default:
        expected("Char not expected %s", chr);
        return;
    }

    string_buffer.position++;
    string_buffer.current_pos++;

    return;
  }
  
  token.type = TOKEN_END_OF_FILE;
  token.name = "";
}

/*
 Go to the next line.
*/
void nextStatement(){
  if(token.type == TOKEN_END_OF_STAT){
    match(";");
  }
}

/*
  Assign an math expression to a one alphabet letter.
*/
void assignment(){

  char *name;
  int value;

  name = getName();

  match("=");
  
  value = expression();
  put_value(name, value);
}

/*
 Validate if the char is for output variable value.
*/
void output(){
  char *name;

  match("?");
  name = getName();
  
  printf("%d \n", get_value(name));
}

/*
  Validate if has an parentesys. Execute them before commom expression.
*/
int factor(){

  int val;

  if(token.type == TOKEN_OPEN_PARENS) {
    match("(");
    val = expression();
    match(")");
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
    switch(token.type){
      case TOKEN_TIMES:
        match("*");
        val *= term();
        break;

      case TOKEN_DIVIDE:
        match("/");
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
int expression() {

  int val;

  if(isAddOp(token)){
    val = 0;
  } else {
    val = term();
  }

  while(isAddOp(token)){
    switch(token.type) {
      case TOKEN_PLUS:
        match("+");
        val += term();
        break;

      case TOKEN_MINUS:
        match("-");
        val -= term();
        break;
    }
  }

  return val;
}

/*
  Validate if received char is for multiplication or division.
*/
bool isMulOp(struct token_type tk) {
  return (tk.type == TOKEN_DIVIDE || tk.type == TOKEN_TIMES);
}

/*
  Validate if received char is for add or substract.
*/
bool isAddOp(struct token_type tk) {
  return (tk.type == TOKEN_PLUS || tk.type == TOKEN_MINUS);
}

/*
 Validate if the received token matches with expected and read next.
*/
void match(char *str) {
  if(strcmp(token.name, str) != 0)
    expected("'%s'", str);

  nextToken();
}

/*
 Validate if the received token matches with an number and read all tokens
 after, until is not a digit.
*/
int getNum() {

  int num = 0;
  char *str;

  if (token.type != TOKEN_INTEGER)
    expected("Integer");

  str = token.name;

  while(*str) {
    num *= 10;
    num += (*str) - '0';
    str++;
  }

  nextToken();
  return num;
}

/*
 Validate if the token is an alpha(letter) and return with uppercase.
*/
char *getName(){
  char *name;

  if(token.type != TOKEN_VARIABLE)
    expected("Variable");

  name = token.name;

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
  fprintf(stderr, " Expected! Found: %s (line: %d, column: %d) \n", token.name, string_buffer.current_line, string_buffer.current_pos);
  exit(1);
}
