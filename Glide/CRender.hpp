#pragma once

#include "Component.hpp"

#include <glm/mat4x4.hpp>

namespace gl
{
class GameObject;
class RMesh;
class RShader;
class RTexture;

/**
This is the openGL Rendering component.
Every GameObject that needs to be rendered needs one of these.
It stores the mesh, texture and shader pointers.
It will grab the Texture from the mesh passed in.

NOTE: currently there is a shader pointer passed in this may change.
*/
class CRender :	public Component
{
public:
	CRender(const TypeID & typeID, GameObject * pOwner, RMesh * pMesh, RShader * pShader);
	//CRender();
	virtual ~CRender();

	/**
	render the game object this component is attached to.
	*/
	virtual void Render(const glm::mat4 & camera);

protected:
	RMesh * mpMesh;
	RTexture * mpTexture;
	RShader * mpShader;
};

}