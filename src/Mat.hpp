#pragma once
#include <stdint.h>
#include <utility>
#include "Matrix.h"
#include "exceptions.hpp"
namespace matrix {
//Our matrix class
class Mat {
public:
    // constructor
    Mat(const uint32_t height, const uint32_t width);
    // copy constructor
    Mat(const Mat& other);
    // copy assignment operator
    Mat& operator=(const Mat& other);
    // Move Constructor
    Mat(Mat&& other) noexcept;
    // Move assignment operator
    Mat& operator=(Mat&& other) noexcept;
    // destructor
    ~Mat();
private:
    Matrix* m_matrix;

};
}