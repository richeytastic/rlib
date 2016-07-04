#pragma once
#include <GL/glut.h>

namespace rlib
{

class RenderedObject
{
public:
    virtual ~RenderedObject() {}
    virtual void render( GLuint *textId) const = 0;   // takes pointer to a texture
    virtual GLuint createDisplayList( unsigned int numIds, GLuint *textId) const = 0;
}; // end class RenderedObject

}  // end namespace rlib
