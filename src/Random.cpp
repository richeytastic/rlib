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

#include <Random.h>
#include <ctime>
#include <cstdlib>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/normal_distribution.hpp>
using rlib::Random;

Random::Random() : _rndGen( (unsigned int)time(NULL)) {}
Random::Random( int seed) : _rndGen(seed) {}


long int Random::getRandomInt()
{
    return boost::random::uniform_int_distribution<>(0, RAND_MAX-1)( _rndGen);
}   // end getRandomInt


double Random::getRandom()
{
    return double(getRandomInt())/RAND_MAX;
}   // end getRandom


double Random::sampleNormal( double mean, double stddev)
{
    return boost::random::normal_distribution<>( mean, stddev)( _rndGen);
}   // end sampleNormal


