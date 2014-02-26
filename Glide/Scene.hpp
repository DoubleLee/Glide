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

class Scene
{
public:
	Scene(const std::string & sceneFile);
	~Scene();

protected:
	Void LoadMaterials( const aiScene * pScene );
	Void LoadMeshes( const aiScene * pScene );

	Void LoadNodes( const aiScene * pScene );
	Void LoadNode( const aiNode * pNode, GameObject * pParent );

	ResourceManager< gl::RTexture, UInt > mTextures;
	ResourceManager< gl::RMesh, UInt > mMeshes;

	GameObjectPtr mpRoot;

	std::string mFile;
};

}