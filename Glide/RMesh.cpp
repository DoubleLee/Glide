#include "RMesh.hpp"

#include "GLCheckError.hpp"

#include "RTexture.hpp"

namespace gl
{

RMesh::RMesh(const RMesh::Configuration & config)
	:
	Resource(config),
	mpTexture(config.mpTexture),
	mVertexCount(config.mVertexCount),
	mVertexIndexCount(config.mVertexIndexCount),
	mVao(config.mVao),
	mVboPositions(config.mVboPositions),
	mVboNormals(config.mVboNormals),
	mVboUVs(config.mVboUVs),
	mVboIndicies(config.mVboIndices)
	{

	}


RMesh::~RMesh()
	{
	BindNull();

	if ( mVao )
		{
		GLCHECKERRORWARNING(glDeleteVertexArrays(1, &mVao))
			mVao = 0u;
		}

	if ( mVboPositions )
		{
		GLCHECKERRORWARNING(glDeleteBuffers(1, &mVboPositions))
		mVboPositions = 0u;
		}

	if ( mVboNormals )
		{
		GLCHECKERRORWARNING(glDeleteBuffers(1, &mVboNormals))
		mVboNormals = 0u;
		}

	if ( mVboUVs )
		{
		GLCHECKERRORWARNING(glDeleteBuffers(1, &mVboUVs))
		mVboUVs = 0u;
		}

	if ( mVboIndicies )
		{
		GLCHECKERRORWARNING(glDeleteBuffers(1, &mVboIndicies))
		mVboIndicies = 0u;
		}
	}

Void RMesh::Bind() const
	{
	GLCHECKERROR(glBindVertexArray(mVao))
	}

Void RMesh::BindNull()
	{
	GLCHECKERROR(glBindVertexArray(0))
	}

RTexture * RMesh::GetTexture() const
	{
	return mpTexture;
	}

GLuint RMesh::GetVertexIndexCount() const
	{
	return mVertexIndexCount;
	}

RMesh::Configuration::Configuration(const std::string & file,
	RTexture * pTex,
	const UInt vertexCount,
	const GLuint vertexIndexCount,
	const GLuint vao,
	const GLuint vboPositions,
	const GLuint vboNormals,
	const GLuint vboUVs,
	const GLuint vboIndices)
	:
	Resource::Configuration(file),
	mpTexture(pTex),
	mVertexCount(vertexCount),
	mVertexIndexCount(vertexIndexCount),
	mVao(vao),
	mVboPositions(vboPositions),
	mVboNormals(vboNormals),
	mVboUVs(vboUVs),
	mVboIndices(vboIndices)
	{

	}

}