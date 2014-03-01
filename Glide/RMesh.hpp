#pragma once
#include "Resource.hpp"
#include "ResourceConfig.hpp"

#include "GL/glew.h"

namespace gl
{
class Configuration;
class RTexture;

/**
RMesh class represents a mesh.
Since we are using Assimp to load entire scenes this object just
takes in the openGL vao and vbos created by the scene loader, and 
stores those ids for rendering and destruction later.
*/
class RMesh : public Resource
{
public:
	class Configuration;
	typedef RMesh::Configuration ConfigType;
public:
	RMesh( const RMesh::Configuration & config );
	virtual ~RMesh();

	/**
	Bind this mesh to openGL's rendering system.
	*/
	Void Bind() const;

	/**
	Binds null to openGL's rendering system.
	*/
	static Void BindNull();
	
	/**
	returns the texture associated with this mesh.
	*/
	RTexture * GetTexture() const;

	/**
	retuns the vertex index count.  You need this when rendering
	meshes with index buffers.
	*/
	GLuint GetVertexIndexCount() const;

protected:
	RTexture * mpTexture;
	UInt mVertexCount;
	GLuint mVertexIndexCount;
	GLuint mVao;
	GLuint mVboPositions;
	GLuint mVboNormals;
	GLuint mVboUVs;
	GLuint mVboIndicies;
};

/**
RMesh needs more data than the default Resource::Configuration provides
So we inherit from that and add our vao/vbo data ect...
*/
class RMesh::Configuration : public Resource::Configuration
{
public:
	Configuration(const std::string & file,
				  RTexture * pTex, 
				  const UInt vertexCount,
				  const GLuint vertexIndexCount,
				  const GLuint vao,
				  const GLuint vboPositions,
				  const GLuint vboNormals,
				  const GLuint vboUVs,
				  const GLuint vboIndices);

	RTexture * mpTexture;
	UInt mVertexCount;
	GLuint mVertexIndexCount;
	GLuint mVao;
	GLuint mVboPositions;
	GLuint mVboNormals;
	GLuint mVboUVs;
	GLuint mVboIndices;
};

}