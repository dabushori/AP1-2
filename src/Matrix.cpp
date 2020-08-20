#include "Matrix.h"

class Mat {
private:
    Matrix* m_matrix;
public:
    Mat(CPMatrix matrix) {
        ErrorCode code = matrix_copy(&m_matrix, matrix);
        if (!error_isSuccess(code)) {
        throw "constructor fail";
        }
    }

    Mat(const uint32_t height, const uint32_t width) {
        ErrorCode code = matrix_create(&m_matrix, height, width);
        if (!error_isSuccess(code)) {
        throw "constructor fail";
        }
    }

    ~Mat() {
        matrix_destroy(m_matrix);
    }
};