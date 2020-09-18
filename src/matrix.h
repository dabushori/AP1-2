#pragma once

#include "Matrix.h"
#include "exceptions.h"

#include <stdint.h>
#include <utility>

namespace matrix {
class matrix {
private:
  Matrix *m_matrix;

public:
  /**
   * @brief Construct a new matrix object
   *
   */
  matrix();

  /**
   * @brief Construct a new matrix object with size height x width
   *
   * @param height the height of the matrix
   * @param width the width of the matrix
   */
  matrix(const uint32_t &height, const uint32_t &width);

  /**
   * @brief copy constructor
   *
   * @param other the other matrix object that is being copied
   */
  matrix(const matrix &other);

  /**
   * @brief copy assignment operator
   *
   * @param other the other matrix object that is being assigned
   * @return matrix& the new matrix object that was created
   */
  matrix &operator=(const matrix &other);

  /**
   * @brief move constructor
   *
   * @param other the other matrix object that is being moved
   */
  matrix(matrix &&other) noexcept;

  /**
   * @brief move assignment operator
   *
   * @param other the other matrix object that is being assigned
   * @return matrix& the new matrix object that was created
   */
  matrix &operator=(matrix &&other) noexcept;

  /**
   * @brief Destroy the matrix object
   *
   */
  ~matrix();

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
  void setValue(const uint32_t &rowIndex, const uint32_t &colIndex,
                const double &value);

  /**
   * @brief add the current matrix and a given matrix
   *
   * @param other the given matrix
   * @return matrix the result of the addition
   */
  matrix operator+(const matrix &othr) const;

  /**
   * @brief multiply the current matrix and a given matrix
   *
   * @param other the given matrix
   * @return matrix the result of the multiplication
   */
  matrix operator*(const matrix &other) const;

  /**
   * @brief multiply the current matrix by a given scalar
   *
   * @param scalar the given scalar
   * @return matrix the result of the multiplication
   */
  matrix operator*(const double &scalar) const;

  /**
   * @brief get the value (by value) in the rowIndex,colIndex cell of the
   * current matrix
   *
   * @param rowIndex the row index of the wanted cell
   * @param colIndex the collumn index of the wanted cell
   * @return double the value that is in the cell
   */
  double operator()(const uint32_t &rowIndex, const uint32_t &colIndex) const;
};

/**
 * @brief a * operator to the other side of the multiplication by a scalar
 *
 * @param scalar the scalar
 * @param mat the matrix
 * @return matrix the new matrix
 */
matrix operator*(const double &scalar, const matrix &mat);
} // namespace matrix