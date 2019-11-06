/************************************************************************
 * Copyright (C) 2018 Richard Palmer
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

#ifndef RLIB_MATH_UTIL_H
#define RLIB_MATH_UTIL_H

#include "NewtonRaphson.h"
#include <cstddef>
#include <vector>

using DP = double;
using Vec_DP = std::vector<double>;


namespace rlib {

// Given arrays xa and ya of the same length where ya[i] = f(xa[i]), interpolate to find and return f(x).
// On return, dy is the error estimate. This function taken from "Numerical Recipies in C++" 2nd edition, p113.
rlib_EXPORT DP polint( const Vec_DP& xa, const Vec_DP& ya, DP x, DP& dy);

rlib_EXPORT DP round( DP v, size_t nd);

}   // end namespace

#endif
