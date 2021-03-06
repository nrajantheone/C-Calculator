#ifndef _OPERATOR_HPP_
#define _OPERATOR_HPP_ 1
#include "calculator.hpp"
typedef enum operators {
  NONE = -2,
  ADD = 0,
  SUBTRACT,
  DIVIDE,
  MULTIPLY,
  MODULUS
} OPERATOR;

OPERATOR isOperator(const char c){
  switch(c) {
    case '+':
      return ADD;
    case '-':
      return SUBTRACT;
    case '*':
      return MULTIPLY;
    case '/':
      return DIVIDE;
    case '%':
      return MODULUS;
  }
  return NONE;
}

class Operator {

  public:

  Operator(int& column): _op(NONE) {
    char c;
    column = skipSpaces(c);
    _op = isOperator(c);
  }
  OPERATOR getOP() const {
    return _op;
  }
  private:
  OPERATOR  _op;
  
};
#endif //_OPERATOR_HPP_