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
extern rlib_EXPORT std::string asString( bool v);

// Given a string of case insensitive "false" or "0", convert to boolean false, else true.
extern rlib_EXPORT bool asBool( const std::string& str);

extern rlib_EXPORT bool asBool( std::istream& is);


template <typename T>
T cnv( std::istream& is);


template <typename T>
T cnv( const std::string& s);


template <typename T>
T cnv( const char* txt);


#include "template/Convert_template.h"

}   // end rlib

#endif
