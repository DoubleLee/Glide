#pragma once

#include "Component.hpp"

namespace gl
{
class GameObject;

class CRender :	public Component
{
public:
	CRender(const TypeID & typeID, GameObject * pOwner);
	CRender();
	virtual ~CRender();

	virtual void Render() = 0;
};

}