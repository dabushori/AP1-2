#pragma once

#include "Mat.h"
#include "exceptions.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace bmp_parser {
class Color;

class BMP {
private:
  // header members
  char m_magic[2]; // supposed to be 'BM'
  uint32_t m_bmpFileSize;
  // addresses 6-9**********
  char m_reserved[4];
  uint32_t m_pixelArrayAddress;
  // DIB header members
  char m_headerSize[4]; // supposed to be 40
  int m_bitmapWidth;
  int m_bitmapHeight;
  char m_constant[2];     // must be 1
  char m_bitsPerPixel[2]; // supposed to be 8 or 24
  uint32_t m_compression; // supposed to be 0
  char m_bitmapSizeWithoutCompression[4];
  // addresses 38-43**********
  char m_resolution[8];
  uint32_t m_numOfColors;
  // addresses 50-53**********
  char m_numberOfImportantColors[4];
  // color pallete members
  std::map<char, Color> m_colors;
  // bitmap array
  matrix::Mat m_red;
  matrix::Mat m_green;
  matrix::Mat m_blue;
  matrix::Mat m_pixels;

  /**
   * @brief turn a color into gray with the given formula
   *
   * @param red the red value of the color
   * @param green the green value of the color
   * @param blue the blue value of the color
   * @return double the value of the gray color that we get (the red, green and
   * blue values)
   */
  double toGray(const double red, const double green, const double blue) const;

public:
  /**
   * @brief rotate the current image 90 degrees clockwise
   *
   * @return BMP the new rotated image
   */
  BMP rotateImage() const;

  /**
   * @brief convert the current image into gray scale colored
   *
   * @return BMP the new gray scale colored image
   */
  BMP convertToGrayScale() const;

  /**
   * @brief write the current image to the given file
   *
   * @param outputFile the given file
   */
  void writeToFile(const std::string &outputFile) const;

  // header setters

  /**
   * @brief Set the Magic member
   *
   * @param magic the new magic
   */
  void setMagic(const char magic[2]);

  /**
   * @brief Set the Bmp File Size member
   *
   * @param bmpFileSize the new bmpFileSize
   */
  void setBmpFileSize(const uint32_t &bmpFileSize);

  /**
   * @brief Set the Reserved member
   *
   * @param reserved the new reserved
   */
  void setReserved(const char reserved[4]);

  /**
   * @brief Set the Pixel Array Address member
   *
   * @param pixelArrayAddress the new pixelArrayAddress
   */
  void setPixelArrayAddress(const uint32_t &pixelArrayAddress);

  // DIB header setters

  /**
   * @brief Set the Header Size member
   *
   * @param headerSize the new headerSize
   */
  void setHeaderSize(const char headerSize[4]);

  /**
   * @brief Set the Bit Map Width member
   *
   * @param bitmapWidth the new bitmapWidth
   */
  void setBitMapWidth(const int &bitmapWidth);

  /**
   * @brief Set the Bit Map Height member
   *
   * @param bitmapHeight the new bitmapHeight
   */
  void setBitMapHeight(const int &bitmapHeight);

  /**
   * @brief Set the Constant member
   *
   * @param constant the new constant
   */
  void setConstant(const char constant[2]);

  /**
   * @brief Set the Bits Per Pixel member
   *
   * @param bitsPerPixel the new bitsPerPixel
   */
  void setBitsPerPixel(const char bitsPerPixel[2]);

  void setBitsPerPixel(const int &bitsPerPixel);

  /**
   * @brief Set the Compression member
   *
   * @param compression the new compression
   */
  void setCompression(const uint32_t &compression);

  /**
   * @brief Set the Bitmap Size Without Compression member
   *
   * @param bitmapSizeWithoutCompression the new bitmapSizeWithoutCompression
   */
  void
  setBitmapSizeWithoutCompression(const char bitmapSizeWithoutCompression[4]);

  /**
   * @brief Set the Resolution member
   *
   * @param resolution the new resolution
   */
  void setResolution(const char resolution[8]);

  /**
   * @brief Set the Num Of Colors member
   *
   * @param numOfColors the new numOfColors
   */
  void setNumOfColors(const uint32_t &numOfColors);

  /**
   * @brief Set the Num Of Important Colors member
   *
   * @param numOfImportantColors the new numOfImportantColors
   */
  void setNumOfImportantColors(const char numOfImportantColors[4]);

  // color pallete setters

  /**
   * @brief Set the Colors member
   *
   * @param colors the new colors
   */
  void setColors(const std::map<char, Color> &colors);

  // bitmap array setters

  /**
   * @brief Set the Bitmap Array member in the case of 24 bits per pixel
   *
   * @param red the new red member
   * @param green the new green member
   * @param blue the new blue member
   */
  void setBitmapArray(const matrix::Mat &red, const matrix::Mat &green,
                      const matrix::Mat &blue);

  /**
   * @brief Set the Bitmap Array member in the case of 8 bits per pixel
   *
   * @param pixels the new pixels member
   */
  void setBitmapArray(const matrix::Mat &pixels);

  /**
   * @brief Get the Bits Per Pixel member
   *
   * @return int the Bits Per Pixel member
   */
  int getBitsPerPixel() const;

  /**
   * @brief Get the Num Of Colors member
   *
   * @return uint32_t the Num Of Colors member
   */
  uint32_t getNumOfColors() const;

  /**
   * @brief Get the Pixel Array Address member
   *
   * @return uint32_t the Pixel Array Address member
   */
  uint32_t getPixelArrayAddress() const;

  /**
   * @brief Get the Bit Map Width member
   *
   * @return uint32_t the Bit Map Width member
   */
  uint32_t getBitMapWidth() const;

  /**
   * @brief Get the Bit Map Height member
   *
   * @return uint32_t the Bit Map Height member
   */
  uint32_t getBitMapHeight() const;

  /**
   * @brief Get the Colors member
   *
   * @return const std::map<char, Color>& the Colors member
   */
  std::map<char, Color> &getColors();
};

class Parser {
private:
  // std::unique_ptr<BMP> m_picture;
  BMP m_picture;
  std::vector<char> m_data;

  // bytes to int

  /**
   * @brief turn 4 chars that represent an unsigned integer to unsigned integer
   *
   * @param bytes the array of the chars
   * @return uint32_t the represented unsigned int
   */
  uint32_t bytesToUnsignedInt(const char bytes[4]) const;

  /**
   * @brief turn 4 chars that represent an signed integer to signed integer
   *
   * @param bytes the array of the chars
   * @return int the represented signed int
   */
  int bytesToSignedInt(const char bytes[4]) const;

  // header

  /**
   * @brief parse the header part of the BMP file
   *
   */
  void parseHeader();

  /**
   * @brief parse the magic part in the header
   *
   */
  void parseMagic();

  /**
   * @brief parse the BMP file size part in the header
   *
   */
  void parseBmpFileSize();

  /**
   * @brief parse the reserved part in the header
   *
   */
  void parseReserved();

  /**
   * @brief parse the pixel array address part in the header
   *
   */
  void parsePixelArrayAddress();

  // DIB header

  /**
   * @brief parse the DIB header part of the BMP file
   *
   */
  void parseDIBHeader();

  /**
   * @brief parse the header size part in the DIB header
   *
   */
  void parseHeaderSize();

  /**
   * @brief parse the bitmap width part in the DIB header
   *
   */
  void parseBitmapWidth();

  /**
   * @brief parse the bitmap height part in the DIB header
   *
   */
  void parseBitmapHeight();

  /**
   * @brief parse the bitmap width part in the DIB header
   *
   */
  void parseConstant();

  /**
   * @brief parse the bits per pixel part in the DIB header
   *
   */
  void parseBitsPerPixel();

  /**
   * @brief parse the compression part in the DIB header
   *
   */
  void parseCompression();

  /**
   * @brief parse the bitmap size without compression part in the DIB header
   *
   */
  void parseBitmapSizeWithoutCompression();

  /**
   * @brief parse the resolution part in the DIB header
   *
   */
  void parseResolution();

  /**
   * @brief parse the num of colors part in the DIB header
   *
   */
  void parseNumOfColors();

  /**
   * @brief parse the num of imporatant colors part in the DIB header
   *
   */
  void parseNumOfImportantColors();

  // color pallete

  /**
   * @brief parse the color pallete part of the BMP file
   *
   */
  void parseColorPallete();

  // bitmap array

  /**
   * @brief parse the bitmap array part of the BMP file
   *
   */
  void parseBitmapArray();

public:
  /**
   * @brief Construct a new Parser object
   *
   * @param filename the name of the file to be parsed
   */
  Parser(const std::string &filename);

  /**
   * @brief Get the picture that was parsed
   *
   * @return BMP& the picture that was parsed
   */
  BMP getPicture() const;
};

class Color {
private:
  char m_red;
  char m_green;
  char m_blue;

public:
  /**
   * @brief Construct a new Color object
   *
   */
  Color();

  /**
   * @brief Construct a new Color object
   *
   * @param red the red value of this color
   * @param green the green value of this color
   * @param blue the blue value of this color
   */
  Color(char red, char green, char blue);

  /**
   * @brief Get the Red value
   *
   * @return double the Red value
   */
  double getRed() const;

  /**
   * @brief Get the Green value
   *
   * @return double the Green value
   */
  double getGreen() const;

  /**
   * @brief Get the Blue value
   *
   * @return double the Blue value
   */
  double getBlue() const;

  /**
   * @brief convert the current color into a gray scale color
   *
   * @return Color the new gray scale colored
   */
  Color toGray() const;

  /**
   * @brief check if the cureent color is equal to the given color
   *
   * @param other the given color
   * @return true if they are equal
   * @return false otherwise
   */
  bool isEqual(const Color &other) const;
};
} // namespace bmp_parser