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

#pragma once
#ifndef RLIB_NEWTON_RAPHSON_H
#define RLIB_NEWTON_RAPHSON_H

#include "rlib_Export.h"

namespace rlib
{

// A function object and its first derivative
class rlib_EXPORT Function
{
public:
    virtual double operator()( double x) const = 0;
    virtual double d( double x) const = 0;
};  // end class


class rlib_EXPORT NewtonRaphson
{
public:
    NewtonRaphson( const Function&);

    // Find the root of the given function to dps decimal places.
    // startx: value to start optimisation at
    double operator()( int dps, double startx=0) const;

private:
    const Function& _f;
};  // end class

}   // end namespace

#endif
