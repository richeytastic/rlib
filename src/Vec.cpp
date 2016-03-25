#include <Vec.h>
using namespace rlib;

#include <cmath>


double rlib::degToRad( double degs)
{
   return degs * M_PI / 180.0;
}  // end degToRad


double rlib::radToDeg( double rads)
{
   return rads * 180.0 / M_PI;
}  // end radToDeg
