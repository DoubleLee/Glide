#pragma once
#include "Resource.hpp"
#include "ResourceConfig.hpp"

#include "GL/glew.h"

namespace gl
{
class Configuration;

class RMesh : public Resource
{
public:
	class Configuration;
	typedef RMesh::Configuration ConfigType;
public:
	RMesh( const RMesh::Configuration & config );
	virtual ~RMesh();

	static Void BindNull();

protected:
	GLuint mVAO;
	GLuint mVBOVertPositions;
	GLuint mVBOVertNormals;
	GLuint mVBOVertUVs;
	GLuint mVBOVertIndicies;
	UInt mVertexCount;
	UInt mVertexIndiciesCount;
};

class RMesh::Configuration : public Resource::Configuration
{
public:
	Configuration(const std::string & file, GLuint meshID);

	GLuint GetMeshID() const;

protected:
	GLuint mMeshID;
};

}