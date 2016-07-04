#pragma once
#ifndef RLIB_VEC_H
#define RLIB_VEC_H


namespace rlib
{
   class Vec
   {
      public:
         enum Axis { X = 0, Y = 1, Z = 2};
         virtual ~Vec(){}

         virtual double magnitude() const = 0;
         virtual double magnitudeSquared() const = 0;
   }; // end class Vec


   // simple conversion functions from radians/degrees to degrees/radians
   double degToRad( double degs);  // returns radians
   double radToDeg( double rads);  // returns degrees
}  // end namespace rlib

#endif
