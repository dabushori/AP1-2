#pragma once

#include "exceptions.h"
#include "matrix.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#define MAGIC_SIZE 2
#define BMP_FILE_SIZE_SIZE 4
#define RESERVED_SIZE 4
#define PIXEL_ARRAY_ADDRESS_SIZE 4
#define HEADER_SIZE 4
#define BITMAP_WIDTH_SIZE 4
#define BITMAP_HEIGHT_SIZE 4
#define CONSTANT_SIZE 2
#define BITS_PER_PIXEL_SIZE 2
#define COMPRESSION_SIZE 4
#define BITMAP_SIZE_WITHOUT_COMPRESSION_SIZE 4
#define RESOLUTION_SIZE 8
#define NUM_OF_COLORS_SIZE 4
#define NUMBER_OF_IMPORTANT_COLORS_SIZE 4

namespace bmp_parser {
class Color;

class BMP {
private:
  // header members
  char m_magic[MAGIC_SIZE]; // supposed to be 'BM'
  char m_bmpFileSize[BMP_FILE_SIZE_SIZE];
  char m_reserved[RESERVED_SIZE];
  char m_pixelArrayAddress[PIXEL_ARRAY_ADDRESS_SIZE];
  // DIB header members
  char m_headerSize[HEADER_SIZE]; // supposed to be 40
  char m_bitmapWidth[BITMAP_WIDTH_SIZE];
  char m_bitmapHeight[BITMAP_HEIGHT_SIZE];
  char m_constant[CONSTANT_SIZE];           // must be 1
  char m_bitsPerPixel[BITS_PER_PIXEL_SIZE]; // supposed to be 8 or 24
  char m_compression[COMPRESSION_SIZE];     // supposed to be 0
  char m_bitmapSizeWithoutCompression[BITMAP_SIZE_WITHOUT_COMPRESSION_SIZE];
  char m_resolution[RESOLUTION_SIZE];
  char m_numOfColors[NUM_OF_COLORS_SIZE];
  char m_numberOfImportantColors[NUMBER_OF_IMPORTANT_COLORS_SIZE];
  // color pallete members
  std::vector<Color> m_colors;
  // bitmap array 8 bits per pixel
  matrix::matrix m_pixels;
  // bitmap array 24 bits per pixel
  matrix::matrix m_red;
  matrix::matrix m_green;
  matrix::matrix m_blue;

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
  void setMagic(const char magic[MAGIC_SIZE]);

  /**
   * @brief Set the Bmp File Size member
   *
   * @param bmpFileSize the new bmpFileSize as a char array
   */
  void setBmpFileSize(const char bmpFileSize[BMP_FILE_SIZE_SIZE]);

  /**
   * @brief Set the Bmp File Size member
   *
   * @param size the new bmpFileSize as an integer
   */
  void setBmpFileSize(const int &size);

  /**
   * @brief Set the Reserved member
   *
   * @param reserved the new reserved
   */
  void setReserved(const char reserved[RESERVED_SIZE]);

  /**
   * @brief Set the Pixel Array Address member
   *
   * @param pixelArrayAddress the new pixelArrayAddress as a char array
   */
  void
  setPixelArrayAddress(const char pixelArrayAddress[PIXEL_ARRAY_ADDRESS_SIZE]);

  /**
   * @brief Set the Pixel Array Address member
   *
   * @param address the new pixelArrayAddress as an integer
   */
  void setPixelArrayAddress(const int &address);

  // DIB header setters

  /**
   * @brief Set the Header Size member
   *
   * @param headerSize the new headerSize
   */
  void setHeaderSize(const char headerSize[HEADER_SIZE]);

  /**
   * @brief Set the Bit Map Width member
   *
   * @param bitmapWidth the new bitmapWidth
   */
  void setBitMapWidth(const char bitmapWidth[BITMAP_WIDTH_SIZE]);

  /**
   * @brief Set the Bit Map Height member
   *
   * @param bitmapHeight the new bitmapHeight
   */
  void setBitMapHeight(const char bitmapHeight[BITMAP_HEIGHT_SIZE]);

  /**
   * @brief Set the Constant member
   *
   * @param constant the new constant
   */
  void setConstant(const char constant[CONSTANT_SIZE]);

  /**
   * @brief Set the Bits Per Pixel member
   *
   * @param bitsPerPixel the new bitsPerPixel as a char array
   */
  void setBitsPerPixel(const char bitsPerPixel[BITS_PER_PIXEL_SIZE]);

  /**
   * @brief Set the Bits Per Pixel member
   *
   * @param bitsPerPixel the new bitsPerPixel as an integer
   */
  void setBitsPerPixel(const int &bitsPerPixel);

  /**
   * @brief Set the Compression member
   *
   * @param compression the new compression
   */
  void setCompression(const char compression[COMPRESSION_SIZE]);

  /**
   * @brief Set the Bitmap Size Without Compression member
   *
   * @param bitmapSizeWithoutCompression the new bitmapSizeWithoutCompression
   */
  void setBitmapSizeWithoutCompression(
      const char
          bitmapSizeWithoutCompression[BITMAP_SIZE_WITHOUT_COMPRESSION_SIZE]);

  /**
   * @brief Set the Resolution member
   *
   * @param resolution the new resolution
   */
  void setResolution(const char resolution[RESOLUTION_SIZE]);

  /**
   * @brief Set the Num Of Colors member
   *
   * @param numOfColors the new numOfColors as a char array
   */
  void setNumOfColors(const char numOfColors[NUM_OF_COLORS_SIZE]);

  /**
   * @brief Set the Num Of Colors member
   *
   * @param numOfColor the new numOfColors as a size_t
   */
  void setNumOfColors(const size_t &numOfColor);

  /**
   * @brief Set the Num Of Important Colors member
   *
   * @param numOfImportantColors the new numOfImportantColors
   */
  void setNumOfImportantColors(
      const char numOfImportantColors[NUMBER_OF_IMPORTANT_COLORS_SIZE]);

  // color pallete setters

  /**
   * @brief Set the Colors member
   *
   * @param colors the new colors
   */
  void setColors(const std::vector<Color> &colors);

  // bitmap array setters

  /**
   * @brief Set the Bitmap Array member in the case of 24 bits per pixel
   *
   * @param red the new red member
   * @param green the new green member
   * @param blue the new blue member
   */
  void setBitmapArray(const matrix::matrix &red, const matrix::matrix &green,
                      const matrix::matrix &blue);

  /**
   * @brief Set the Bitmap Array member in the case of 8 bits per pixel
   *
   * @param pixels the new pixels member
   */
  void setBitmapArray(const matrix::matrix &pixels);

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
  std::vector<Color> &getColors();
};

class Parser {
private:
  BMP m_picture;
  std::vector<char> m_data;

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

// some help functions

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
  Color(const char &red, const char &green, const char &blue);

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
  bool operator==(const Color &other) const;
};
} // namespace bmp_parser