#pragma once
#include "Resource.hpp"
#include "ResourceConfig.hpp"

#include "GL/glew.h"

namespace gl
{
class Configuration;
class RTexture;

class RMesh : public Resource
{
public:
	class Configuration;
	typedef RMesh::Configuration ConfigType;
public:
	RMesh( const RMesh::Configuration & config );
	virtual ~RMesh();

	Void Bind() const;

	static Void BindNull();

	RTexture * GetTexture() const;

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