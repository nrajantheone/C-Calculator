#ifndef _CALCULATOR_HPP_
#define _CALCULATOR_HPP_ 1

inline int skipSpaces(char& c) {
  int i = 0;
  int j = 0;
  /*for(;(j = getchar())!= EOF && (isspace(j)); i++) c = j;
  return j == EOF? EOF : i;
  for(;isspace(c = getchar()); i++);*/
  c = getchar();
  if(c == EOF)return EOF;
  while(c != EOF && isspace(c)){
    c = getchar(); 
    i++;
  }
  return c != EOF ? i : EOF;
}
#endif // _CALCULATOR_HPP_