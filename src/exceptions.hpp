#pragma once

#include "ErrorCode.h"
#include "Matrix.h"

#include <exception>

namespace exceptions {
class ErrorCodesException : public std::exception {
  ErrorCode code;

public:
  /**
   * @brief Construct a new Error Codes Exception object using a given ErrorCode
   *
   * @param code the given ErrorCode that is thrown
   */
  ErrorCodesException(const ErrorCode code);

  /**
   * @brief gets the error message
   *
   * @return const char* the error message
   */
  const char *what() const noexcept override;
};
} // namespace exceptions