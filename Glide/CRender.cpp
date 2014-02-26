#include "CRender.hpp"

#include "RMesh.hpp"
#include "RTexture.hpp"

#include "GameObject.hpp"

namespace gl
{

CRender::CRender(const TypeID & typeID, GameObject * pOwner, RMesh * pMesh)
	:
	Component("Render", typeID, pOwner),
	mpMesh(pMesh),
	mpTexture(pMesh->GetTexture())
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

Void CRender::Render()
	{
	// Bind mesh
	// Bind Texture
	mpMesh->Bind();
	mpTexture->Bind();

	// TODO: Bind shader

	//glm::mat4 MVP( cameraVP * GetOwner()->GetGlobalWorld() );

	// Set Shaders MVP.

	GLCHECKERROR( glDrawElements( GL_TRIANGLES, mpMesh->GetVertexIndexCount(), GL_UNSIGNED_INT, nullptr) )
	}
}