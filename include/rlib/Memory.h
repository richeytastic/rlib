/************************************************************************
 * Copyright (C) 2019 Richard Palmer
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

#ifndef RLIB_MEMORY_H
#define RLIB_MEMORY_H

#include "rlib_Export.h"
#include <cstdlib>
#include <cstdint>

#ifdef _WIN32
using u_int64_t = uint_least64_t;
#endif

namespace rlib {

/**
 * Returns the size of physical memory (RAM) in bytes.
 */
rlib_EXPORT u_int64_t getMemorySize();


/**
 * Returns maximum so far resident set size (physical memory use) in
 * bytes or zero if the value cannot be determined for this OS.
 */
rlib_EXPORT u_int64_t getPeakRSS();

/**
 * Returns the current resident set size (physical memory use in
 * bytes or zero if the value cannot be determined for this OS.
 */
rlib_EXPORT u_int64_t getCurrentRSS();

}	// end namespace

#endif
