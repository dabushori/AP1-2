#pragma once

#include "Matrix.h"
#include "exceptions.h"

#include <stdint.h>
#include <utility>

namespace matrix {
class Mat {
private:
  Matrix *m_matrix;

public:
  /**
   * @brief Construct a new Mat object
   *
   */
  Mat();

  /**
   * @brief Construct a new Mat object with size height x width
   *
   * @param height the height of the matrix
   * @param width the width of the matrix
   */
  Mat(const uint32_t height, const uint32_t width);

  /**
   * @brief copy constructor
   *
   * @param other the other Mat object that is being copied
   */
  Mat(const Mat &other);

  /**
   * @brief copy assignment operator
   *
   * @param other the other Mat object that is being assigned
   * @return Mat& the new Mat object that was created
   */
  Mat &operator=(const Mat &other);

  /**
   * @brief move constructor
   *
   * @param other the other Mat object that is being moved
   */
  Mat(Mat &&other) noexcept;

  /**
   * @brief move assignment operator
   *
   * @param other the other Mat object that is being assigned
   * @return Mat& the new Mat object that was created
   */
  Mat &operator=(Mat &&other) noexcept;

  /**
   * @brief Destroy the Mat object
   *
   */
  ~Mat();

  /**
   * @brief Get the height of the matrix
   *
   * @return uint32_t the height of the matrix
   */
  uint32_t getHeight() const;

  /**
   * @brief Get the width of the matrix
   *
   * @return uint32_t the width of the matrix
   */
  uint32_t getWidth() const;

  /**
   * @brief Set the value of the cell in location i,j
   *
   * @param rowIndex the row index of the cell
   * @param colIndex the collumn index of the cell
   * @param value the value that is being set
   */
  void setValue(const uint32_t rowIndex, const uint32_t colIndex,
                const double value);

  /**
   * @brief add the current matrix and a given matrix
   *
   * @param other the given matrix
   * @return Mat the result of the addition
   */
  Mat add(const Mat &other) const;

  /**
   * @brief multiply the current matrix and a given matrix
   *
   * @param other the given matrix
   * @return Mat the result of the multiplication
   */
  Mat multiplyMatrices(const Mat &other) const;

  /**
   * @brief multiply the current matrix by a given scalar
   *
   * @param scalar the given scalar
   * @return Mat the result of the multiplication
   */
  Mat multiplyByScalar(const double scalar) const;

  /**
   * @brief get the value (by value) in the rowIndex,colIndex cell of the
   * current matrix
   *
   * @param rowIndex the row index of the wanted cell
   * @param colIndex the collumn index of the wanted cell
   * @return double the value that is in the cell
   */
  double operator()(const uint32_t rowIndex, const uint32_t colIndex) const;

  /**
   * @brief rotate the matrix 90 degrees clockwise.
   *
   * @param matrix the matrix we want to rotate
   * @return Mat the rotated matrix
   */
  Mat rotate90Degrees() const;
};
} // namespace matrix