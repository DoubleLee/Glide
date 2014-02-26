#pragma once

#include "Component.hpp"

namespace gl
{
class GameObject;
class RMesh;
class RTexture;

class CRender :	public Component
{
public:
	CRender(const TypeID & typeID, GameObject * pOwner, RMesh * pMesh);
	CRender();
	virtual ~CRender();

	virtual void Render();

protected:
	RMesh * mpMesh;
	RTexture * mpTexture;
};

}