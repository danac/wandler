#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

namespace Exceptions {

    class EndOfWork: public std::exception
    {
      virtual const char* what() const throw()
      {
        return "The producer is shutting down";
      }
    };

}


#endif // EXCEPTIONS_H
