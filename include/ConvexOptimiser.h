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

/**
 * Efficiently finds the global minimum of a convex function defined
 * in an overridden class. Will not work if overridden operator() function
 * is not a convex function and d(x) is not its derivative.
 *
 * Richard Palmer
 * April 2012
 */

#pragma once
#ifndef RLIB_CONVEX_OPTIMISER
#define RLIB_CONVEX_OPTIMISER

#include "rlib_Export.h"

namespace rlib
{

class rlib_EXPORT ConvexOptimiser
{
public:
    virtual double operator()( double x) const = 0;
    virtual double d( double x) const = 0;

    // Find the x that minimises the function.
    double minimise( double precision = 0.00001) const;

    // Use after calling minimum() to return number of iterations
    // required to find the global minimum of the function.
    inline int iterations() const { return i;}

private:
    mutable int i;  // For counting iterations
    void findDomain( double&, double&) const;
};  // end class

}   // end namespace

#endif
