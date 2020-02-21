#include <iostream>
#include "Operand.hpp"
#include "Operator.hpp"

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
 while (!quit){
   std::cout << ">>>>>>>>>" << std::endl;
   quit = doesOneLine();
 }
}
