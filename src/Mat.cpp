#include "Mat.hpp"
#include "Matrix.h"

namespace matrix {
Mat::Mat(const uint32_t height, const uint32_t width) {
  ErrorCode code = matrix_create(&this->m_matrix, height, width);
  if (!error_isSuccess(code)) {
    throw exceptions::ErrorCodesException(code);
  }
}

Mat::Mat(const Mat &other) {
  ErrorCode code = matrix_copy(&this->m_matrix, other.m_matrix);
  if (!error_isSuccess(code)) {
    throw exceptions::ErrorCodesException(code);
  }
}

Mat &Mat::operator=(const Mat &other) {
  if (this == &other) {
    return *this;
  }
  matrix_destroy(m_matrix);
  m_matrix = other.m_matrix;
  return *this;
}

Mat::Mat(Mat &&other) noexcept {
  m_matrix = std::exchange(other.m_matrix, nullptr);
}

Mat &Mat::operator=(Mat &&other) noexcept {
  if (this == &other) {
    return *this;
  }
  matrix_destroy(this->m_matrix);
  m_matrix = std::exchange(other.m_matrix, nullptr);
  return *this;
}

Mat::~Mat() { matrix_destroy(this->m_matrix); }

uint32_t Mat::getHeight() const {
  uint32_t result;
  ErrorCode code = matrix_getHeight(m_matrix, &result);
  if (!error_isSuccess(code)) {
    throw exceptions::ErrorCodesException(code);
  }
  return result;
}

uint32_t Mat::getWidth() const {
  uint32_t result;
  ErrorCode code = matrix_getWidth(m_matrix, &result);
  if (!error_isSuccess(code)) {
    throw exceptions::ErrorCodesException(code);
  }
  return result;
}

void Mat::setValue(const uint32_t rowIndex, const uint32_t colIndex,
                   const double value) {
  ErrorCode code = matrix_setValue(m_matrix, rowIndex, colIndex, value);
  if (!error_isSuccess(code)) {
    throw exceptions::ErrorCodesException(code);
  }
}

Mat &Mat::add(const Mat &other) const {
  Mat matrix(getHeight(), getWidth());
  ErrorCode code = matrix_add(&matrix.m_matrix, m_matrix, other.m_matrix);
  if (!error_isSuccess(code)) {
    throw exceptions::ErrorCodesException(code);
  }
  return matrix;
}

Mat &Mat::multiplyMatrices(const Mat &other) const {
  Mat matrix(getHeight(), getWidth());
  ErrorCode code =
      matrix_multiplyMatrices(&matrix.m_matrix, m_matrix, other.m_matrix);
  if (!error_isSuccess(code)) {
    throw exceptions::ErrorCodesException(code);
  }
  return matrix;
}

Mat &Mat::multiplyByScalar(const double scalar) const {
  Mat matrix(*this);
  ErrorCode code = matrix_multiplyWithScalar(matrix.m_matrix, scalar);
  if (!error_isSuccess(code)) {
    throw exceptions::ErrorCodesException(code);
  }
  return matrix;
}

double Mat::operator()(const uint32_t rowIndex, const uint32_t colIndex) const {
  double result;
  ErrorCode code = matrix_getValue(m_matrix, rowIndex, colIndex, &result);
  if (!error_isSuccess(code)) {
    throw exceptions::ErrorCodesException(code);
  }
  return result;
}
} // namespace matrix