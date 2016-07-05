#include "Random.h"
using rlib::Random;

Random::Random() : _rndGen( (unsigned int)time(NULL)) {}
Random::Random( int seed) : _rndGen(seed) {}


long int Random::getRandomInt() const
{
    return boost::random::uniform_int_distribution<>(0, RAND_MAX-1)( _rndGen);
}   // end getRandomInt


double Random::getRandom() const
{
    return double(getRandomInt())/RAND_MAX;
}   // end getRandom


double Random::sampleNormal( double mean, double stddev) const
{
    return boost::random::normal_distribution<>( mean, stddev)( _rndGen);
}   // end sampleNormal
