#pragma once
#include "Resource.hpp"

#include "GL/glew.h"

namespace gl
{

template< class Compare >
class RMesh : public Resource<Compare>
{
public:
	RMesh( const ResourceConfig<Compare> & config );
	virtual ~RMesh();

protected:
	GLuint mTextureID;
	GLuint mColorType;
};

template< class Compare >
RMesh<Compare>::RMesh( const ResourceConfig<Compare> & config )
	:
	Resource(config)
	{

	}

template< class Compare >
RMesh<Compare>::~RMesh()
	{

	}

}