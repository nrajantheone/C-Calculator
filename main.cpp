#include <iostream>
#include <stdio.h>
#include "Operand.hpp"
#include "Operator.hpp"

#define debug(x)\
cout << "line " << x << endl

using namespace std;

bool doesOneLine(){
  bool quit = false;
  int column = 0;
  Operand  a(column);
  Operator o(column);
  Operand  b(column);
  Operand  result(a);
  quit = result.perform(b, o) == QUIT;
  result.outputResult();
  return quit;
}
int main() {
  bool quit = false;
  int column = 0;
  FILE *file = freopen("UnitTests.txt", "r", stdin);
  if(file != NULL){
    cout << "UnitTest.txt" << endl;
    while(!quit){
      quit = doesOneLine();
    }
  }
  while (!quit){
    cout << ">>>>>>>>>" << endl;
    quit = doesOneLine();
  }
}
