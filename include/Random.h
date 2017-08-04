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
