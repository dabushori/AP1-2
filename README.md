# Assignment Two - C++ Matrix and BMP
## Yorai Roth Hazan - 213251861
## Ori Dabush - 212945760
* * *
### In this assignment we created:
* Mat.cpp + Mat.h - a matrix class in cpp.
* exceptions.cpp + exceptions.h - throwing exceptions.
* bmp.cpp + bmp.h - parsing BMP pictures.
* bmp_tester.cpp - with the given bmp_tester.hpp file.
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
* Operator (rowIndex, colIndex) - get the value in the matrix.
* rotate90Degrees - return a matrix after rotating this matrix.
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
* writeToFile - write the photo into a BMP file.
* setters to all the members in the class.
* getters to some of the members.
* toGray (private) - returns a color from a 3 given numbers. (rgb)
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
* Has a ToGray function - return a new color that is a grayscale of this color.
* Has an isEqual function - checks if this color and the given color are the same.
* * *
## bmp_tester.cpp
### This cpp file is testing if the code is working, we added two functions:
* isBMPFile - checks if the input file is a bmp file.
* isValidFile - checks if the file exists.
### In addition to that, we implemented the two functions:
* rotate_image - we checked if output and input files are bmp files and if the input file exists and then we rotated the image.
* convert_to_grayscale - we checked if output and input files are bmp files and if the input file exists and then we converted the image to grayscale.
* * *
## Tests
* Tested the Matrix part with tests that we made.
* Tested the code with tests that we got from our fellow students.
* Tested the BMP with the "woman" that you gave us.
* Tested the BMP with a couple more photos that we created.
* * *
# "c++ is the best because it warms our heart and not our computers" - The God Of Programming - 2016
## Inspiration - https://www.youtube.com/watch?v=dQw4w9WgXcQ
## Inspiration - https://www.youtube.com/watch?v=JkafqBj6dsk
Note: If you want us to give you good songs every excercise ler us know!!!