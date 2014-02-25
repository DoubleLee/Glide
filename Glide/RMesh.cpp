#include "RMesh.hpp"

#include "GLCheckError.hpp"

namespace gl
{

RMesh::RMesh(const RMesh::Configuration & config)
	:
	Resource(config)
	{

	}


RMesh::~RMesh()
	{
	BindNull();

	if ( mVAO )
		{
		GLCHECKERRORWARNING( glDeleteVertexArrays(1, &mVAO) )
		mVAO = 0u;
		}

	if ( mVBOVertPositions )
		{
		GLCHECKERRORWARNING(glDeleteBuffers(1, &mVBOVertPositions))
		mVBOVertPositions = 0u;
		}

	if ( mVBOVertNormals )
		{
		GLCHECKERRORWARNING(glDeleteBuffers(1, &mVBOVertNormals))
		mVBOVertNormals = 0u;
		}

	if ( mVBOVertUVs )
		{
		GLCHECKERRORWARNING(glDeleteBuffers(1, &mVBOVertUVs))
		mVBOVertUVs = 0u;
		}

	if ( mVBOVertIndicies )
		{
		GLCHECKERRORWARNING(glDeleteBuffers(1, &mVBOVertUVs))
		mVBOVertIndicies = 0u;
		}
	}

}