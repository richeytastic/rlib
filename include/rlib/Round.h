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

#ifndef RLIB_ROUND_H
#define RLIB_ROUND_H

#include "rlib_Export.h"
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

namespace rlib {

// Round v away from zero for n decimal places.
double roundAway( double v, int n) { return long(pow(10,n)*v + copysign(0.5,v))*pow(10,-n);}

// Round v in a positive direction for n decimal places.
double roundUp( double v, int n) { return long(pow(10,n)*v + 0.5)*pow(10,-n);}

// Return v rounded to n decimal places as a string showing only n decimal places.
std::string dps( double v, int n)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(n) << roundAway(v,n);
    return oss.str();
}   // end dps

}   // end rlib

#endif
