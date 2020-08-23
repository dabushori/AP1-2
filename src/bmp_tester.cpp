#include "bmp_tester.hpp"

#include "bmp.h"

namespace testing {
namespace bmp {
bool isBMPFile(const std::string &path) {
  if (path.length() < 5) {
    return false;
  }
  return (path == ".bmp") || isBMPFile(path.substr(1, path.length() - 1));
}

bool isValidFile(const std::string &path) {
  std::ifstream in(path);
  if (!in) {
    return false;
  }
  in.close();
  return true;
}

void rotate_image(const std::string &imagePath, const std::string &outputPath) {
  if (!isBMPFile(imagePath)) {
    throw exceptions::BMPException("input file is not a .bmp file");
  }
  if (!isValidFile(imagePath)) {
    throw exceptions::BMPException("input file doesn't exist");
  }
  if (!isBMPFile(outputPath)) {
    throw exceptions::BMPException("output file is not a .bmp file");
  }
  bmp_parser::Parser parser(imagePath);
  parser.getPicture().rotateImage().writeToFile(outputPath);
}

void convert_to_grayscale(const std::string &imagePath,
                          const std::string &outputPath) {
  if (!isBMPFile(imagePath)) {
    throw exceptions::BMPException("input file is not a .bmp file");
  }
  if (!isValidFile(imagePath)) {
    throw exceptions::BMPException("input file doesn't exist");
  }
  if (!isBMPFile(outputPath)) {
    throw exceptions::BMPException("output file is not a .bmp file");
  }
  bmp_parser::Parser parser(imagePath);
  parser.getPicture().convertToGrayScale().writeToFile(outputPath);
}
} // namespace bmp
} // namespace testing