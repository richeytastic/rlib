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
