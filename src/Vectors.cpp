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

#include "Vectors.h"
using rlib::PosVector;
using rlib::Rotation;



/**
 * Get the angle of a right angled triangle with opp and adj provided.
 * The resulting angle is always in the range [0,2pi).
 */
double rlib::getTheta( double opp, double adj)
{
   if ( opp == 0.0 && adj == 0.0)
      return -DBL_MAX;

   double hyp = sqrt(pow(opp,2) + pow(adj,2));

   double theta = asin(opp/hyp); // Assumes quadrant 1
   if ( adj < 0.0)   // Test for quadrant 2/3
      theta = M_PI - theta;   // For quadrant 3, double negation makes angle = pi + theta
   else if ( theta < 0.0)  // Test for quadrant 4
      theta = M_PI*2 + theta;

   return theta;
}  // end getTheta



PosVector::PosVector() : x(0), y(0), z(0)
{}



PosVector::PosVector( double *arr) : x(arr[0]), y(arr[1]), z(arr[2])
{}



PosVector::PosVector( double mx, double my, double mz) : x(mx), y(my), z(mz)
{}



PosVector::PosVector( const PosVector &p) : x(p.x), y(p.y), z(p.z)
{}



const PosVector& PosVector::operator=( const PosVector &p)
{
   x = p.x;
   y = p.y;
   z = p.z;
   return *this;
}  // end operator=



bool PosVector::operator==( const PosVector &p) const
{
   return ((x==p.x) && (y==p.y) && (z==p.y));
}  // end operator==



bool PosVector::operator!=( const PosVector &p) const
{
   return !operator==( p);
}  // end operator!=



PosVector PosVector::operator*( double fac) const
{
   return PosVector( fac*x, fac*y, fac*z);
}  // end operator*



PosVector PosVector::operator/( double fac) const
{
   return operator*(1.0/fac);
}  // end operator/



PosVector PosVector::operator+( const PosVector &p) const
{
   return PosVector( x + p.x, y + p.y, z + p.z);
}  // end operator+



PosVector PosVector::operator-( const PosVector &p) const
{
   return operator+( -p);
}  // end operator-



PosVector PosVector::operator-() const
{
   return PosVector( -x, -y, -z);
}  // end operator-



const PosVector& PosVector::operator*=( double fac)
{
   x *= fac;
   y *= fac;
   z *= fac;
   return *this;
}  // end operator*=



const PosVector& PosVector::operator/=( double fac)
{
   x /= fac;
   y /= fac;
   z /= fac;
   return *this;
}  // end operator/=



const PosVector& PosVector::operator+=( const PosVector &p)
{
   x += p.x;
   y += p.y;
   z += p.z;
   return *this;
}  // end operator+=



const PosVector& PosVector::operator-=( const PosVector &p)
{
   x -= p.x;
   y -= p.y;
   z -= p.z;
   return *this;
}  // end operator-=



PosVector PosVector::getNormalised() const
{
   double m = getMagnitude();
   return PosVector( x/m, y/m, z/m);
}  // end getNormalised



Rotation PosVector::getAngles() const
{
   double x = getTheta( z, y);
   double y = getTheta( x, z);
   double z = getTheta( y, x);
   Rotation r = {x,y,z};
   return r;
}  // end getAngles



Rotation PosVector::getRotationsFromUnitX() const
{
   double z = getTheta( y, x);
   PosVector v = *this;
   v.rotateZ( -z);   // Rotate v into XZ plane
   // Get Y rotation needed to rotate <1,0,0> into v as it lies now in XZ plane
   double y = getTheta( v.x, v.z) - M_PI/2;
   Rotation r = {0.0, y, z};
   return r;
}  // end getRotationsFromUnitX



void PosVector::rotateX( double t)
{
   if ( t == 0.0)
      return;

   double i = x;
   double j = y;
   double k = z;

   x = i;
   y = j*cos(t)-k*sin(t);
   z = j*sin(t)+k*cos(t);
}  // end rotateX



void PosVector::rotateY( double t)
{
   if ( t == 0.0)
      return;

   double i = x;
   double j = y;
   double k = z;

   x = i*cos(t)+k*sin(t);
   y = j;
   z = k*cos(t)-i*sin(t);
}  // end rotateY



void PosVector::rotateZ( double t)
{
   if ( t == 0.0)
      return;

   double i = x;
   double j = y;
   double k = z;

   x = i*cos(t)-j*sin(t);
   y = i*sin(t)+j*cos(t);
   z = k;
}  // end rotateZ



PosVector rlib::operator*( double fac, const PosVector &v)
{
	return v.operator*(fac);
}	// end operator*



PosVector rlib::operator/( double fac, const PosVector &v)
{
	return v.operator/(fac);
}	// end operator/



double rlib::dot( const PosVector &p, const PosVector &q)
{
	return p.getX() * q.getX() + p.getY() * q.getY() + p.getZ() * q.getZ();
}	// end dot



PosVector rlib::cross( const PosVector &p, const PosVector &q)
{
	PosVector i(1,0,0);
	PosVector j(0,1,0);
	PosVector k(0,0,1);
	return i*(p.getY()*q.getZ() - p.getZ()*q.getY())
			- j*(p.getX()*q.getZ() - p.getZ()*q.getX())
			+ k*(p.getX()*q.getY() - p.getY()*q.getX());
}	// end cross



ostream &rlib::operator<<( ostream &stream, const PosVector &pv)
{
    if ( stream.good())
        stream << pv.getX() << " " << pv.getY() << " " << pv.getZ();
    return stream;
}  // end operator<<



istream &rlib::operator>>( istream &stream, PosVector &pv)
{
    if ( stream.good())
        stream >> pv.x >> pv.y >> pv.z;
    return stream;
}  // end operator>>



Vector3d rlib::getAngles( const Vector3d &v)
{
    PosVector pv( v(0), v(1), v(2));
    Rotation r( pv.getAngles());
    return Vector3d( r.tx, r.ty, r.tz);
}   // end getAngles



Vector3d rlib::getRotationsFromUnitX( const Vector3d &v)
{
    PosVector pv( v(0), v(1), v(2));
    Rotation r( pv.getRotationsFromUnitX());
    return Vector3d( r.tx, r.ty, r.tz);
}   // end getRotationsFromUnitX



void rlib::rotateX( Vector3d &v, double rads)
{
    PosVector pv( v(0), v(1), v(2));
    pv.rotateX( rads);
    v << pv.X(), pv.Y(), pv.Z();
}   // end rotateX


void rlib::rotateY( Vector3d &v, double rads)
{
    PosVector pv( v(0), v(1), v(2));
    pv.rotateY( rads);
    v << pv.X(), pv.Y(), pv.Z();
}   // end rotateY


void rlib::rotateZ( Vector3d &v, double rads)
{
    PosVector pv( v(0), v(1), v(2));
    pv.rotateZ( rads);
    v << pv.X(), pv.Y(), pv.Z();
}   // end rotateZ
