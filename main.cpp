    #include <iostream>
#include <stdio.h>
#include "Operand.hpp"
#include "Operator.hpp"


#define debug(x)\
cout << "line " << x << endl

using namespace std;

bool doesOneLine(FILE* file = NULL){
  bool quit = false;
  int column = 0;
  Operand  a(column, file);
  Operator o(column, file);
  Operand  b(column, file);
  Operand  result(a);
  quit = result.perform(b, o) == QUIT;  
  result.outputResult();
  return quit;
}


int main() {
  bool quit = false;
  string  test;
  int column = 0;
  FILE *file = fopen("UnitTests.txt", "r"); 
  if(file != NULL){
    cout << "UnitTest.txt" << endl;
    while(!quit){
      quit = doesOneLine(file);
    }
    fclose(file);
  }
  quit = false; 
  while (!quit){
    cout << ">>>>>>>>>" << endl;
    cin >> test;
    cout << test << endl;
    quit = doesOneLine(stdin);
  }
}
