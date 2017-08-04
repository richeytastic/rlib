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

#include <Model.h>
using namespace rlib;



Model::Model() : dl( 0)
{
}	// end Model::Model



Model::~Model()
{
	if ( dl != 0)
		glDeleteLists( dl, 1);
}	// end Model



void Model::draw() const
{
	if ( dl == 0)
	{
		dl = glGenLists( 1);
		glNewList( dl, GL_COMPILE);	// New display list
		drawModel();	// Create the model structure from the vector of triangles
		glEndList();	// end of display list
	}	// end if

	glCallList( dl);
}	// end Model::draw



void Model::drawModel() const
{
	bool texturing = false;

	for ( vector< Triangle>::const_iterator i = polys.begin(); i != polys.end(); ++i)
	{
		if ( !i->mat.texFile.empty())
		{
			if ( texturing == false)
			{
				glEnable( GL_TEXTURE_2D);
				texturing = true;
			}	// end if

			glBindTexture( GL_TEXTURE_2D, i->mat.texId);
		}	// end if

		glColor3f( i->mat.red, i->mat.green, i->mat.blue);

		glBegin( GL_TRIANGLES);

		glNormal3f( i->v[ 0].n.x, i->v[ 0].n.y, i->v[ 0].n.z);
		if ( i->mat.texId != 0)
			glTexCoord2f( i->v[ 0].tx, i->v[ 0].ty);
		glVertex3f( i->v[ 0].c.x, i->v[ 0].c.y, i->v[ 0].c.z);

		glNormal3f( i->v[ 1].n.x, i->v[ 1].n.y, i->v[ 1].n.z);
		if ( i->mat.texId != 0)
			glTexCoord2f( i->v[ 1].tx, i->v[ 1].ty);
		glVertex3f( i->v[ 1].c.x, i->v[ 1].c.y, i->v[ 1].c.z);

		glNormal3f( i->v[ 2].n.x, i->v[ 2].n.y, i->v[ 2].n.z);
		if ( i->mat.texId != 0)
			glTexCoord2f( i->v[ 2].tx, i->v[ 2].ty);
		glVertex3f( i->v[ 2].c.x, i->v[ 2].c.y, i->v[ 2].c.z);

		// glNormal3f( i->n.x, i->n.y, i->n.z);
		glEnd();
	}	// end for

	if ( texturing)
		glDisable( GL_TEXTURE_2D);
}	// end Model::drawModel
