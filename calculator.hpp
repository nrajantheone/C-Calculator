#ifndef _CALCULATOR_HPP_
#define _CALCULATOR_HPP_ 1

inline int skipSpaces(char& c) {
  int i = 0;
  for(;isspace(c = getchar()); i++) {
    std::cout << c << std::endl;
  }
  return i;
}
#endif // _CALCULATOR_HPP_