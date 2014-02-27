#include "CRender.hpp"

#include "RMesh.hpp"
#include "RTexture.hpp"
#include "RShader.hpp"

#include "GameObject.hpp"

namespace gl
{

CRender::CRender(const TypeID & typeID, GameObject * pOwner, RMesh * pMesh, RShader * pShader)
	:
	Component("Render", typeID, pOwner),
	mpMesh(pMesh),
	mpTexture(pMesh->GetTexture()),
	mpShader(pShader)
	{

	}

CRender::CRender()
	:
	Component()
	{
	SetFamilyID("Render");
	}


CRender::~CRender()
	{

	}

Void CRender::Render(const glm::mat4 & camera)
	{
	// Bind mesh
	// Bind Texture
	if ( mpMesh )
		mpMesh->Bind();
	else
		return;

	if ( mpTexture)
		mpTexture->Bind();
	else
		return;

	if ( mpShader )
		mpShader->Bind();
	else
		return;

	// TODO: Bind shader

	glm::mat4 MVP( camera * GetOwner()->GetGlobalWorld() );

	// Set Shaders MVP.
	mpShader->SetUniform("MVP", MVP);

	GLCHECKERROR( glDrawElements( GL_TRIANGLES, mpMesh->GetVertexIndexCount(), GL_UNSIGNED_INT, nullptr) )
	}
}