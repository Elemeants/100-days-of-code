#ifndef EXCEPTIONS_H

#include <exception>

struct IndexArrayException : public std::exception
{
    const char * what () const throw ()
    {
        return "IndexArrayException";
    }
};
struct NotImplementedException : public std::exception
{
    const char * what () const throw ()
    {
        return "NotImplementedException";
    }
};

#endif
