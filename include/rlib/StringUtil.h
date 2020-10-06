/************************************************************************
 * Copyright (C) 2020 Richard Palmer
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

#ifndef RLIB_STRING_UTIL_H
#define RLIB_STRING_UTIL_H

#include "rlib_Export.h"
#include <string>

namespace rlib {

// Trim from left (in-place)
rlib_EXPORT void ltrim( std::string&);

// Trim from right (in-place)
rlib_EXPORT void rtrim( std::string&);

// Trim from left and right (in-place)
rlib_EXPORT void trim( std::string&);

// Return a left trimmed copy.
rlib_EXPORT std::string ltrim( const std::string&);

// Return a right trimmed copy.
rlib_EXPORT std::string rtrim( const std::string&);

// Return a left and right trimmed copy.
rlib_EXPORT std::string trim( const std::string&);

}   // end namespace

#endif
