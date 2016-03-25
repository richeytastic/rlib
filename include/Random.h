#pragma once
#ifndef RLIB_RANDOM_H
#define RLIB_RANDOM_H

#include "rlib_Export.h"
#include <cstdlib>
#include <ctime>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/normal_distribution.hpp>


namespace rlib
{

class rlib_EXPORT Random
{
public:
    Random();
    explicit Random( int seed);

    // Get a random number in the half open interval [0, RAND_MAX)
    long int getRandomInt() const;

    // Get a random number in the half open interval [0, 1)
    double getRandom() const;

    // Get a random number from the normal distribution with given params.
    double sampleNormal( double mean, double stddev) const;

private:
    mutable boost::random::mt19937 _rndGen;
};  // end class

}   // end namespace

#endif
