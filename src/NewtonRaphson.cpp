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

#include "NewtonRaphson.h"
using rlib::Function;
using rlib::NewtonRaphson;
#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <iostream>


NewtonRaphson::NewtonRaphson( const Function& f) : _f(f) {}


double NewtonRaphson::operator()( int dps, double startx) const
{
    long ldps = dps;
    double x, y, d, oldx;
    double xdiff = DBL_MAX;
    double smallDiff;
    long ndps;
    x = startx;
    int i = 0;
    do
    {
        smallDiff = xdiff;
        i++;
        y = _f(x);
        d = _f.d(x);
        //std::cerr << "f(" << x << ") = " << y << ", df = " << d << std::endl;

        oldx = x;
        x = x - y/d;
        xdiff = fabs(x-oldx);
        ndps = abs(long(log10(xdiff)));
    } while (ndps < ldps && xdiff < smallDiff);

    if ( xdiff >= smallDiff)
    {
        //std::cerr << "Warning: BREAKING OPTIMISATION" << std::endl;
        x = (x + oldx)/2;
    }   // end if
    //std::cerr << "Achieved optimisation to " << ndps << " decimal places after " << i << " iterations" << std::endl;

    return x;
}   // end operator()
