#include "Matrix.h"
#include "Mat.hpp"
namespace matrix {
    Mat::Mat(const uint32_t height, const uint32_t width) {
        ErrorCode code = matrix_create(&m_matrix, height, width);
        if (!error_isSuccess(code)) {
        throw exceptions::ErrorCodesException(code);
        }
    }
    Mat::Mat(const Mat& other) {
        ErrorCode code = matrix_copy(&m_matrix, other.m_matrix);
        if (!error_isSuccess(code)) {
        throw exceptions::ErrorCodesException(code);
        }
    }
    Mat& Mat::operator=(const Mat& other) {
        if (this == &other) {
		    return *this;
        }
	    delete m_matrix;
	    *this = Mat(other); 
	    return *this;
    }
    // Move Constructor
    Mat::Mat(Mat&& other) noexcept {
        m_matrix = std::exchange(other.m_matrix, nullptr);
    }
    // Move assignment operator
    Mat& Mat::operator=(Mat&& other) noexcept {
        if (this == &other) {
		return *this;
	    }
	    matrix_destroy(m_matrix);
	    m_matrix = std::exchange(other.m_matrix, nullptr);
	    return *this;
    }
    // destructor
    Mat::~Mat() {
        matrix_destroy(m_matrix);
    }
}