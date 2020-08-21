#include "exceptions.h"

#include "ErrorCode.h"

#include <exception>

namespace exceptions {
ErrorCodesException::ErrorCodesException(const ErrorCode code) {
  m_code = code;
}

const char *ErrorCodesException::what() const noexcept {
  return error_getErrorMessage(m_code);
}
} // namespace exceptions