// Exceptions library for librlib.
// Richard Palmer
// 25 June 2007

//#pragma once
#ifndef RLIB_EXCEPTIONS_H
#define RLIB_EXCEPTIONS_H

#include "rlib_Export.h"
#include <exception>
#include <string>
using std::string;

namespace rlib
{

class rlib_EXPORT Exception : public std::exception
{
public:
    Exception( const string &err);
    virtual ~Exception() throw();
    virtual const char* what() const throw();
    virtual string error() const throw();
    virtual string errStr() const throw();
private:
    string m_err;
}; // end class


class rlib_EXPORT InvalidVectorException : public Exception
{
public:
    InvalidVectorException( const string &es);
}; // end class rlib_EXPORT InvalidVectorException


class rlib_EXPORT IOException : public Exception
{
public:
    IOException( const string &es);
}; // end class rlib_EXPORT IOException


class rlib_EXPORT OutOfBoundsException: public Exception
{
public:
    OutOfBoundsException( const string &es);
};  // end class rlib_EXPORT OutOfBoundsException


class rlib_EXPORT OverflowException: public Exception
{
public:
    OverflowException( const string &es);
};  // end class rlib_EXPORT OverflowException


class rlib_EXPORT OutOfMemoryException: public Exception
{
public:
    OutOfMemoryException( const string &es);
};  // end class rlib_EXPORT OutOfMemoryException


class rlib_EXPORT ArithmeticException : public Exception
{
public:
    ArithmeticException( const string &es);
}; // end class rlib_EXPORT ArithmeticException


class rlib_EXPORT TimeException : public Exception
{
public:
    TimeException( const string &es);
}; // end class rlib_EXPORT TimeException


class rlib_EXPORT VersionException : public Exception
{
public:
    VersionException( const string &es);
};  // end class rlib_EXPORT VersionException


class rlib_EXPORT CorruptionException : public Exception
{
public:
    CorruptionException( const string &es);
};  // end class rlib_EXPORT CorruptionException


class rlib_EXPORT JsonException : public Exception
{
public:
    JsonException( const string &es);
};  // end class rlib_EXPORT JsonException


class rlib_EXPORT ParseException : public Exception
{
public:
    ParseException( const string &es);
};  // end class rlib_EXPORT ParseException


class rlib_EXPORT SegmentException : public Exception
{
public:
    SegmentException( const string &es);
}; // end class rlib_EXPORT SegmentException


class rlib_EXPORT CompressException : public Exception
{
public:
    CompressException( const string &es);
}; // end class rlib_EXPORT CompressException


class rlib_EXPORT InvalidImageException : public Exception
{
public:
    InvalidImageException( const string &es);
}; // end class rlib_EXPORT InvalidImageException


class rlib_EXPORT PointCloudException : public Exception
{
public:
    PointCloudException( const string &es);
}; // end class rlib_EXPORT PointCloudException


}  // end namespace rlib


#endif
