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

namespace bmp {
class BMP {
private:
  // header members
  char m_magic[2]; // supposed to be 'BM'
  uint32_t m_bmpFileSize;
  uint32_t m_pixelArrayAddress;
  // DIB header members
  uint32_t m_headerSize; // supposed to be 40
  int m_bitmapWidth;
  int m_bitmapHeight;
  char m_constant[2];                      // must be 1
  char m_bitsPerPixel[2];                  // supposed to be 8 or 24
  uint32_t m_compression;                  // supposed to be 0
  uint32_t m_bitmapSizeWithoutCompression; // supposed to be 0
  uint32_t m_numOfColors;
  // color pallete members
  std::map<char, Color> m_colors;
  // bitmap array
  matrix::Mat m_red;
  matrix::Mat m_green;
  matrix::Mat m_blue;

public:
  /**
   * @brief Receives a path to a BMP image on the disk and rotates it 90 degrees
   * clockwise, writing the resulting image to the disk.
   *
   * @param imagePath Path of a BMP image that should be rotated. The path might
   * be invalid or contain a non-BMP file.
   * @param outputPath Path of the resulting BMP image. can be assumed to
   *  reside in a valid directory, however, cannot be assumed to exist. If the
   *  path already exists, the file previously existing in the path should be
   *  overriden.
   */
  void rotate_image(const std::string &imagePath,
                    const std::string &outputPath);

  /**
   * @brief Receives a path to a BMP image on the disk and converts it to
   * grayscale, writing the resulting image to the disk.
   *
   * @param imagePath Path of a BMP image that should be rotated.
   * @param outputPath Path of the resulting BMP image.
   */
  void convert_to_grayscale(const std::string &imagePath,
                            const std::string &outputPath);

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
  void setHeaderSize(const uint32_t &headerSize);

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
  setBitmapSizeWithoutCompression(const uint32_t &bitmapSizeWithoutCompression);

  /**
   * @brief Set the Num Of Colors member
   *
   * @param numOfColors the new numOfColors
   */
  void setNumOfColors(const uint32_t &numOfColors);

  // color pallete setters

  /**
   * @brief Set the Colors member
   *
   * @param colors the new colors
   */
  void setColors(const std::map<char, Color> &colors);

  // bitmap array setters

  /**
   * @brief Set the Bitmap Array member
   *
   * @param red the new red
   * @param green the new green
   * @param blue the new blue
   */
  void setBitmapArray(const matrix::Mat &red, const matrix::Mat &green,
                      const matrix::Mat &blue);

  /**
   * @brief Get the Bits Per Pixel member
   *
   * @return const int the Bits Per Pixel member
   */
  const int getBitsPerPixel();

  /**
   * @brief Get the Num Of Colors member
   *
   * @return const uint32_t the Num Of Colors member
   */
  const uint32_t getNumOfColors();

  /**
   * @brief Get the Pixel Array Address member
   *
   * @return const uint32_t the Pixel Array Address member
   */
  const uint32_t getPixelArrayAddress();

  /**
   * @brief Get the Bit Map Width member
   *
   * @return const uint32_t the Bit Map Width member
   */
  const uint32_t getBitMapWidth();

  /**
   * @brief Get the Bit Map Height member
   *
   * @return const uint32_t the Bit Map Height member
   */
  const uint32_t getBitMapHeight();

  /**
   * @brief Get the Colors member
   *
   * @return const std::map<char, Color>& the Colors member
   */
  const std::map<char, Color> &getColors();
};

class Parser {
private:
  std::unique_ptr<BMP> m_picture;
  std::vector<char> m_data;

  // bytes to int

  /**
   * @brief turn 4 chars that represent an unsigned integer to unsigned integer
   *
   * @param bytes the array of the chars
   * @return uint32_t the represented unsigned int
   */
  uint32_t bytesToUnsignedInt(const char bytes[4]);

  /**
   * @brief turn 4 chars that represent an signed integer to signed integer
   *
   * @param bytes the array of the chars
   * @return int the represented signed int
   */
  int bytesToSignedInt(const char bytes[4]);

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
   * @brief parse the num of colors part in the DIB header
   *
   */
  void parseNumOfColors();

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
  BMP &getPicture();
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
  double getRed();

  /**
   * @brief Get the Green value
   *
   * @return double the Green value
   */
  double getGreen();

  /**
   * @brief Get the Blue value
   *
   * @return double the Blue value
   */
  double getBlue();
};
} // namespace bmp