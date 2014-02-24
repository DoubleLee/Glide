#pragma once

#include "GameObject.hpp"
#include "ResourceManager.hpp"
#include "RTexture.hpp"
#include "RMesh.hpp"

#include <string>

struct aiScene;


namespace gl
{

class Scene
{
public:
	Scene(const std::string & sceneFile);
	~Scene();

protected:
	Void LoadMaterials( const aiScene * pScene );

	ResourceManager< gl::RTexture<std::string> > mTextures;
	ResourceManager< gl::RMesh<std::string> > mMesh;

	std::string mFile;
};

}