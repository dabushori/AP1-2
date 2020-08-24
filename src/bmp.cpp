#include "bmp.h"

namespace bmp_parser {
double BMP::toGray(const char red, const char green, const char blue) const {
  return std::round(0.2126 * red + 0.7152 * green + 0.0722 * blue);
}

BMP BMP::rotateImage() const {
  BMP converted(*this);
  if (converted.getBitsPerPixel() == 8) {
    converted.setBitmapArray(m_pixels.rotate90Degrees());
  } else {
    converted.setBitmapArray(m_red.rotate90Degrees(), m_green.rotate90Degrees(),
                             m_blue.rotate90Degrees());
  }
  char newWidth[4] = {m_bitmapHeight[0], m_bitmapHeight[1], m_bitmapHeight[2],
                      m_bitmapHeight[3]};
  converted.setBitMapHeight(m_bitmapWidth);
  converted.setBitMapWidth(newWidth);
  return converted;
}

BMP BMP::convertToGrayScale() const {
  BMP converted(*this);
  if (converted.getBitsPerPixel() == 8) {
    auto colors = converted.getColors();
    for (auto it = colors.begin(); it != colors.end(); ++it) {
      *it = it->toGray();
    }
    converted.setColors(colors);
    converted.setNumOfColors(colors.size());
  } else {
    for (uint32_t i = 0; i < converted.m_red.getHeight(); ++i) {
      for (uint32_t j = 0; j < converted.m_red.getWidth(); ++j) {
        Color color(m_red(i, j), m_green(i, j), m_blue(i, j));
        Color gray = color.toGray();
        converted.m_red.setValue(i, j, gray.getRed());
        converted.m_green.setValue(i, j, gray.getGreen());
        converted.m_blue.setValue(i, j, gray.getBlue());
      }
    }
  }
  return converted;
}

void BMP::writeToFile(const std::string &outputFile) const {
  std::ofstream out(outputFile, std::ios::binary | std::ios::trunc);
  if (!out) {
    throw exceptions::BMPException(
        "error occured - couldn't open the output file");
  }
  out << m_magic[0] << m_magic[1];
  for (uint32_t i = 0; i < 4; ++i) {
    out << m_bmpFileSize[i];
  }
  for (uint32_t i = 0; i < 4; ++i) {
    out << m_reserved[i];
  }
  for (uint32_t i = 0; i < 4; ++i) {
    out << m_pixelArrayAddress[i];
  }
  for (uint32_t i = 0; i < 4; ++i) {
    out << m_headerSize[i];
  }
  for (uint32_t i = 0; i < 4; ++i) {
    out << m_bitmapWidth[i];
  }
  for (uint32_t i = 0; i < 4; ++i) {
    out << m_bitmapHeight[i];
  }
  out << m_constant[0] << m_constant[1];
  out << m_bitsPerPixel[0] << m_bitsPerPixel[1];
  for (uint32_t i = 0; i < 4; ++i) {
    out << m_compression[i];
  }
  for (uint32_t i = 0; i < 4; ++i) {
    out << m_bitmapSizeWithoutCompression[i];
  }
  for (uint32_t i = 0; i < 8; ++i) {
    out << m_resolution[i];
  }
  for (uint32_t i = 0; i < 4; ++i) {
    out << m_numOfColors[i];
  }
  for (uint32_t i = 0; i < 4; ++i) {
    out << m_numberOfImportantColors[i];
  }

  if (getBitsPerPixel() == 8) {
    for (auto it = m_colors.begin(); it != m_colors.end(); ++it) {
      out << (char)it->getRed() << (char)it->getGreen() << (char)it->getBlue()
          << (char)0;
    }
    uint32_t padding = getBitMapWidth() % 4;
    for (int i = m_pixels.getHeight() - 1; i >= 0; --i) {
      for (uint32_t j = 0; j < m_pixels.getWidth(); ++j) {
        out << (char)m_pixels(i, j);
      }
      for (uint32_t j = 0; j < padding; ++j) {
        out << (char)0;
      }
    }
  } else {
    uint32_t padding = getBitMapWidth() % 4;
    for (int i = m_red.getHeight() - 1; i >= 0; --i) {
      for (uint32_t j = 0; j < m_red.getWidth(); ++j) {
        out << (char)m_red(i, j) << (char)m_green(i, j) << (char)m_blue(i, j);
      }
      for (uint32_t j = 0; j < padding; ++j) {
        out << (char)0;
      }
    }
  }

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

void BMP::setBmpFileSize(const char bmpFileSize[4]) {
  for (uint32_t i = 0; i < 4; ++i) {
    m_bmpFileSize[i] = bmpFileSize[i];
  }
}

void BMP::setBmpFileSize(const int size) {
  int temp = size;
  for (uint32_t i = 0; i < 4; ++i) {
    m_bmpFileSize[i] = (char)size;
    temp >>= 8;
  }
}

void BMP::setReserved(const char reserved[4]) {
  for (int i = 0; i < 4; ++i) {
    m_reserved[i] = reserved[i];
  }
}

void BMP::setPixelArrayAddress(const char pixelArrayAddress[4]) {
  for (uint32_t i = 0; i < 4; ++i) {
    m_pixelArrayAddress[i] = pixelArrayAddress[i];
  }
}

void BMP::setPixelArrayAddress(const int address) {
  int temp = address;
  for (uint32_t i = 0; i < 4; ++i) {
    m_pixelArrayAddress[i] = (char)temp;
    temp >>= 8;
  }
}

void BMP::setHeaderSize(const char headerSize[4]) {
  for (int i = 0; i < 4; ++i) {
    m_headerSize[i] = headerSize[i];
  }
}

void BMP::setBitMapWidth(const char bitmapWidth[4]) {
  for (int i = 0; i < 4; ++i) {
    m_bitmapWidth[i] = bitmapWidth[i];
  }
}

void BMP::setBitMapHeight(const char bitmapHeight[4]) {
  for (int i = 0; i < 4; ++i) {
    m_bitmapHeight[i] = bitmapHeight[i];
  }
}

void BMP::setConstant(const char constant[2]) {
  m_constant[0] = constant[0];
  m_constant[1] = constant[1];
}

void BMP::setBitsPerPixel(const char bitsPerPixel[2]) {
  m_bitsPerPixel[0] = bitsPerPixel[0];
  m_bitsPerPixel[1] = bitsPerPixel[1];
}

void BMP::setBitsPerPixel(const int &bitsPerPixel) {
  if (bitsPerPixel != 8 && bitsPerPixel != 24) {
    throw exceptions::BMPException("bitsPerPixel not 8 or 24");
  }
  m_bitsPerPixel[0] = bitsPerPixel;
  m_bitsPerPixel[1] = 0;
}

void BMP::setCompression(const char compression[4]) {
  for (int i = 0; i < 4; ++i) {
    m_compression[i] = compression[i];
  }
}

void BMP::setBitmapSizeWithoutCompression(
    const char bitmapSizeWithoutCompression[4]) {
  for (int i = 0; i < 4; ++i) {
    m_bitmapSizeWithoutCompression[i] = bitmapSizeWithoutCompression[i];
  }
}

void BMP::setResolution(const char resolution[8]) {
  for (int i = 0; i < 8; ++i) {
    m_resolution[i] = resolution[i];
  }
}

void BMP::setNumOfColors(const char numOfColors[4]) {
  for (int i = 0; i < 4; ++i) {
    m_numOfColors[i] = numOfColors[i];
  }
}

void BMP::setNumOfColors(const size_t numOfColors) {
  char numOfColorsArray[4];
  int temp = numOfColors;
  for (int i = 3; i >= 0; --i) {
    numOfColorsArray[i] = (char)(temp & 255);
    temp = temp >> 8;
  }
  setNumOfColors(numOfColorsArray);
}

void BMP::setNumOfImportantColors(const char numOfImportantColors[4]) {
  for (int i = 0; i < 4; ++i) {
    m_numberOfImportantColors[i] = numOfImportantColors[i];
  }
}

void BMP::setColors(const std::vector<Color> &colors) { m_colors = colors; }

void BMP::setBitmapArray(const matrix::Mat &red, const matrix::Mat &green,
                         const matrix::Mat &blue) {
  m_pixels = matrix::Mat();
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

int BMP::getBitsPerPixel() const { return (int)m_bitsPerPixel[0]; }

uint32_t BMP::getNumOfColors() const {
  for (int i = 0; i < 4; ++i) {
    if (m_numOfColors[i] != 0) {
      return bytesToUnsignedInt(m_numOfColors);
    }
  }
  return std::pow(2, getBitsPerPixel());
}

uint32_t BMP::getPixelArrayAddress() const {
  return bytesToUnsignedInt(m_pixelArrayAddress);
}

uint32_t BMP::getBitMapWidth() const {
  return bytesToUnsignedInt(m_bitmapWidth);
}

uint32_t BMP::getBitMapHeight() const {
  return bytesToUnsignedInt(m_bitmapHeight);
}

std::vector<Color> &BMP::getColors() { return m_colors; }

// Parser

Parser::Parser(const std::string &filename) {

  m_picture = {};

  std::ifstream in(filename, std::ios::binary);
  if (!in) {
    throw exceptions::BMPException("error occured in the file reading");
  }

  m_data = std::vector<char>{std::istreambuf_iterator<char>{in},
                             std::istreambuf_iterator<char>{}};

  parseHeader();
  parseDIBHeader();
  parseColorPallete();
  parseBitmapArray();

  in.close();
}

BMP Parser::getPicture() const { return m_picture; }

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
  m_picture.setMagic(magic);
}

void Parser::parseBmpFileSize() {
  const char bmpFileSize[4] = {m_data[2], m_data[3], m_data[4], m_data[5]};
  m_picture.setBmpFileSize(bmpFileSize);
}

void Parser::parseReserved() {
  const char reserved[4] = {m_data[6], m_data[7], m_data[8], m_data[9]};
  m_picture.setReserved(reserved);
}

void Parser::parsePixelArrayAddress() {
  const char pixelArrayAddress[4] = {m_data[10], m_data[11], m_data[12],
                                     m_data[13]};
  m_picture.setPixelArrayAddress(pixelArrayAddress);
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
  if (bytesToSignedInt(headerSizeArray) != 40) {
    throw exceptions::BMPException(
        "Error in size of header(not 40) - in DIBHeader");
  }
  m_picture.setHeaderSize(headerSizeArray);
}

void Parser::parseBitmapWidth() {
  const char bitmapWidth[4] = {m_data[18], m_data[19], m_data[20], m_data[21]};
  m_picture.setBitMapWidth(bitmapWidth);
}

void Parser::parseBitmapHeight() {
  const char bitmapHeight[4] = {m_data[22], m_data[23], m_data[24], m_data[25]};
  m_picture.setBitMapHeight(bitmapHeight);
}

void Parser::parseConstant() {
  if (m_data[26] != 1 || m_data[27] != 0) {
    throw exceptions::BMPException("Error in constant(not 1) - in DIBHeader");
  }
  const char constant[2] = {m_data[26], m_data[27]};
  m_picture.setConstant(constant);
}

void Parser::parseBitsPerPixel() {
  char bitsPerPixelArray[2] = {m_data[28], m_data[29]};
  uint16_t bitsPerPixel = m_data[29];
  bitsPerPixel <<= 8;
  bitsPerPixel += m_data[28];
  if (bitsPerPixel != 8 && bitsPerPixel != 24) {
    throw exceptions::BMPException(
        "Error in bitsPerPixel(not 8 and 24) - in DIBHeader");
  }
  m_picture.setBitsPerPixel(bitsPerPixelArray);
}

void Parser::parseCompression() {
  const char compressionArray[4] = {m_data[30], m_data[31], m_data[32],
                                    m_data[33]};
  if (bytesToSignedInt(compressionArray) != 0) {
    throw exceptions::BMPException(
        "Error in compression(not 0) - in DIBHeader");
  }
  m_picture.setCompression(compressionArray);
}

void Parser::parseBitmapSizeWithoutCompression() {
  const char bitmapSizeWithoutCompressionArray[4] = {m_data[34], m_data[35],
                                                     m_data[36], m_data[37]};
  m_picture.setBitmapSizeWithoutCompression(bitmapSizeWithoutCompressionArray);
}

void Parser::parseResolution() {
  char resolution[8];
  for (int i = 0; i < 8; ++i) {
    resolution[i] = m_data[38 + i];
  }
  m_picture.setResolution(resolution);
}

void Parser::parseNumOfColors() {
  const char numOfColorsArray[4] = {m_data[46], m_data[47], m_data[48],
                                    m_data[49]};
  m_picture.setNumOfColors(numOfColorsArray);
}

void Parser::parseNumOfImportantColors() {
  const char numOfImportantColorsArray[4] = {m_data[50], m_data[51], m_data[52],
                                             m_data[53]};
  m_picture.setNumOfImportantColors(numOfImportantColorsArray);
}

uint32_t bytesToUnsignedInt(const char bytes[4]) {
  uint32_t result = bytes[3];
  for (int i = 2; i >= 0; --i) {
    result <<= 8;
    result += bytes[i];
  }
  return result;
}

int bytesToSignedInt(const char bytes[4]) {
  int result = bytes[3];
  for (int i = 2; i >= 0; --i) {
    result <<= 8;
    result += bytes[i];
  }
  return result;
}

void Parser::parseColorPallete() {
  if (m_picture.getBitsPerPixel() == 8) {
    std::vector<Color> colors{};
    uint32_t currentColor = 54;
    for (uint32_t i = 0; i < m_picture.getNumOfColors(); ++i) {
      colors.emplace_back(Color(m_data[currentColor], m_data[currentColor + 1],
                                m_data[currentColor + 2]));
      currentColor += 4;
    }
    m_picture.setColors(colors);
  }
}

void Parser::parseBitmapArray() {
  uint32_t height = m_picture.getBitMapHeight();
  uint32_t width = m_picture.getBitMapWidth();
  uint32_t index = m_picture.getPixelArrayAddress();
  if (m_picture.getBitsPerPixel() == 24) {
    matrix::Mat red(height, width);
    matrix::Mat green(height, width);
    matrix::Mat blue(height, width);
    uint32_t padding = width % 4;
    for (int i = height - 1; i >= 0; --i) {
      for (uint32_t j = 0; j < width; ++j) {
        red.setValue(i, j, m_data[index]);
        green.setValue(i, j, m_data[index + 1]);
        blue.setValue(i, j, m_data[index + 2]);
        index += 3;
      }
      index += padding;
    }
    m_picture.setBitmapArray(red, green, blue);
  } else {
    uint32_t padding = width % 4;
    matrix::Mat pixels(height, width);
    for (int i = height - 1; i >= 0; --i) {
      for (uint32_t j = 0; j < width; ++j) {
        char colorNum = m_data[index];
        pixels.setValue(i, j, colorNum);
        ++index;
      }
      index += padding;
    }
    m_picture.setBitmapArray(pixels);
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

double Color::getRed() const { return m_red; }

double Color::getGreen() const { return m_green; }

double Color::getBlue() const { return m_blue; }

Color Color::toGray() const {
  char val = std::round(0.2126 * static_cast<uint8_t>(m_red) +
                        0.7152 * static_cast<uint8_t>(m_green) +
                        0.0722 * static_cast<uint8_t>(m_blue));
  return Color(val, val, val);
}

bool Color::isEqual(const Color &other) const {
  return m_red == other.m_red && m_green == other.m_green &&
         m_blue == other.m_blue;
}
} // namespace bmp_parser