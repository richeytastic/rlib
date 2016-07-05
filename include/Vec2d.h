#pragma once

#include <iostream>
using std::ostream;
using std::istream;

#include <cmath>
using std::sqrt;

#include <cstdlib>
using std::abs;

#include <Exceptions.h>
#include <Vec.h>
using rlib::ArithmeticException;
using rlib::Vec;


namespace rlib
{
   class Vec2d : public Vec
	{
      friend istream &operator>>( istream &input, Vec2d &v);

	   public:
		Vec2d();
      Vec2d( int x, int y);
      Vec2d( unsigned int x, unsigned int y);
		Vec2d( double x, double y);
      Vec2d( const Vec2d &inVec);   // copy constructor
      const Vec2d &operator=( const Vec2d &inVec); // assignment
      virtual ~Vec2d(){}
		
    	double &operator[]( Axis a);   // for LHS (assignment)
   	double operator[]( Axis a) const;
		
   	const Vec2d operator*( double scale) const;   // scalar product
   	const Vec2d operator/( double scale) const;
   	const Vec2d operator+( const Vec2d &other) const;
   	const Vec2d operator-( const Vec2d &other) const;
   	const Vec2d operator-() const;   // unary
		
   	const Vec2d &operator*=( double scale);
   	const Vec2d &operator/=( double scale);
   	const Vec2d &operator+=( const Vec2d &other);
   	const Vec2d &operator-=( const Vec2d &other);

      bool operator==( const Vec2d &other);

      double manhatten() const;  // return the Manhatten length of this Vec2d		
   	virtual double magnitude() const;
   	virtual double magnitudeSquared() const;

   	Vec2d normalize() const;   // unit length vector
   	virtual double dot( const Vec2d &other) const;   // dot product
      virtual double angle( const Vec2d &other) const;   // angle other makes with this vector (radians)

		virtual double angle() const;	// Angle made from the origin vector <1,0>

	   private:
		double v[2];
   }; // end class Vec2d


   Vec2d operator*( double scale, const Vec2d &v);
   ostream &operator<<( ostream &output, const Vec2d &v);
   istream &operator>>( istream &input, Vec2d &v);

   Vec2d normalize( const Vec2d &v); // convenience
   double dot( const Vec2d &vecI, const Vec2d &VecII);   // convenience
   double angle( const Vec2d &vecI, const Vec2d &VecII);  // convenience (radians)
}  // end namespace rlib
