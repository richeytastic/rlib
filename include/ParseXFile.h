/**
 * class ParseXFile
 *
 * @author Richard Palmer
 * @date October 2007
 *
 * This class takes in an X file and parses the contents into
 * data structures than can be used by a Model class. Texture files
 * need to be BMPs!
 */

#pragma once
#include <GL/glut.h>

#include <iostream>
using std::cerr;
using std::endl;

#include <fstream>
using std::ifstream;

#include <string>
using std::string;

#include <sstream>
using std::stringstream;
using std::istringstream;

#include <cmath>
using std::sqrt;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <cstdlib>
using std::exit;

#include <Exceptions.h>
using rlib::IOException;

#include <BmpImage.h>
using rlib::BmpImage;



namespace rlib
{
	struct Material
	{
		float red;
		float green;
		float blue;
		string texFile;// Filename to identify texture
		GLuint texId;	// Id of texture
	};	// end struct Material


	struct Coords3D
	{
		float x;
		float y;
		float z;
	};	// end struct Coords3D


	struct Vertex
	{
		Coords3D c;
		float tx;	// 2D x coord of texture
		float ty;	// 2D y coord of texture
		Coords3D n;	// Normal of this vertex
	};	// end struct Vertex


	struct Triangle
	{
		Vertex v[3];	// Vertices
		Coords3D n;	// Normal - normalised sum of 3 vertex normals
		Material mat;
	};	// end struct Triangle


	struct Matrix
	{
		Coords3D m[4];	// Don't need final column since not concerned with projection (only using modelling coords).
	};	// end struct Matrix

	class Model;	// Defined elsewhere

	class Scene;	// Defined elsewhere


	class ParseXFile
	{
   public:
      /**
       * Loads the scene in from DirectX file and outputs data into vector objects.
       */
      static void loadModels( const string &fileName, Scene &scn);
      static const string TEXTURE_DIR;

   private:
      /**
       * Take material information and add to textures and materials.
       */
      static void parseMaterialBlock( stringstream &ss, map< string, Material> &materials);

      /**
       * Assumes materials created and creates objects in hierarchical fashion.
       */
      static void parseFrameBlock( stringstream &ss, map< string, Material> &materials, Scene &scn);
      static void createTextures( map< string, Material> &materials);	///< Called when Material blocks all parsed to create textures.
      static map< string, GLuint> texMap;	///< Map of textures.
	};	// end class ParseXFile
}	// end namespace rlib
