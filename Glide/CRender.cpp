#include "CRender.hpp"

namespace gl
{

CRender::CRender(const TypeID & typeID, GameObject * pOwner)
	:
	Component("Render", typeID, pOwner)
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


}