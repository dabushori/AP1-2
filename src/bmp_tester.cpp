#include "bmp_tester.hpp"

#include "bmp.h"

namespace testing {
namespace bmp {
void rotate_image(const std::string &imagePath, const std::string &outputPath) {
  bmp_parser::Parser parser(imagePath);
  parser.getPicture().rotateImage().writeToFile(outputPath);
}

void convert_to_grayscale(const std::string &imagePath,
                          const std::string &outputPath) {
  bmp_parser::Parser parser(imagePath);
  parser.getPicture().convertToGrayScale().writeToFile(outputPath);
}
} // namespace bmp
} // namespace testing