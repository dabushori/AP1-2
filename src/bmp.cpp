#include "bmp.h"

namespace bmp {

// Parser

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

void Parser::parseColorPallete() {
  if (m_picture->getBitsPerPixel() == 8) {
    std::map<char, Color> colors{};
    uint32_t currentColor = 54;
    for (uint32_t i = 0; i < m_picture->getNumOfColors(); ++i) {
      colors[m_data[currentColor + 3]] =
          Color(m_data[currentColor], m_data[currentColor + 1],
                m_data[currentColor + 2]);
      currentColor += 4;
    }
    m_picture->setColors(colors);
  }
}

void Parser::parseBitmapArray() {
  matrix::Mat red(m_picture->getBitMapHeight(), m_picture->getBitMapWidth());
  matrix::Mat green(m_picture->getBitMapHeight(), m_picture->getBitMapWidth());
  matrix::Mat blue(m_picture->getBitMapHeight(), m_picture->getBitMapWidth());
  uint32_t index = m_picture->getPixelArrayAddress();
  if (m_picture->getBitsPerPixel() == 24) {
    uint32_t padding = m_picture->getBitMapWidth() % 4;
    for (int i = 0; i < m_picture->getBitMapHeight(); ++i) {
      for (int j = 0; j < m_picture->getBitMapWidth(); ++j) {
        red(i, j) = m_data[index];
        green(i, j) = m_data[index + 1];
        blue(i, j) = m_data[index + 2];
        index += 3;
      }
      index += padding;
    }
  } else {
    uint32_t padding = 4 - m_picture->getBitMapWidth() % 4;
    for (int i = 0; i < m_picture->getBitMapHeight(); ++i) {
      for (int j = 0; j < m_picture->getBitMapWidth(); ++j) {
        char colorNum = m_data[index];
        auto colors = m_picture->getColors();
        red(i, j) = colors[colorNum].getRed();
        green(i, j) = colors[colorNum].getGreen();
        blue(i, j) = colors[colorNum].getBlue();
        ++index;
      }
      index += padding;
    }
  }
  m_picture->setBitmapArray(red, green, blue);
}

// BMP

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

void BMP::setBitsPerPixel(const char bitsPerPixel[2]) {
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

void BMP::setColors(const std::map<char, Color> &colors) { m_colors = colors; }

void BMP::setBitmapArray(const matrix::Mat &red, const matrix::Mat &green,
                         const matrix::Mat &blue) {
  m_red = red;
  m_green = green;
  m_blue = blue;
}

const int BMP::getBitsPerPixel() { return (int)m_bitsPerPixel[1]; }

const uint32_t BMP::getNumOfColors() { return m_numOfColors; }

const uint32_t BMP::getPixelArrayAddress() { return m_pixelArrayAddress; }

const uint32_t BMP::getBitMapWidth() { return m_bitmapWidth; }

const uint32_t BMP::getBitMapHeight() { return m_bitmapHeight; }

const std::map<char, Color> &BMP::getColors() { return m_colors; }

// Color

Color::Color(char red, char green, char blue) {
  m_red = red;
  m_green = green;
  m_blue = blue;
}

double Color::getRed() { return m_red; }

double Color::getGreen() { return m_green; }

double Color::getBlue() { return m_blue; }

} // namespace bmp