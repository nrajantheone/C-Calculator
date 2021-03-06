#pragma  once
#ifndef _OPERAND_HPP_
#define _OPERAND_HPP_ 1
#include <iostream>
#include "Operator.hpp"
#include <stdio.h>
#include <string>
#include <string.h>

const int LINE_LENGTH = 1024;
typedef enum OperandType {
  QUIT = -1,
  INTEGER = 0,
  DOUBLE,
  STRING 
} OPERAND_TYPE;

class Operator;

class Operand {
  public:
  Operand(int& column) : data(NULL), length(0), dvalue(0.0), value(0), type(QUIT), resultType(QUIT){
    allocateMemory();
    char c = '\0';
    int i = 0;
    column = skipSpaces(c);
    column += collectCharacters(c);
    if(!convertToFloat())
      if(!convertToInteger()) {
        type = STRING;
      }
  }
  Operand() : data(NULL), length(0), dvalue(0.0), value(0), type(QUIT), resultType(QUIT) {
    allocateMemory();
  }
  Operand(const Operand& rhs) : data(NULL) , length(rhs.length) , dvalue(rhs.dvalue) , value(rhs.value) , type(rhs.type) , resultType(rhs.resultType) {
    allocateMemory();
    if(rhs.type == STRING)
      strcpy((char*)data, (const char*)rhs.data);
  }

  ~Operand() {
    freeMemory();
  }

  void freeMemory() {
    if(data != NULL) 
      free(data);
      data = NULL;   
  }
  
  int collectCharacters(const char st) {
    int i = 1;
    char  c = '\0';
    ((char*)data)[0] = st;
    for(; isOperator(c = getchar()) == NONE && !isspace(c); i++ ) {
      ((char*)data)[i] = c;    
    }
    ((char*)data)[i + 1] = '\0';
    //std::cout << "i = " << i << std::endl;
    //std::string s((char*)data);
    //std::cout << s << std::endl;
    return (length = i);
  }

  bool isFloat() {
    const char* p = (char*)data;
    for(int i = 0; i < length; i++){
      if(p[i] == '.') return true;
    } 
    return false;
  }

  bool convertToFloat() {
    if(isFloat()) {
      sscanf((char*)data,"%lg", &dvalue);
      type = DOUBLE;
      return true;
    }
    return false;
  }

  void allocateMemory() {
    if(data == NULL)
      data = malloc(LINE_LENGTH);
  }

  bool convertToInteger(){
    if(sscanf((char*)data, "%d", &value)){
      type = INTEGER;
      return true;
    }
    return false;
  }

  OPERAND_TYPE perform(const Operand& rhs, const Operator& o) {
    switch((int)o.getOP()) {
      case ADD:
        return sum(rhs);
      case MULTIPLY:
        printf("Multiply: Type = %d\n", type);
        return product(rhs);
    }
    return QUIT;
  }
  void outputResult(){
    std::string s((char*)data);
    switch(resultType){
      case STRING:
        std::cout << s << std::endl;
        break;
      case INTEGER:
        printf("Result = %d\n", value);
        break;
      case DOUBLE:
        std::cout << dvalue << std::endl;
        break;
      case QUIT:
        break;
    }
  }
  private: 
  OPERAND_TYPE sum(const Operand& rhs){
    switch(rhs.type){
      case INTEGER:
        value += rhs.value;
        return set(INTEGER);
      case DOUBLE:
        dvalue += rhs.dvalue;
        return set(DOUBLE);
      case STRING:
        strcat((char*)data, (char*)rhs.data);
        length = strlen((char*)data);
        return set(STRING);
      case QUIT:
        return set(QUIT);
    } 
    return QUIT;
  }

  int calculateLengthNeeded(const Operand& rhs) const{
    return type == STRING && rhs.type == INTEGER
      ? length * rhs.value
      : value * rhs.length;
  }

  static int copyMultiple(char* dest, const char* data, const int value, const int length) {
    for(int i = 0; i < value-1; i++)
        strncat(dest,  (char*)data, length);
        dest += length;
    return value * length;
  }

  bool copyStringMultipleTimes(const Operand& rhs) {
    if(type == STRING && rhs.type == INTEGER) { 
      printf("copyStringMultipleTimes: String \n");
      length = copyMultiple((char*)data + length
        , (const char*)data
        , rhs.value
        , length);
      return true; 
    }
    if(type == INTEGER && rhs.type ==  STRING) {
      length = copyMultiple((char*)data
        , (const char*)rhs.data
        , value + 1
        , rhs.length);
      return true;
    }
    return false;
  }


  void makeStringProduct(const Operand& rhs) {
    int req = calculateLengthNeeded(rhs);
    printf("makeStringProduct: req = %d \n", req);
    if(req < LINE_LENGTH)
      copyStringMultipleTimes(rhs);
    else {
      data = realloc(data, req + LINE_LENGTH);
      *((char*)data + req) = '\0';
      copyStringMultipleTimes(rhs);
    }
  }
  static bool isStringProduct(const OPERAND_TYPE a, const OPERAND_TYPE b) {
    return (a == STRING && b == INTEGER) || ( a == INTEGER && b == STRING);
  }
  OPERAND_TYPE product(const Operand& rhs) {
    printf("Product Types: Type = %d, rhs.type = %d \n", type, rhs.type);
    if(isStringProduct(type, rhs.type)) {
      makeStringProduct(rhs);
      return set(STRING);
    }
    switch(rhs.type){
      case INTEGER:
        {
          if(type == INTEGER) {
            value *= rhs.value;
            return set(INTEGER);
          }
          dvalue *= rhs.value;
          return set(DOUBLE);
        }
        value *= rhs.value;
        return set(INTEGER);
      case DOUBLE:
        dvalue *= rhs.dvalue;
        return set(DOUBLE);
      default:
        std::cout << "INCORRECT INPUT ERROR" << std::endl;
    }
    return QUIT;
  }

  OPERAND_TYPE set(const OPERAND_TYPE type) {
    return resultType = type;
  }

  void* data;
  int length;
  double  dvalue;
  int value;
  OPERAND_TYPE  type;
  OPERAND_TYPE  resultType;
};
#endif //_OPERAND_HPP_
