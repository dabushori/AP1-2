# Assignment Two - C++ Matrix and BMP
## Yorai Roth Hazan - 213251861
## Ori Dabush - 212945760
* * *
### In this assignment we created:
* Mat.cpp + Mat.h - a matrix class in cpp.
* exceptions.cpp + exceptions.h - throwing exceptions.
* bmp.cpp + bmp.h - parsing BMP pictures
* * *
## Mat (Matrix) class is doing the following functions:
### The only member is a Matrix (from the first assignment)
* Constructor
* Copy constructor
* Copy assignment operator
* Move Constructor
* Move assignment operator
* Destructor
* Get height and width
* Set value
* Add another matrix
* Multiply the matrix with another matrix
* Multiply the matrix by scalar
* Operator (rowIndex, colIndex) - get the value in the matrix
### We used The libmatrix.so to create most of the functions
* * *
## ErrorCodesException class:
### The only member is an ErrorCode
* Exception that is dealing with the ErrorCode errors in the Matrix section.
* * *
## BMPException class:
### The only member is a string
* Exception that is dealing with message errors in the BMP section.
* * *
## BMP class is doing the following functions:
* rotating the BMP picture 90 degrees clockwise.
* converting the BMP picture to gray scale one.
* setters to all the members in the class.
* getters to some of the members.
* * *
### BMP has a lot of members (for each line in the table) and we parse all of them into a BMP member in Parser.
### If The BMP format was diffrent we would have changed the members of the BMP class and then the Parser methods that parse them.
### If the photo format was diffrent we would have done it the same way as if it was a diffrent BMP (change fileds and parse methods)
* * *
## Parser class is doing the following functions:
* bytesToUnsignedInt - convert 4 bytes to unsigned int.
* bytesToSignedInt - convert 4 bytes to signed int.
* parseHeader - parsing Header of the picture. (with this private methods)
  * parseMagic - parse the magic.
  * parseBmpFileSize - parse the size of the BMP file.
  * parseReserved - parse the reserved.
  * parsePixelArrayAddress - parse the offset of the pixel array in bytes.
* parseDIBHeader - parsing DIBHeader of the picture. (with this private methods)
  * parseHeaderSize - parse the size of the DIBheader. (must be 40)
  * parseBitmapWidth - parse the width of the bitmap.
  * parseBitmapHeight - parse the height of the bitmap.
  * parseConstant - parse the constant. (must be 1)
  * parseBitsPerPixel - parse the bits per pizel (8 or 24)
  * parseCompression - parse the compression (must be 0)
  * parseBitmapSizeWithoutCompression - parse the bit map size without compression. (might be 0)
  * parseResolution - parse the revolution. (width and height)
  * parseNumOfColors - parse the number of colors. 
  * parseNumOfImportantColors - parse the number of important colors.
* parseColorPallete - parse the color pallete. (only for 8 bits per pixel)
* parseBitmapArray - parse the bitmap array. (only for 24 bits per pixel)
* getPicture - get the picture that was parsed.
* * *
## Color class:
### This class is used to help us with the BMP/PARSER classes.
* Has three members (chars): m_red, m_green, m_blue.
* Has a constructor.
* Has getters to the members.
* * *
## Tests
* Tested the Matrix part with tests that we made.
* Tested the code with tests that we got from our fellow students.
* Tested the BMP with the "woman" that you gave us.
* Tested the BMP with a couple more photos that we created.
* * *
# "c++ is the best because it warms our heart and not our computers" - The God Of Programming - 2016
## Inspiration - https://www.youtube.com/watch?v=dQw4w9WgXcQ
