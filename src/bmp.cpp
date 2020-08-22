#include "bmp.h"

namespace bmp {
void Parser::parseHeader() {}

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

BMP &Parser::getPicture() { return *m_picture; }

void BMP::setMagic(const char magic[2]) {
  m_magic[0] = magic[0];
  m_magic[1] = magic[1];
}

void BMP::setBmpFileSize(const uint32_t &bmpFileSize) {
  m_bmpFileSize = bmpFileSize;
}

void BMP::setPixelArrayAddress(const uint32_t &pixelArrayAddress) {
  m_pixelArrayAddress = pixelArrayAddress;
}

void BMP::setHeaderSize(const uint32_t &headerSize) {
  m_headerSize = headerSize;
}

void BMP::setBitMapWidth(const int &bitmapWidth) {
  m_bitmapWidth = bitmapWidth;
}

void BMP::setBitMapHeight(const int &bitmapHeight) {
  m_bitmapHeight = bitmapHeight;
}

void BMP::setConstant(const char constant[2]) {
  m_constant[0] = constant[0];
  m_constant[1] = constant[1];
}

void BMP::setBitPerPixel(const char bitsPerPixel[2]) {
  m_bitsPerPixel[0] = bitsPerPixel[0];
  m_bitsPerPixel[1] = bitsPerPixel[1];
}

void BMP::setCompression(const uint32_t &compression) {
  m_compression = compression;
}

void BMP::setBitmapSizeWithoutCompression(
    const uint32_t &bitmapSizeWithoutCompression) {
  m_bitmapSizeWithoutCompression = bitmapSizeWithoutCompression;
}

void BMP::setNumOfColors(const uint32_t &numOfColors) {
  m_numOfColors = numOfColors;
}

void BMP::setColors(const std::vector<int> &colors) { m_colors = colors; }

} // namespace bmp