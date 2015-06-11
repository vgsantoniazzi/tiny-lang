#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

#define MAXVAR 26

int var[MAXVAR];

FILE *file;

char token;
char *tokens;
size_t column = 0;

void init(char *file_name);
void readFile(char *file_name);
void assignment();
void nextChar();
void match(char c);
void expected(char *message, ...);
char getName();
bool isAddOp(char c);
bool isMulOp(char c);
int factor();
int getNum();
int expression();
int term();

int main(int argc, char **argv){
  init(argv[1]);
  printf("%d", expression());
  return 0;
}

void assignment(){
  char name;
  name = getName();
  match('=');
  var[name] = expression();
}

void init(char *file_name){
  readFile(file_name);
  nextChar();
}

void readFile(char *file_name){
  char c;
  file = fopen(file_name, "r");
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

void nextChar(){
  token = (char) tokens[column++];
}

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

bool isMulOp(char c) {
  return (c == '/' || c == '*');
}

bool isAddOp(char c) {
  return (c == '+' || c == '-');
}

void match(char c) {
  if(token != c)
    expected("'%c'", c);
  nextChar();
}

int getNum(){
  int num = 0;
  if (!isdigit(token))
    expected("Integer");
  while(isdigit(token)) {
    num *= 10;
    num += token - '0';
    nextChar();
  }
  return num;
}

char getName(){
  char name;
  if(!isalpha(token))
    expected("Name");
  name = toupper(token);
  nextChar();
  return name;
}

void expected(char *message, ...){
  va_list(args);
  fputs("Error: ", stderr);
  va_start(args, message);
  vfprintf(stderr, message, args);
  va_end(args);
  fputs(" Expected!\n", stderr);
  exit(1);
}
