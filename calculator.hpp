#ifndef _CALCULATOR_HPP_
#define _CALCULATOR_HPP_ 1

inline int skipSpaces(char& c) {
  if(isspace(c)) {
    int i = 0;
    for(;isspace(c = getchar()); i++) {
      std::cout << c << std::endl;
    }
    return i;
  }
  return 0;
}
#endif // _CALCULATOR_HPP_