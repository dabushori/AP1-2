#include "exceptions.hpp"

#include "ErrorCode.h"
#include "Matrix.h"

#include <exception>

namespace exceptions {
ErrorCodesException::ErrorCodesException(const ErrorCode error) {
  this->code = error;
}

const char *ErrorCodesException::what() const noexcept {
  return error_getErrorMessage(code);
}
} // namespace exceptions