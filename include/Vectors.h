/**
 * Some basic angle and vector operations.
 *
 * Richard Palmer
 * June 2011
 */

#pragma once
#ifndef RLIB_VECTORS_H
#define RLIB_VECTORS_H

#include "rlib_Export.h"
#include <cmath>
#include <cfloat>
#include <istream>
#include <ostream>
using std::ostream;
using std::istream;

#include <Eigen/Dense>
using Eigen::Vector3d;


namespace rlib
{
/**
 * Get the angle of a right angled triangle with opp and adj provided.
 * The resulting angle is always in the range [0,2pi). If opp and adj
 * are both zero, the result is undefined and the returned value is less than zero.
 */
extern rlib_EXPORT double getTheta( double opp, double adj);



typedef struct rlib_EXPORT Rotation
{
    double tx;  // Theta about X axis
    double ty;  // Theta about Y axis
    double tz;  // Theta about Z axis
    void convertToDegrees() { tx*=180/M_PI; ty*=180/M_PI; tz*=180/M_PI;}
    void convertToRadians() { tx*=M_PI/180; ty*=M_PI/180; tz*=M_PI/180;}
} Rotation;



class rlib_EXPORT PosVector
{
public:
    PosVector();
    PosVector( double x, double y, double z);
    PosVector( double *arr);	// Array of three doubles
    PosVector( const PosVector &p);  // Copy
    const PosVector& operator=( const PosVector &p);   // Assignment

    inline double X() const { return x;}
    inline double Y() const { return y;}
    inline double Z() const { return z;}

    inline double getX() const { return x;}
    inline double getY() const { return y;}
    inline double getZ() const { return z;}

    inline double getMagnitude() const { return sqrt(pow(x,2)+pow(y,2)+pow(z,2));}
    inline double getMagnitudeXY() const { return sqrt(pow(x,2)+pow(y,2));}
    inline double getMagnitudeXZ() const { return sqrt(pow(x,2)+pow(z,2));}
    inline double getMagnitudeYZ() const { return sqrt(pow(y,2)+pow(z,2));}

    bool operator==( const PosVector &v) const;
    bool operator!=( const PosVector &v) const;
    PosVector operator*( double fac) const;
    PosVector operator/( double fac) const;
    PosVector operator+( const PosVector &v) const;
    PosVector operator-( const PosVector &v) const;
    PosVector operator-() const;  // Unary
    const PosVector& operator*=( double fac);
    const PosVector& operator/=( double fac);
    const PosVector& operator+=( const PosVector &v);
    const PosVector& operator-=( const PosVector &v);

    PosVector getNormalised() const;

    /**
    * Get the X, Y and Z angles the provided vector u makes with each axis. These
    * angles are always in the range [0,2pi). Where an angle is undefined, its value will be < 0.
    */
    Rotation getAngles() const;

    /**
    * Get the Y then the Z rotations needed to rotate the <1,0,0> vector to be coincident with this vector.
    * Angles are always in the range [0,2pi). The X rotation is to be ignored.
    */
    Rotation getRotationsFromUnitX() const;

    void rotateX( double rads);
    void rotateY( double rads);
    void rotateZ( double rads);

    friend istream &operator>>( istream &is, PosVector &pv);

private:
    double x;
    double y;
    double z;
}; // end class


// Formatted output/input as a line of 3 doubles (X Y Z)
ostream &operator<<( ostream &os, const PosVector &pv);
istream &operator>>( istream &is, PosVector &pv);

PosVector operator*( double fac, const PosVector &v);
PosVector operator/( double fac, const PosVector &v);
double dot( const PosVector &p, const PosVector &q);
PosVector cross( const PosVector &p, const PosVector &q);

Vector3d getAngles( const Vector3d &v);
Vector3d getRotationsFromUnitX( const Vector3d &v);
void rotateX( Vector3d &v, double rads);
void rotateY( Vector3d &v, double rads);
void rotateZ( Vector3d &v, double rads);

}  // end namespace

#endif
