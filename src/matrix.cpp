#include "matrix.h"

#include "ErrorCode.h"
#include "Matrix.h"
#include "exceptions.h"

#include <iostream>
#include <memory>
#include <utility>

namespace matrix {
matrix::matrix() { m_matrix = nullptr; }

matrix::matrix(const uint32_t &height, const uint32_t &width) {
  ErrorCode code = matrix_create(&m_matrix, height, width);
  if (!error_isSuccess(code)) {
    throw exceptions::ErrorCodesException(code);
  }
}

matrix::matrix(const matrix &other) {
  if (other.m_matrix == nullptr) {
    m_matrix = nullptr;
  } else {
    ErrorCode code = matrix_copy(&m_matrix, other.m_matrix);
    if (!error_isSuccess(code)) {
      throw exceptions::ErrorCodesException(code);
    }
  }
}

matrix &matrix::operator=(const matrix &other) {
  if (this == &other) {
    return *this;
  }
  if (other.m_matrix == nullptr) {
    matrix_destroy(m_matrix);
    this->m_matrix = nullptr;
  } else {
    matrix_destroy(m_matrix);

    ErrorCode code = matrix_copy(&m_matrix, other.m_matrix);
    if (!error_isSuccess(code)) {
      throw exceptions::ErrorCodesException(code);
    }
  }
  return *this;
}

matrix::matrix(matrix &&other) noexcept {
  if (other.m_matrix == nullptr) {
    m_matrix = nullptr;
  } else {
    m_matrix = std::exchange(other.m_matrix, nullptr);
  }
}

matrix &matrix::operator=(matrix &&other) noexcept {
  if (this == &other) {
    return *this;
  }
  matrix_destroy(this->m_matrix);
  m_matrix = std::exchange(other.m_matrix, nullptr);
  return *this;
}

matrix::~matrix() { matrix_destroy(this->m_matrix); }

uint32_t matrix::getHeight() const {
  uint32_t result;
  ErrorCode code = matrix_getHeight(m_matrix, &result);
  if (!error_isSuccess(code)) {
    throw exceptions::ErrorCodesException(code);
  }
  return result;
}

uint32_t matrix::getWidth() const {
  uint32_t result;
  ErrorCode code = matrix_getWidth(m_matrix, &result);
  if (!error_isSuccess(code)) {
    throw exceptions::ErrorCodesException(code);
  }
  return result;
}

void matrix::setValue(const uint32_t &rowIndex, const uint32_t &colIndex,
                      const double &value) {
  ErrorCode code = matrix_setValue(m_matrix, rowIndex, colIndex, value);
  if (!error_isSuccess(code)) {
    throw exceptions::ErrorCodesException(code);
  }
}

matrix matrix::operator+(const matrix &other) const {
  matrix mat(getHeight(), getWidth());
  ErrorCode code = matrix_add(&mat.m_matrix, m_matrix, other.m_matrix);
  if (!error_isSuccess(code)) {
    throw exceptions::ErrorCodesException(code);
  }
  return mat;
}

matrix matrix::operator*(const matrix &other) const {
  matrix mat(getHeight(), getWidth());
  ErrorCode code =
      matrix_multiplyMatrices(&mat.m_matrix, m_matrix, other.m_matrix);
  if (!error_isSuccess(code)) {
    throw exceptions::ErrorCodesException(code);
  }
  return mat;
}

matrix matrix::operator*(const double &scalar) const {
  matrix mat(*this);
  ErrorCode code = matrix_multiplyWithScalar(mat.m_matrix, scalar);
  if (!error_isSuccess(code)) {
    throw exceptions::ErrorCodesException(code);
  }
  return mat;
}

double matrix::operator()(const uint32_t &rowIndex,
                          const uint32_t &colIndex) const {
  double result;
  ErrorCode code = matrix_getValue(m_matrix, rowIndex, colIndex, &result);
  if (!error_isSuccess(code)) {
    throw exceptions::ErrorCodesException(code);
  }
  return result;
}

matrix operator*(const double &scalar, const matrix &mat) {
  return mat * scalar;
}
} // namespace matrix