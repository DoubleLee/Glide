#pragma once

#include "Component.hpp"

#include <glm/mat4x4.hpp>

namespace gl
{
class GameObject;
class RMesh;
class RShader;
class RTexture;

class CRender :	public Component
{
public:
	CRender(const TypeID & typeID, GameObject * pOwner, RMesh * pMesh, RShader * pShader);
	//CRender();
	virtual ~CRender();

	virtual void Render(const glm::mat4 & camera);

protected:
	RMesh * mpMesh;
	RTexture * mpTexture;
	RShader * mpShader;
};

}