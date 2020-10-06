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

#include <Vec2d.h>
using namespace rlib;


// friend function
istream &rlib::operator>>( istream &input, Vec2d &v)
{
   char ch; // syntax of a vector understood as "(x,y,z)"
   return input >> ch >> v[ Vec::X] >> ch >> v[ Vec::Y] >> ch;
}  // end operator>>


Vec2d::Vec2d()
{
   v[ Vec::X] = 0.0;
   v[ Vec::Y] = 0.0;
} // end default constructor


Vec2d::Vec2d( int x, int y)
{
   v[ Vec::X] = x;
   v[ Vec::Y] = y;
}  // end constructor


Vec2d::Vec2d( unsigned int x, unsigned int y)
{
   v[ Vec::X] = x;
   v[ Vec::Y] = y;
}  // end constructor


Vec2d::Vec2d( double x, double y)
{
   v[ Vec::X] = x;
   v[ Vec::Y] = y;
}  // end constructor


Vec2d::Vec2d( const Vec2d &inVec) : Vec( inVec)
{
   v[ Vec::X] = inVec[ Vec::X];
   v[ Vec::Y] = inVec[ Vec::Y];
}  // end constructor


const Vec2d &Vec2d::operator=( const Vec2d &inVec)
{
   v[ Vec::X] = inVec[ Vec::X];
   v[ Vec::Y] = inVec[ Vec::Y];

   return *this;
}  // end assignment


double &Vec2d::operator[]( Vec::Axis a)
{
   return v[ int( a)];
}  // end operator[] (LHS)


double Vec2d::operator[]( Vec::Axis a) const
{
   return v[ int( a)];
}  // end operator[]


const Vec2d Vec2d::operator*( double scale) const
{
   return Vec2d( v[ Vec::X] * scale, v[ Vec::Y] * scale);
}  // end scalar product


const Vec2d Vec2d::operator/( double scale) const
{
   if ( scale == 0.0f) throw ArithmeticException( "Division by zero");
   return operator*( double( 1) / scale);
}  // end scalar product (reciprocal)


const Vec2d Vec2d::operator+( const Vec2d &other) const
{
   return Vec2d( v[ Vec::X] + other.v[ Vec::X], v[ Vec::Y] + other.v[ Vec::Y]);
}  // end operator+


const Vec2d Vec2d::operator-( const Vec2d &other) const
{
   return Vec2d( v[ Vec::X] - other.v[ Vec::X], v[ Vec::Y] - other.v[ Vec::Y]);
}  // end operator-


const Vec2d Vec2d::operator-() const
{
   return Vec2d( -v[ Vec::X], -v[ Vec::Y]);
}  // end operator- (unary)


const Vec2d &Vec2d::operator*=( double scale)
{
   v[ Vec::X] *= scale;
   v[ Vec::Y] *= scale;
   return *this;
}  // end operator*=


const Vec2d &Vec2d::operator/=( double scale)
{
   if ( scale == 0.0f) throw ArithmeticException( "Division by zero");
   return *this *= ( double( 1) / scale);
}  // end operator/=


const Vec2d &Vec2d::operator+=( const Vec2d &other)
{
   v[ Vec::X] += other.v[ Vec::X];
   v[ Vec::Y] += other.v[ Vec::Y];
   return *this;
}  // end operator+=


const Vec2d &Vec2d::operator-=( const Vec2d &other)
{
   return *this += -other;
}  // end operator-=


bool Vec2d::operator==( const Vec2d &other)
{
   return (( v[ Vec::X] == other[ Vec::X]) && ( v[ Vec::Y] == other[ Vec::Y]));
}  // end operator==


double Vec2d::manhatten() const
{
   return abs( (*this)[ Vec::X]) + abs( (*this)[ Vec::Y]);
}  // end manhatten


double Vec2d::magnitude() const
{
   return sqrt( magnitudeSquared());
}  // end magnitude


double Vec2d::magnitudeSquared() const
{
   return v[ Vec::X] * v[ Vec::X] + v[ Vec::Y] * v[ Vec::Y];
}  // end magnitudeSquared


Vec2d Vec2d::normalize() const
{
   double mag = magnitude();

   if ( mag > 0)
      return *this / mag;

   return *this;  // return this if zero vector
}  // end normalize



double Vec2d::dot( const Vec2d &other) const
{
	return v[ Vec::X] * other[ Vec::X] + v[ Vec::Y] * other[ Vec::Y];
}  // end dot product



double Vec2d::angle( const Vec2d &other) const
{
	// Get the angle this vector makes with <1,0>
	double ang1 = 0;
	double thismag = magnitude();
	if ( thismag > 0)
		ang1 = acos( v[ Vec::X] / thismag);

	if ( v[ Vec::Y] < 0)	// If vector is in quadrant 3 or 4
		ang1 = 2 * M_PI - ang1;

	// Get the angle the other vector makes with <1,0>
	double ang2 = 0;
	double othermag = other.magnitude();
	if ( othermag > 0)
		ang2 = acos( other[ Vec::X] / othermag);

	if ( other[ Vec::Y] < 0)
		ang2 = 2 * M_PI - ang2;

	// Subtract the second angle from the first for return
	return ang1 - ang2;
}  // end angle



double Vec2d::angle() const
{
	// Get the angle this vector makes with <1,0>
	double ang = 0;
	double mag = magnitude();
	if ( mag > 0)
		ang = acos( v[ Vec::X] / mag);

	if ( v[ Vec::Y] < 0)	// If vector is in quadrant 3 or 4
		ang = 2 * M_PI - ang;

	return ang;
}	// end angle



Vec2d rlib::operator*( double scale, const Vec2d &v)
{
   return v * scale;
}  // end operator* (vector on RHS)


ostream &rlib::operator<<( ostream &output, const Vec2d &v)
{
   return output << '(' << v[ Vec::X] << ", " << v[ Vec::Y] << ')';
}  // end operator<<


/////////////////////////////////////////////
/********** CONVENIENCE FUNCTIONS **********/
/////////////////////////////////////////////

Vec2d rlib::normalize( const Vec2d &v)
{
   return v.normalize();
}  // end normalize


double rlib::dot( const Vec2d &vI, const Vec2d &vII)
{
   return vI.dot( vII);
}  // end dot product


double rlib::angle( const Vec2d &vI, const Vec2d &vII)
{
   return vI.angle( vII);
}  // end angle
