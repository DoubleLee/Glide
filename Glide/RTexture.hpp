#pragma once

#include "Resource.hpp"
#include "GLCheckError.hpp"

#include "libpng16/png.h"

#include "GL/glew.h"

#include <fstream>
#include <stdexcept>
#include <memory>

namespace gl
{
void ErrorCallbackPNG(png_structp png_ptr, png_const_charp error_msg);
void ReadDataCallbackPNG(png_structp pngReadPtr, png_bytep data, png_size_t length);

/**
RTexture represents a texture for openGL.
Currently it only supports png, more format support in bound.
Since RTexture loads the resource itself we need a file name.
the default ResourceConfig stores enough info for this.
*/
class RTexture : public Resource
{
public:
	typedef Resource::Configuration ConfigType;
public:
	/*
	RTexture manages an openGL texture id.
	It takes in a ResourceConfig<Compare> which is the default configuration class
	This class only needs a file name so the default config class is fine.
	When this class goes out of scope it will tell openGL to free the texture.
	*/
	RTexture( const Resource::Configuration & config );
	RTexture( RTexture && other );
	RTexture( const RTexture & other ) = delete;
	RTexture & operator = ( const RTexture & other ) = delete;
	virtual ~RTexture();
	
	// returns opengl texture id
	GLuint GetTextureID() const;

	// calls opengl glBindTexture with this objects texture id
	// effectively making this texture the active one.
	Void Bind() const;

	// simply calls glBindTexture(0) so there will be no bound texture.
	static Void BindNull();

protected:
	GLuint mTextureID;
	GLenum mColorType;
};

}