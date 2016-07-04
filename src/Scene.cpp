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
