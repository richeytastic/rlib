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

#include <ParseXFile.h>
using namespace rlib;

#include <Model.h>
using rlib::Model;

#include <Scene.h>
using rlib::Scene;


map< string, GLuint> ParseXFile::texMap;
const string ParseXFile::TEXTURE_DIR = "textures";


/**
 * Fills ss with the contents between two matching
 * curly braces. Before the first curly brace, the
 * block identifying information is included.
 * Returns true if a block is found, false if not.
 */
bool getBlock( istream &is, stringstream &ss)
{
	ss.str( "");	// clear ss

	// Keep track of matching braces
	int openCount = 0;
	int closeCount = 0;

	string inLine;
	while ( getline( is, inLine))
	{
		if ( inLine.empty() || ( inLine.at( 0) == '/'))	// Ignore blank lines or lines starting with /
			continue;

		size_t foundOpenPos = inLine.find( '{');
		size_t foundClosePos = inLine.find( '}');

		if ( foundClosePos < foundOpenPos)
			throw IOException( "Malformed braces on line (close before open) in DirectX File!");

		if ( foundOpenPos != string::npos)
			++openCount;

		if ( foundClosePos != string::npos)
			++closeCount;

		// 3 Situations possible
		// a) openCount == closeCount == 0 in which case start of block not yet reached so continue
		// b) openCount == closeCount > 0 : end of block reached so finish reading in data before the closing brace and end loop
		// c) openCount > closeCount : not yet at the end of the block so read in data normally
		if (( openCount == closeCount) && ( openCount == 0))
			continue;

		if (( openCount == closeCount) && ( openCount > 0))
		{
			// Single line block - make sure opening brace isn't added
			if (( openCount == 1) && ( foundOpenPos != string::npos))
				ss << inLine.substr( 0, foundOpenPos) << " ";
			else
				foundOpenPos = -1;

			// Add remainder of string before closing brace
			ss << inLine.substr( foundOpenPos + 1, foundClosePos - foundOpenPos - 1) << endl;
			break;
		}	// end if

		if ( openCount > closeCount)
		{
			// Opening of block - make sure opening brace isn't added, but
			// do add the block identification info before the brace.
			if ( openCount == 1)
				ss << inLine.substr( 0, foundOpenPos) << endl;
			else
				ss << inLine << endl;
		}	// end if
	}	// end while

	return (( openCount == closeCount) && ( openCount > 0));
}	// end getBlock



void ParseXFile::loadModels( const string &fileName, Scene &scn)
{
	ifstream iff ( fileName.c_str());

	map< string, Material> materials;

	stringstream ss;
	while ( getBlock( iff, ss))	// Get and parse all the top level blocks in the file (Materials and Scene Frame)
	{
		string id;
		ss >> id;
		if ( id == "Material")
			parseMaterialBlock( ss, materials);
		else if ( id == "Frame")
		{
			createTextures( materials);	// All materials created so can now create textures.
			scn.parent = NULL;	// scn is root scene.
			parseFrameBlock( ss, materials, scn);
		}	// end if

		ss.clear();	// Clear failed extractions
	}	// end while - all blocks parsed
}	// end ParseXFile::loadModels



void ParseXFile::createTextures( map< string, Material> &mats)
{
	for ( map< string, Material>::iterator i = mats.begin(); i != mats.end(); ++i)
	{
		if ( !i->second.texFile.empty())	// If this material has a texture filename
		{
			if ( texMap.find( i->second.texFile) == texMap.end())	// If the texture wasn't already in texMap then load it.
			{
				GLuint texId;
				glGenTextures( 1, &texId);

				ostringstream oss;
				oss << ParseXFile::TEXTURE_DIR << "/" << i->second.texFile;

	   		BmpImage img( oss.str());	// Load the image for the texture
				glBindTexture( GL_TEXTURE_2D, texId);

				uint w = img.getWidth();
				uint h = img.getHeight();
				uint sz = w * h * 3;
				uchar pxls[ sz];
				img.getPixels( pxls, sz);

				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pxls);

				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				i->second.texId = texId;
				texMap[ i->second.texFile] = texId;
			}	// end if
			else
				i->second.texId = texMap[ i->second.texFile];
		}	// end if
	}	// end for
}	// end ParseXFile::createTextures



void ParseXFile::parseMaterialBlock( stringstream &ss, map< string, Material> &materials)
{
	Material nm;
	string matId;
	ss >> matId;
	char sc;	// Semicolons
	ss >> nm.red >> sc >> nm.green >> sc >> nm.blue;
	nm.texId = 0;	// Zeroed out for now (check for texture below).

	// Now get the texture file name if present
	stringstream ts;
	if ( getBlock( ss, ts))
	{
		string tex, texFile;
		ts >> tex >> texFile;
		// Strip quotes and semicolon from texFile
		texFile = texFile.substr( 1, texFile.size() - 3);
		nm.texFile = texFile;	// So we can identify the texture for this material later.
	}	// end if

	materials[ matId] = nm;	// Add nm to the map of materials.
}	// end ParseXFile::parseMaterialBlock



void getFrameTransformMatrix( stringstream &ss, Matrix &mt)
{
	// Get the transformation matrix
	stringstream mats;	// Matrix stream for the transformation matrix
	getBlock( ss, mats);
	string titleTrans;
	mats >> titleTrans;

	if ( titleTrans != "FrameTransformMatrix")
		throw IOException( "FrameTransformMatrix not found!");

	// Fill the transform matrix
	char c;
	float fNull;
	mats >> mt.m[ 0].x >> c >> mt.m[ 0].y >> c >> mt.m[ 0].z >> c >> fNull >> c 
		>> mt.m[ 1].x >> c >> mt.m[ 1].y >> c >> mt.m[ 1].z >> c >> fNull >> c 
		>> mt.m[ 2].x >> c >> mt.m[ 2].y >> c >> mt.m[ 2].z >> c >> fNull >> c 
		>> mt.m[ 3].x >> c >> mt.m[ 3].y >> c >> mt.m[ 3].z >> c >> fNull >> c >> c;
}	// end getFrameTransformMatrix



// Read in from ss to find the materials from mats needing to be assigned to the triangles.
void setPolygonMaterials( stringstream &ss, map< string, Material> &mats, vector< Triangle> &triangles)
{
	int numMats;
	int numPolys;
	char ch;	// Holds stripped commas, braces, semicolons...
	ss >> numMats >> ch >> numPolys >> ch;

	// Read in the material ids
	vector< int> matIds;	// Material ids corresponding to each triangle
	int id;

	for ( int i = 0; i < numPolys; ++i)
	{
		ss >> id >> ch;
		matIds.push_back( id);
	}	// end for

	ss >> ch;	// Final extra ; removed

	// Read in the material identifier strings
	vector< string> matStrings;
	string matStr;

	for ( int i = 0; i < numMats; ++i)
	{
		ss >> ch >> matStr >> ch;
		matStrings.push_back( matStr);
	}	// end for

	// Materials block now read in but need to now assign a material to each triangle.
	for ( int i = 0; i < numPolys; ++i)
	{
		Triangle nt;
		nt.mat = mats[ matStrings.at( matIds.at( i))];
		triangles.push_back( nt);
	}	// end for
}	// end setPolygonMaterials



void setVertexTextureCoords( stringstream &ss, vector< Vertex> &vtxs)
{
	int numVertices;
	char ch;
	ss >> numVertices >> ch;
	for ( int i = 0; i < numVertices; ++i)
		ss >> vtxs.at( i).tx >> ch >> vtxs.at( i).ty >> ch >> ch;
}	// end setVertexTextureCoords



void setVertexNormals( stringstream &ss, vector< Vertex> &vtxs)
{
	int numVertices;
	char ch;
	ss >> numVertices >> ch;
	for ( int i = 0; i < numVertices; ++i)
		ss >> vtxs.at( i).n.x >> ch >> vtxs.at( i).n.y >> ch >> vtxs.at( i).n.z >> ch >> ch;
}	// end setVertexNormals



void calculateTriangleNormal( Triangle &t)
{
	t.n.x = t.v[ 0].n.x * t.v[ 1].n.x * t.v[ 2].n.x;
	t.n.y = t.v[ 0].n.y * t.v[ 1].n.y * t.v[ 2].n.y;
	t.n.z = t.v[ 0].n.z * t.v[ 1].n.z * t.v[ 2].n.z;

	float magN = sqrt( t.n.x * t.n.x + t.n.y * t.n.y + t.n.z * t.n.z);
	t.n.x = t.n.x / magN;
	t.n.y = t.n.y / magN;
	t.n.z = t.n.z / magN;
}	// end calculateTriangleNormal



void setTriangleNormals( stringstream &ss, vector< Triangle> &triangles, vector< Vertex> &vtxs)
{
	int numTriangles, numSides, v1, v2, v3;
	char ch;
	ss >> numTriangles >> ch;
	for ( int i = 0; i < numTriangles; ++i)
	{
		ss >> numSides >> ch >> v1 >> ch >> v2 >> ch >> v3 >> ch >> ch;
		triangles.at( i).n.x = vtxs.at( v1).n.x + vtxs.at( v2).n.x + vtxs.at( v3).n.x;
		triangles.at( i).n.y = vtxs.at( v1).n.y + vtxs.at( v2).n.y + vtxs.at( v3).n.y;
		triangles.at( i).n.z = vtxs.at( v1).n.z + vtxs.at( v2).n.z + vtxs.at( v3).n.z;
	}	// end for
}	// end setTriangleNormals



void parseModelFrame( stringstream &ss, map< string, Material> &mats, Model &obj)
{
	char ch;
	int numVertices;
	ss >> numVertices >> ch;
	vector< Vertex> vtxs;	// Holds vertices for this object
	for ( int i = 0; i < numVertices; ++i)	// Read in each of the vertices
	{
		Vertex v;
		ss >> v.c.x >> ch >> v.c.y >> ch >> v.c.z >> ch >> ch;
		vtxs.push_back( v);
	}	// end for

	// Construct the triangles making up the object. Actually, we're setting the vertices
	// needed for each of the triangles in a vector of aliases since the Vertex objects
	// themselves will be added to later when we parse the texture coord block. Because
	// of this, the triangles will have the vertices copied into them (from polys) when
	// the whole mesh is parsed.
	int numPolys;
	int sides;	// Always 3 since dealing with triangles
	int v1, v2, v3;	// Indices of the vertices required for each triangle
	ss >> numPolys >> ch;
	vector< vector< Vertex *> > polys;	// Using a vertex of aliases to 3 Vertices since Vertices are changed later on.
	for ( int i = 0; i < numPolys; ++i)	// Read in each of the triangles
	{
		vector< Vertex *> verts;

		ss >> sides >> ch >> v1 >> ch >> v2 >> ch >> v3 >> ch >> ch;
		Vertex *v1p = &vtxs.at( v1);	// Aliasing
		Vertex *v2p = &vtxs.at( v2);	// Aliasing
		Vertex *v3p = &vtxs.at( v3);	// Aliasing

		verts.push_back( v1p);
		verts.push_back( v2p);
		verts.push_back( v3p);

		polys.push_back( verts);
	}	// end for

	vector< Triangle> triangles;	// Stores the triangles making up this object.

	// Set the materials, texture coords and normals.
	stringstream blockStream;
	while ( getBlock( ss, blockStream))
	{
		string title;
		blockStream >> title;
		if ( title == "MeshMaterialList")
		{
			// triangles is now filled and each member Triangle has its Material assigned.
			setPolygonMaterials( blockStream, mats, triangles);
		}
		else if ( title == "MeshTextureCoords")
			setVertexTextureCoords( blockStream, vtxs);	// Texture coords now set for each vertex
		else if ( title == "MeshNormals")
		{
			setVertexNormals( blockStream, vtxs);	// Normal now set for each vertex
			setTriangleNormals( blockStream, triangles, vtxs);	// Normal now set for each triangle
		}
	}	// end while

	for ( int i = 0; i < numPolys; ++i)	// Copy polys into the triangles
	{
		triangles.at( i).v[ 0] = *polys.at( i).at( 0);	// Copying
		triangles.at( i).v[ 1] = *polys.at( i).at( 1);	// Copying
		triangles.at( i).v[ 2] = *polys.at( i).at( 2);	// Copying

		// calculateTriangleNormal( triangles.at( i));
	}	// end for

	obj.polys = triangles;
}	// end parseModelFrame



void ParseXFile::parseFrameBlock( stringstream &ss, map< string, Material> &mats, Scene &scn)
{
	getFrameTransformMatrix( ss, scn.transform);	// Set the scene transform matrix

	// Parse each frame recursively until get to a Mesh
	stringstream blockStream;
	while ( getBlock( ss, blockStream))
	{
		string title;
		blockStream >> title;
		if ( title == "Frame")	// Recurse
		{
			Scene *childScene = new Scene();
			childScene->parent = &scn;
			scn.sPtrs.push_back( childScene);
			parseFrameBlock( blockStream, mats, *childScene);
		}	// end if
		else if ( title == "Mesh")	// Stop recursion
		{
			Model *obj = new Model();
			parseModelFrame( blockStream, mats, *obj);
			scn.obj = obj;
		}	// end else if

		blockStream.clear();
		ss.clear();
	}	// end while
}	// end ParseXFile::parseFrameBlock
