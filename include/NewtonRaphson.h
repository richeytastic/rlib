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
