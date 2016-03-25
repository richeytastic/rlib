#pragma once
#include <ParseXFile.h>
using rlib::Matrix;
#include <Model.h>
using rlib::Model;
#include <vector>
using std::vector;


namespace rlib
{
	class Scene
	{
		public:
         Scene();
         ~Scene();

			Scene *parent;	// Parent scene in the hierarchy (root scene has NULL parent).
			Model *obj;		// Model for this transform (no more child scenes i.e. if obj exists then this is leaf node).
			vector<Scene*> sPtrs;	// Child scenes.
			Matrix transform;	// The transformation needing to be applied at this level in the hierarchy.

			/**
 			 * Carries out the matrix transform at this level
 			 * then calls child scenes if sPtrs not empty, otherwise
 			 * calls obj::draw().
 			 */
			void draw() const;
	};	// end class Scene

}	// end namespace rlib
