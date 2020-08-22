#include "bmp.h"

namespace bmp {
Parser::Parser(const std::string &filename) {
  m_picture = std::make_unique<BMP>();
  std::ifstream in(filename, std::ios::binary);
  m_data = {std::istreambuf_iterator<char>{in},
            std::istreambuf_iterator<char>{}};
  parseHeader();
  parseDIBHeader();
  parseColorPallete();
  parseBitmapArray();
}
} // namespace bmp