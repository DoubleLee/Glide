#pragma once
#include "Component.hpp"

namespace gl
{
class GameObject;

/**
CCamera is a GameObject component that represents
openGL camera.
*/
class CCamera : public Component
{
public:
	CCamera(GameObject * pOwner);
	virtual ~CCamera();

protected:
	
};

}