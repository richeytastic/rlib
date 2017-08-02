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
