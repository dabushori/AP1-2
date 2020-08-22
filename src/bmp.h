#pragma once

#include <fstream>
#include <iostream>
#include <iterator>
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
  std::vector<int> m_colors;
  // bitmap array
  int getPixel(uint32_t i, uint32_t j);

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
  void setMagic(const char magic[2]); // supposed to be 'BM'
  void setBmpFileSize(const uint32_t &bmpFileSize);
  void setPixelArrayAddress(const uint32_t &pixelArrayAddress);
  // DIB header setters
  void setHeaderSize(const uint32_t &headerSize); // supposed to be 40
  void setBitMapWidth(const int &bitmapWidth);
  void setBitMapHeight(const int &bitmapHeight);
  void setConstant(const char constant[2]);         // must be 1
  void setBitPerPixel(const char bitsPerPixel[2]);  // supposed to be 8 or 24
  void setCompression(const uint32_t &compression); // supposed to be 0
  void setBitmapSizeWithoutCompression(
      const uint32_t &bitmapSizeWithoutCompression); // supposed to be 0
  void setNumOfColors(const uint32_t &numOfColors);
  // color pallete setters
  void setColors(const std::vector<int> &colors);
};

class Parser {
private:
  std::unique_ptr<BMP> m_picture;
  std::vector<char> m_data;
  void parseHeader();
  void parseDIBHeader();
  void parseColorPallete();
  void parseBitmapArray();

public:
  Parser(const std::string &filename);
  BMP &getPicture();
};
} // namespace bmp