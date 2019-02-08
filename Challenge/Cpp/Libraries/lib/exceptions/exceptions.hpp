#ifndef EXCEPTIONS_H

#include <exception>

namespace LJP
{
  namespace Exceptions
  {
    struct IndexArrayException : public std::exception
    {
    private:
      const char *error_log;

    public:
      IndexArrayException(const char *error_log) : error_log((char *)error_log) {}
      IndexArrayException() : error_log("IndexArrayException") {}
      char const *what() const throw()
      {
        return error_log;
      }
    };
    struct NotImplementedException : public std::exception
    {
    private:
      const char *error_log;

    public:
      NotImplementedException(const char *error_log) : error_log((char *)error_log) {}
      NotImplementedException() : error_log("NotImplementedException") {}
      char const *what() const throw()
      {
        return error_log;
      }
    };
  } // namespace Exceptions
} // namespace LJP

#endif