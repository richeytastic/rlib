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
#include <RenderedObject.h>
using namespace rlib;

#include<string>
using std::string;


class CubeRObj : public RenderedObject
{
public:
   CubeRObj( string id_string, double boxSize) : id( id_string), BOX_SIZE( boxSize) {}
   virtual ~CubeRObj(){}

   string getId() const { return id;}
   double sideLength() const { return BOX_SIZE;}

   // inherited member functions
   void render( GLuint *textId) const;
   GLuint createDisplayList( uint numIds, GLuint *textId) const;

private:
   CubeRObj( const CubeRObj &inCube) {} // prevent copy calls
   CubeRObj &operator=( const CubeRObj &copyCube){ return *this;} // prevent assignment

   string id;
   double BOX_SIZE;  // length of cube sides
}; // end class CubeRObj
