#include <CubeRObj.h>
using namespace rlib;


void CubeRObj::render( GLuint *textId) const
{
   glBegin( GL_QUADS);

   // Top face
   glColor3f( 1.0f, 1.0f, 0.0f);
   glNormal3f( 0.0f, 1.0f, 0.0f);
   glVertex3f( -BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
   glVertex3f( BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
   glVertex3f( BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
   glVertex3f( -BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);

   // Bottom face
   glColor3f( 1.0f, 0.0f, 1.0f);
   glNormal3f( 0.0f, -1.0f, 0.0f);
   glVertex3f( -BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
   glVertex3f( BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
   glVertex3f( BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
   glVertex3f( -BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);

   // Left face
   glNormal3f( -1.0f, 0.0f, 0.0f);
   glColor3f( 0.0f, 1.0f, 0.0f);
   glVertex3f( -BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
   glVertex3f( -BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
   glColor3f( 0.5f, 0.0f, 0.5f);
   glVertex3f( -BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
   glVertex3f( -BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);

   // Right face
   glNormal3f( 1.0f, 0.0f, 0.0f);
   glColor3f( 1.0f, 0.0f, 0.0f);
   glVertex3f( BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
   glVertex3f( BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
   glColor3f( 0.0f, 0.0f, 1.0f);
   glVertex3f( BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
   glVertex3f( BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);

   glEnd();

   if ( textId != 0)
   {
      glEnable( GL_TEXTURE_2D);
      glBindTexture( GL_TEXTURE_2D, *textId);
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glColor3f( 1.0f, 1.0f, 1.0f); // Normally lit texture

      glBegin( GL_QUADS);

      // Front face
      glNormal3f( 0.0f, 0.0f, 1.0f);
      glTexCoord2f( 0.0f, 0.0f);
      glVertex3f( -BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
      glTexCoord2f( 1.0f, 0.0f);
      glVertex3f( BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
      glTexCoord2f( 1.0f, 1.0f);
      glVertex3f( BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
      glTexCoord2f( 0.0f, 1.0f);
      glVertex3f( -BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);

      // Back face
      glNormal3f( 0.0f, 0.0f, -1.0f);
      glTexCoord2f( 0.0f, 0.0f);
      glVertex3f( -BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
      glTexCoord2f( 1.0f, 0.0f);
      glVertex3f( -BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
      glTexCoord2f( 1.0f, 1.0f);
      glVertex3f( BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
      glTexCoord2f( 0.0f, 1.0f);
      glVertex3f( BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
   
   	glEnd();

      glDisable( GL_TEXTURE_2D);
   }  // end if - texture mapped
}  // end render


GLuint CubeRObj::createDisplayList( unsigned int numIds, GLuint *textId) const
{
   GLuint cubeDL = glGenLists( numIds);
   glNewList( cubeDL, GL_COMPILE);
   render( textId);
   glEndList();
   return cubeDL;
}  // end createDisplayList
