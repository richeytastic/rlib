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


