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
