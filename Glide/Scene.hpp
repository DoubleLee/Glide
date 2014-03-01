#pragma once

#include "GameObject.hpp"
#include "ResourceManager.hpp"
#include "RTexture.hpp"
#include "RMesh.hpp"

#include <string>

struct aiScene;
struct aiNode;

namespace gl
{
class RShader;

/**
Stores the scene node hiarchy, the meshes and textures.

Soon to also store the lights and cameras.
*/
class Scene
{
public:
	Scene(const std::string & sceneFile);
	~Scene();

	/**
	Get a game object in the hiarchy by its ID field.
	*/
	GameObject * FindObjectByID( const std::string & id, GameObject * pStartObject = nullptr );
	
	// temporary call, shaders will be managed by a resource.
	RShader * GetShader();

	Void Render();

protected:
	Void LoadMaterials( const aiScene * pScene );
	Void LoadMeshes( const aiScene * pScene );

	Void LoadNodes( const aiScene * pScene );
	Void LoadNode( const aiNode * pNode, GameObject * pParent );

	ResourceManager< gl::RTexture, std::string > mTextures;
	ResourceManager< gl::RMesh, UInt > mMeshes;

	std::unique_ptr<RShader> mpShaderDefault;

	GameObjectPtr mpRoot;

	std::string mFile;
};

}