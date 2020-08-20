#include "exceptions.hpp"

#include "ErrorCode.h"
#include "Matrix.h"

#include <exception>

namespace exceptions {
ErrorCodesException::ErrorCodesException(const ErrorCode code) {
  this->code = code;
}

const char *ErrorCodesException::what() const noexcept {
  return error_getErrorMessage(code);
}
}; // namespace exceptions