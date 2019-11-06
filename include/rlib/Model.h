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
#include <GL/glut.h>

#include <ParseXFile.h>
using rlib::Triangle;


namespace rlib
{
   class Model
   {
   public:
        Model();
        ~Model();

        /**
         * Iterates through polys to draw them.
         */
        void draw() const;

        vector< Triangle> polys;

    private:
        Model( const Model &ro);	///< No copy construction.
        const Model &operator=( const Model &ro);	///< No copy assignment.

        void drawModel() const;	///< Called by constructor to create display list.

        mutable GLuint dl;	///< Display list generated at first draw.
   }; // end class Model
}  // end namespace rlib
