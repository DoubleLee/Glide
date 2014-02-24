#pragma once
#include "Resource.hpp"

#include "GL/glew.h"

namespace gl
{


class RMesh : public Resource
{
public:
	RMesh( const ResourceConfig & config );
	virtual ~RMesh();

protected:
	GLuint mTextureID;
	GLuint mColorType;
};

}