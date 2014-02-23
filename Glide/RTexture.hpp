#pragma once

#include "Resource.hpp"

#include "GL/glew.h"

namespace gl
{

class RTexture : public Resource
{
public:
	RTexture( const ResourceConfig & config );
	RTexture( RTexture && other );
	RTexture( const RTexture & other ) = delete;
	RTexture & operator = ( const RTexture & other ) = delete;
	virtual ~RTexture();
	
	GLuint GetTextureID() const;

	Void Bind() const;

	static Void BindNull();

protected:
	GLuint mTextureID;
	UInt mColorType;
};

}