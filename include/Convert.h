#pragma once
#ifndef RLIB_CONVERT_H
#define RLIB_CONVERT_H

#include "rlib_Export.h"
#include <string>
#include <iostream>
#include <algorithm>

namespace rlib
{

// Returns "FALSE" if !v else "TRUE"
rlib_EXPORT std::string asString( bool v);

// Given a string of case insensitive "false" or "0", convert to boolean false, else true.
rlib_EXPORT bool asBool( const std::string& str);

rlib_EXPORT bool asBool( std::istream& is);


template <typename T>
rlib_EXPORT T cnv( std::istream& is)
{
    T v;
    is >> v;
    return v;
}   // end cnv


template <typename T>
rlib_EXPORT T cnv( const std::string& s)
{
    std::istringstream iss(s);
    return cnv<T>(iss);
}   // end cnv


template <typename T>
rlib_EXPORT T cnv( const char* txt)
{
    std::istringstream iss(txt);
    return cnv<T>(iss);
}   // end cnv

}   // end rlib

#endif
