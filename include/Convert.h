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

#ifndef RLIB_CONVERT_H
#define RLIB_CONVERT_H

#include "rlib_Export.h"
#include <string>
#include <iostream>
#include <algorithm>

namespace rlib {

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
