#ifndef RLIB_RANDOM_H
#define RLIB_RANDOM_H

#ifdef _WIN32
#pragma warning( disable : 4251)
#endif
#include "rlib_Export.h"
#include <boost/random/mersenne_twister.hpp>

namespace rlib
{

class rlib_EXPORT Random
{
public:
    Random();
    explicit Random( int seed); // Seed with same constant for repeatible sequences

    // Get a random number in the half open interval [0, RAND_MAX)
    long int getRandomInt();

    // Get a random number in the half open interval [0, 1)
    double getRandom();

    // Get a random number from the normal distribution with given params.
    double sampleNormal( double mean, double stddev);

private:
    boost::random::mt19937 _rndGen;
};  // end class

}   // end namespace

#endif
