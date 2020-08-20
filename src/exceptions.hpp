#include "ErrorCode.h"
#include "Matrix.h"

#include <exception>

namespace exceptions {
class ErrorCodesException : public std::exception {
  ErrorCode code;

public:
  ErrorCodesException(const ErrorCode code);
  const char *what() const noexcept override;
};
}; // namespace exceptions