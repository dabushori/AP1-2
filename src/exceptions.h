#pragma once

#include "ErrorCode.h"
#include <exception>
#include <string.h>
#include <string>

namespace exceptions {
class ErrorCodesException : public std::exception {
  ErrorCode m_code;

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

class BMPException : public std::exception {
  std::string m_message;

public:
  /**
   * @brief Construct a new BMP Exception object using a given string
   *
   * @param message the given string that is thrown
   */
  BMPException(const std::string &message);

  /**
   * @brief gets the error message
   *
   * @return const char* the error message
   */
  const char *what() const noexcept override;
};
} // namespace exceptions