#include "bmp.h"

namespace bmp_parser {
double BMP::toGray(const double red, const double green, const double blue) {
  return std::round(0.2126 * red + 0.7152 * green + 0.0722 * blue);
}

BMP BMP::rotateImage() {
  BMP converted(*this);
  if (converted.getBitsPerPixel() == 8) {
    converted.setBitmapArray(m_pixels.rotate90Degrees());
  } else {
    converted.setBitmapArray(m_red.rotate90Degrees(), m_green.rotate90Degrees(),
                             m_blue.rotate90Degrees());
  }
  return converted;
}

BMP BMP::convertToGrayScale() {
  BMP converted(*this);
  if (converted.getBitsPerPixel() == 8) {

    auto colors = converted.getColors();
    std::map<char, Color> newColors;

    for (auto it = colors.begin(); it != colors.end(); ++it) {
      newColors.try_emplace(it->first, it->second.toGray());
    }

    converted.setColors(newColors);

  } else {

    uint32_t height = getBitMapHeight(), width = getBitMapWidth();
    matrix::Mat pixels(height, width);
    std::map<char, Color> newColors;
    char key = 0;
    for (uint32_t i = 0; i < height; ++i) {
      for (uint32_t j = 0; j < width; ++j) {
        Color color(m_red(i, j), m_green(i, j), m_blue(i, j));

        bool found = false;
        for (auto it = newColors.begin(); it != newColors.end(); ++it) {
          if (!found && it->second.isEqual(color.toGray())) {
            pixels.setValue(i, j, it->first);
            found = true;
          }
        }
        if (!found) {
          newColors[key] = color.toGray();
          pixels.setValue(i, j, key);
          ++key;
        }
      }
    }

    converted.setColors(newColors);
    converted.setBitmapArray(pixels);
  }
  return converted;
}

void BMP::writeToFile(const std::string &outputFile) {
  std::ofstream out(outputFile);
  if (!out) {
    throw exceptions::BMPException(
        "error occured - couldn't open the output file");
  }

  // writing

  if (!out) {
    throw exceptions::BMPException(
        "error occured after finished writing to the file");
  }
  out.close();
}

// BMP

void BMP::setMagic(const char magic[2]) {
  m_magic[0] = magic[0];
  m_magic[1] = magic[1];
}

void BMP::setBmpFileSize(const uint32_t &bmpFileSize) {
  m_bmpFileSize = bmpFileSize;
}

void BMP::setReserved(const char reserved[4]) {
  for (int i = 0; i < 4; ++i) {
    m_reserved[i] = reserved[i];
  }
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

void BMP::setResolution(const char resolution[8]) {
  for (int i = 0; i < 8; ++i) {
    m_resolution[i] = resolution[i];
  }
}

void BMP::setNumOfColors(const uint32_t &numOfColors) {
  m_numOfColors = numOfColors;
}

void BMP::setNumOfImportantColors(const char numOfImportantColors[4]) {
  for (int i = 0; i < 4; ++i) {
    m_numberOfImportantColors[i] = numOfImportantColors[i];
  }
}

void BMP::setColors(const std::map<char, Color> &colors) { m_colors = colors; }

void BMP::setBitmapArray(const matrix::Mat &red, const matrix::Mat &green,
                         const matrix::Mat &blue) {
  m_red = red;
  m_green = green;
  m_blue = blue;
}

void BMP::setBitmapArray(const matrix::Mat &pixels) {
  m_pixels = pixels;
  m_red = matrix::Mat();
  m_green = matrix::Mat();
  m_blue = matrix::Mat();
}

int BMP::getBitsPerPixel() { return (int)m_bitsPerPixel[1]; }

uint32_t BMP::getNumOfColors() { return m_numOfColors; }

uint32_t BMP::getPixelArrayAddress() { return m_pixelArrayAddress; }

uint32_t BMP::getBitMapWidth() { return m_bitmapWidth; }

uint32_t BMP::getBitMapHeight() { return m_bitmapHeight; }

const std::map<char, Color> &BMP::getColors() { return m_colors; }

// Parser

Parser::Parser(const std::string &filename) {
  m_picture = std::make_unique<BMP>();

  std::ifstream in(filename, std::ios::binary);
  if (!in) {
    throw exceptions::BMPException("error occured in the file reading");
  }

  m_data = {std::istreambuf_iterator<char>{in},
            std::istreambuf_iterator<char>{}};

  if (!in.eof()) {
    throw exceptions::BMPException(
        "error occured - didn't reach the end of the file");
  }

  parseHeader();
  parseDIBHeader();
  parseColorPallete();
  parseBitmapArray();

  in.close();
}

BMP &Parser::getPicture() { return *m_picture; }

void Parser::parseHeader() {
  parseMagic();
  parseBmpFileSize();
  parseReserved();
  parsePixelArrayAddress();
}

void Parser::parseMagic() {
  if (m_data[0] != 'B' || m_data[1] != 'M') {
    throw exceptions::BMPException("Error in Magic - Header");
  }
  const char magic[2] = {m_data[0], m_data[1]};
  m_picture->setMagic(magic);
}

void Parser::parseBmpFileSize() {
  const char bmpFileSize[4] = {m_data[2], m_data[3], m_data[4], m_data[5]};
  m_picture->setBmpFileSize(bytesToUnsignedInt(bmpFileSize));
}

void Parser::parseReserved() {
  const char reserved[4] = {m_data[6], m_data[7], m_data[8], m_data[9]};
  m_picture->setReserved(reserved);
}

void Parser::parsePixelArrayAddress() {
  const char pixelArrayAddress[4] = {m_data[10], m_data[11], m_data[12],
                                     m_data[13]};
  m_picture->setPixelArrayAddress(bytesToUnsignedInt(pixelArrayAddress));
}

void Parser::parseDIBHeader() {
  parseHeaderSize();
  parseBitmapWidth();
  parseBitmapHeight();
  parseConstant();
  parseBitsPerPixel();
  parseCompression();
  parseBitmapSizeWithoutCompression();
  parseResolution();
  parseNumOfColors();
  parseNumOfImportantColors();
}

void Parser::parseHeaderSize() {
  const char headerSizeArray[4] = {m_data[14], m_data[15], m_data[16],
                                   m_data[17]};
  uint32_t headerSize = bytesToUnsignedInt(headerSizeArray);
  if (headerSize != 40) {
    throw exceptions::BMPException(
        "Error in size of header(not 40) - in DIBHeader");
  }
  m_picture->setHeaderSize(headerSize);
}

void Parser::parseBitmapWidth() {
  const char bitmapWidth[4] = {m_data[18], m_data[19], m_data[20], m_data[21]};
  m_picture->setBitMapWidth(bytesToSignedInt(bitmapWidth));
}

void Parser::parseBitmapHeight() {
  const char bitmapHeight[4] = {m_data[22], m_data[23], m_data[24], m_data[25]};
  m_picture->setBitMapHeight(bytesToSignedInt(bitmapHeight));
}

void Parser::parseConstant() {
  if (m_data[26] != 0 || m_data[27] != 1) {
    throw exceptions::BMPException("Error in constant(not 1) - in DIBHeader");
  }
  const char constant[2] = {m_data[26], m_data[27]};
  m_picture->setConstant(constant);
}

void Parser::parseBitsPerPixel() {
  uint16_t bitsPerPixel = m_data[28];
  bitsPerPixel <<= 8;
  bitsPerPixel += m_data[29];
  if (bitsPerPixel != 0) {
    throw exceptions::BMPException(
        "Error in bitsPerPixel(not 0) - in DIBHeader");
  }
}

void Parser::parseCompression() {
  const char compressionArray[4] = {m_data[30], m_data[31], m_data[32],
                                    m_data[33]};
  uint32_t compression = bytesToUnsignedInt(compressionArray);
  if (compression != 0) {
    throw exceptions::BMPException(
        "Error in compression(not 0) - in DIBHeader");
  }
  m_picture->setCompression(compression);
}

void Parser::parseBitmapSizeWithoutCompression() {
  const char bitmapSizeWithoutCompressionArray[4] = {m_data[34], m_data[35],
                                                     m_data[36], m_data[37]};
  uint32_t bitmapSizeWithoutCompression =
      bytesToUnsignedInt(bitmapSizeWithoutCompressionArray);
  m_picture->setBitmapSizeWithoutCompression(bitmapSizeWithoutCompression);
}

void Parser::parseResolution() {
  char resolution[8];
  for (int i = 0; i < 8; ++i) {
    resolution[i] = m_data[38 + i];
  }
  m_picture->setResolution(resolution);
}

void Parser::parseNumOfColors() {
  const char numOfColorsArray[4] = {m_data[46], m_data[47], m_data[48],
                                    m_data[49]};
  uint32_t numOfColors = bytesToUnsignedInt(numOfColorsArray);
  if (numOfColors == 0) {
    numOfColors = std::pow(2, m_picture->getBitsPerPixel());
  }
  m_picture->setNumOfColors(numOfColors);
}

void Parser::parseNumOfImportantColors() {
  const char numOfImportantColorsArray[4] = {m_data[50], m_data[51], m_data[52],
                                             m_data[53]};
  m_picture->setNumOfImportantColors(numOfImportantColorsArray);
}

uint32_t Parser::bytesToUnsignedInt(const char bytes[4]) {
  uint32_t result = bytes[0];
  for (auto i = 1; i < 4; i++) {
    result <<= 8;
    result += bytes[i];
  }
  return result;
}

int Parser::bytesToSignedInt(const char bytes[4]) {
  int result = bytes[0];
  for (auto i = 1; i < 4; i++) {
    result <<= 8;
    result += bytes[i];
  }
  return result;
}

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
  uint32_t height = m_picture->getBitMapHeight(),
           width = m_picture->getBitMapWidth();
  uint32_t index = m_picture->getPixelArrayAddress();
  if (m_picture->getBitsPerPixel() == 24) {
    matrix::Mat red(height, width);
    matrix::Mat green(height, width);
    matrix::Mat blue(height, width);
    uint32_t padding = width % 4;
    for (uint32_t i = 0; i < height; ++i) {
      for (uint32_t j = 0; j < width; ++j) {
        red.setValue(i, j, m_data[index]);
        green.setValue(i, j, m_data[index + 1]);
        blue.setValue(i, j, m_data[index + 2]);

        index += 3;
      }
      index += padding;
    }
    m_picture->setBitmapArray(red, green, blue);

  } else {
    uint32_t padding = 4 - width % 4;
    matrix::Mat pixels(height, width);
    for (uint32_t i = 0; i < height; ++i) {
      for (uint32_t j = 0; j < width; ++j) {
        char colorNum = m_data[index];
        pixels.setValue(i, j, colorNum);
        ++index;
      }
      index += padding;
    }
    m_picture->setBitmapArray(pixels);
  }
}

// Color

Color::Color() {
  m_red = 0;
  m_green = 0;
  m_blue = 0;
}

Color::Color(char red, char green, char blue) {
  m_red = red;
  m_green = green;
  m_blue = blue;
}

double Color::getRed() { return m_red; }

double Color::getGreen() { return m_green; }

double Color::getBlue() { return m_blue; }

Color Color::toGray() {
  char val = std::round(0.2126 * m_red + 0.7152 * m_green + 0.0722 * m_blue);
  return Color(val, val, val);
}

bool Color::isEqual(const Color &other) {
  return m_red == other.m_red && m_green == other.m_green &&
         m_blue == other.m_blue;
}

} // namespace bmp_parser