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

#include <Scene.h>
using rlib::Scene;


Scene::Scene() : parent( NULL), obj( NULL)
{
}	// end Scene::Scene



Scene::~Scene()
{
	if ( obj != NULL)
		delete obj;

	while ( !sPtrs.empty())
	{
		delete sPtrs.back();
		sPtrs.pop_back();
	}	// end while
}	// end Scene::~Scene



void Scene::draw() const
{
	glPushMatrix();

	// Scale, rotate and translate according to the transform matrix for the obj->ct.
	float mVals[] = { transform.m[ 0].x, transform.m[ 0].y, transform.m[ 0].z, 0,
							transform.m[ 1].x, transform.m[ 1].y, transform.m[ 1].z, 0,
							transform.m[ 2].x, transform.m[ 2].y, transform.m[ 2].z, 0,
							transform.m[ 3].x, transform.m[ 3].y, transform.m[ 3].z, 1};
	glMultMatrixf( mVals);

	if ( sPtrs.empty())	// If no child scenes, draw the object
		obj->draw();
	else
	{
		for ( vector< Scene *>::const_iterator i = sPtrs.begin(); i != sPtrs.end(); ++i)
			(*i)->draw();
	}	// end else

	glPopMatrix();
}	// end Scene::draw
