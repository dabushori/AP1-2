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

BMPException::BMPException(const std::string &message) { m_message = message; }

const char *BMPException::what() const noexcept { return m_message.data(); }
} // namespace exceptions