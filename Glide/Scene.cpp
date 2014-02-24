#include "Scene.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"



using namespace Assimp;
using namespace std;
namespace gl
{

Scene::Scene(const std::string & sceneFile)
	:
	mFile(sceneFile)
	{
	Assimp::Importer importer;

	const aiScene * pScene = importer.ReadFile( mFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType );

	if ( !pScene )
		{
		throw std::runtime_error("Failed to load scene from assimp file, " + mFile);
		}

	LoadMaterials( pScene );
	}


Scene::~Scene()
	{
	}

Void Scene::LoadMaterials( const aiScene * pScene )
	{
	for ( UInt i = 0; i < pScene->mNumMaterials; ++i )
		{
		for ( UInt j = 0; j < pScene->mMaterials[i]->GetTextureCount(aiTextureType_DIFFUSE); ++j )
			{
			aiString texFile;
			pScene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, j, &texFile);

			// TODO: finish writing texture file name loader.
			//gl::ResourceConfig config(texFile,
			}
		}
	}
}