/************************************************************************
 * Copyright (C) 2017 Richard Palmer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ************************************************************************/

// Exceptions library for librlib.
// Richard Palmer
// 25 June 2007

#ifndef RLIB_EXCEPTIONS_H
#define RLIB_EXCEPTIONS_H

#include "rlib_Export.h"
#include <exception>
#include <string>

// Disable warnings about standard template library specialisations not being exported in the DLL interface
#ifdef _WIN32
#pragma warning( disable : 4251)
#pragma warning( disable : 4275)
#endif
/*
#ifdef _WIN32
class rlib_EXPORT std::exception;
template struct rlib_EXPORT std::_Simple_types<char>;
struct rlib_EXPORT std::_Container_base12;
template class rlib_EXPORT std::_String_val<std::_Simple_types<char> >;
template class rlib_EXPORT std::allocator<char>;
template struct rlib_EXPORT std::_Wrap_alloc<std::allocator<char> >;
template class rlib_EXPORT std::_Compressed_pair<std::_Wrap_alloc<std::allocator<char> >, std::_String_val<std::_Simple_types<char> >, true>;
template struct rlib_EXPORT std::char_traits<char>;
template class rlib_EXPORT std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
#endif
*/

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
