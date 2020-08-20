#include "ErrorCode.h"
#include "Matrix.h"
#include <exception>

namespace exceptions {
class ErrorCodesException : public std::exception {
  ErrorCode code;

public:
  ErrorCodesException(const ErrorCode code) { this->code = code; }

  const char *what() const noexcept override {
    return error_getErrorMessage(code);
  }
};
}; // namespace exceptions