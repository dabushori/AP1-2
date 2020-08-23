#include <fstream>
#include <iostream>
#include <string>

#include "Mat.h"

void printMatrix(const matrix::Mat &matrix) {
  for (uint32_t i = 0; i < matrix.getHeight(); ++i) {
    for (uint32_t j = 0; j < matrix.getWidth(); ++j) {
      std::cout << matrix(i, j);
    }
    std::cout << std::endl;
  }
}

int main() {
  std::ofstream out("details.tx");
  std::string str = "hello hello3";
  out.write(str.data(), static_cast<std::streamsize>(str.length()));
  out.close();
  return 0;
}