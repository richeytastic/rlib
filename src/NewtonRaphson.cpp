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
