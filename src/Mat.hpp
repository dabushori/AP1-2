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
    // get Height
    uint32_t getHeight() const;
    // get Width
    uint32_t getWidth() const;
    // set the value in i and j index
    void setValue(const uint32_t rowIndex, const uint32_t colIndex, const double value);
    // add matrix to this matrix
    Mat add(const Mat& other) const;
    // multiply another matrix with this matrix
    Mat multiplyMatrices(const Mat& other) const;
    // get the value in the rowIndex and the colIndex of the Mat
    double operator()(const uint32_t rowIndex, const uint32_t colIndex);
private:
    Matrix* m_matrix;
};
}