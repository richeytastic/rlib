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
