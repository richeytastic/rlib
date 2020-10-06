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
