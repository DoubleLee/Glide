#include "Scene.hpp"

#include "Resource.hpp"
#include "ResourceConfig.hpp"
#include "CRender.hpp"
#include "FilePaths.hpp"
#include "RShader.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace Assimp;
using namespace std;
namespace gl
{
// temporary simple camera code
glm::mat4 camera = glm::perspective(3.14f / 2.0f, 4.0f / 3.0f, 0.1f, 1000.0f) * glm::lookAt(glm::vec3(0, 4, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

Scene::Scene(const std::string & sceneFile)
	:
	mFile(sceneFile),
	mpRoot( std::make_unique<GameObject>("") ),
	mpShaderDefault( std::make_unique<RShader>( RShader::ConfigType(gShadersFolder + "vertShader.vert", gShadersFolder + "fragShader.frag") ))
	{
	Assimp::Importer importer;

	const aiScene * pScene = importer.ReadFile( mFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType |
		aiProcess_ConvertToLeftHanded );

	if ( !pScene )
		{
		throw GlideException("Failed to load scene from assimp file, " + mFile);
		}

	LoadMaterials( pScene );
	LoadMeshes( pScene);
	LoadNodes(pScene);
	}

Scene::~Scene()
	{
	}

RShader * Scene::GetShader()
	{
	return mpShaderDefault.get();
	}

Void Scene::Render()
	{
	mpRoot->CalculateWorlds(glm::mat4(1.0f));

	mpRoot->Render(camera);
	}

Void Scene::LoadMaterials( const aiScene * pScene )
	{
	// Loading materials, at this time just texture strings.
	for ( UInt i = 0; i < pScene->mNumMaterials; ++i )
		{
		UInt texCount = pScene->mMaterials[i]->GetTextureCount(aiTextureType_DIFFUSE);
		for ( UInt j = 0; j < texCount; ++j )
			{
			aiString texFile;
			pScene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, j, &texFile);

			// TODO: finish writing texture file name loader.
			RTexture::ConfigType config( gTexturesFolder + texFile.C_Str());
			mTextures.ResourceAdd(config, texFile.C_Str());
			}
		}
	}

Void Scene::LoadMeshes( const aiScene * pScene )
	{
	for ( UInt i = 0; i < pScene->mNumMeshes; ++i )
		{
		aiMesh * pMesh = pScene->mMeshes[i];

		GLuint vertexCount = pMesh->mNumVertices;
		if ( pMesh->mPrimitiveTypes != aiPrimitiveType_TRIANGLE )
			throw GlideException("Mesh is not triangulated.", pMesh->mPrimitiveTypes);
		const UInt vertsPerFace = 3;
		GLuint vertexIndexCount = pMesh->mNumFaces * vertsPerFace;

		std::vector<GLuint> indices(vertexIndexCount, 0);

		for ( UInt index = 0; index < vertexIndexCount; ++index )
			{
			indices[index] = pMesh->mFaces[index / 3].mIndices[index % 3];
			}

		// create vao
		GLuint vao = 0;
		GLCHECKERROR( glGenVertexArrays(1, &vao) )
		GLCHECKERROR( glBindVertexArray(vao) )

		// Loading positions data
		GLuint vboPositions = 0;
		if ( pMesh->HasPositions() )
			{
			GLCHECKERROR( glGenBuffers(1, &vboPositions) )
			GLCHECKERROR( glBindBuffer( GL_ARRAY_BUFFER, vboPositions ) )
			GLCHECKERROR( glBufferData( GL_ARRAY_BUFFER, sizeof( aiVector3D ) * pMesh->mNumVertices, pMesh->mVertices, GL_STATIC_DRAW ) )
			
			GLCHECKERROR( glEnableVertexAttribArray(0) )

			GLCHECKERROR( glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof( aiVector3D ), nullptr) )
			}

		GLuint vboNormals = 0;
		if ( pMesh->HasNormals() )
			{
			GLCHECKERROR( glGenBuffers(1, &vboNormals) )
			GLCHECKERROR( glBindBuffer( GL_ARRAY_BUFFER, vboNormals) )
			GLCHECKERROR( glBufferData( GL_ARRAY_BUFFER, sizeof( aiVector3D ) * pMesh->mNumVertices, pMesh->mNormals, GL_STATIC_DRAW ) )

			GLCHECKERROR( glEnableVertexAttribArray(1) )

			GLCHECKERROR( glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof( aiVector3D ), nullptr) )
			}

		// NOTE: only one UV channel supported at this time.
		GLuint vboUVs = 0;
		if ( pMesh->HasTextureCoords(0) )
			{
			GLCHECKERROR( glGenBuffers(1, &vboUVs) )
			GLCHECKERROR( glBindBuffer( GL_ARRAY_BUFFER, vboUVs ) )
			GLCHECKERROR( glBufferData( GL_ARRAY_BUFFER, sizeof( aiVector3D ) * pMesh->mNumVertices, &pMesh->mTextureCoords[0][0], GL_STATIC_DRAW ) )

			GLCHECKERROR( glEnableVertexAttribArray(2) )

			GLCHECKERROR( glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(aiVector3D), nullptr) )
			}

		GLuint vboIndices = 0;
		if ( pMesh->HasFaces() && pMesh->mNumFaces != 0u )
			{
			GLCHECKERROR( glGenBuffers(1, &vboIndices) )
			GLCHECKERROR( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vboIndices) )
			GLCHECKERROR( glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( GLuint ) * vertexIndexCount, indices.data(), GL_STATIC_DRAW ) )
			}

		RTexture * pTex = nullptr;
		if(pScene->mMaterials[pMesh->mMaterialIndex]->GetTextureCount(aiTextureType_DIFFUSE) > 0)
			{
			aiString texFile;
			pScene->mMaterials[pMesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &texFile);
			std::string file(texFile.C_Str());
			pTex = mTextures.ResourceGet(file);
			}
		
		RMesh::ConfigType config(mFile, pTex, vertexCount, vertexIndexCount, vao, vboPositions, vboNormals, vboUVs, vboIndices);

		mMeshes.ResourceAdd(config, i);
		}
	}

Void Scene::LoadNodes( const aiScene * pScene )
	{
	for ( UInt i = 0; i < pScene->mRootNode->mNumChildren; ++i )
		{
		LoadNode( pScene->mRootNode->mChildren[i], mpRoot.get() );
		}
	}

Void Scene::LoadNode( const aiNode * pNode, GameObject * pParent )
	{
	// Load node meshes and create GameObject
	std::unique_ptr<GameObject> pObject( std::make_unique<GameObject>(pNode->mName.C_Str()) );
	// NOTE: dangerous cast here, if both are truely packed floats it should work.
	aiMatrix4x4 nodeWorld = pNode->mTransformation;
	glm::mat4 localWorld;
	localWorld[0][0] = nodeWorld.a1;
	localWorld[0][1] = nodeWorld.b1;
	localWorld[0][2] = nodeWorld.c1;
	localWorld[0][3] = nodeWorld.d1;

	localWorld[1][0] = nodeWorld.a2;
	localWorld[1][1] = nodeWorld.b2;
	localWorld[1][2] = nodeWorld.c2;
	localWorld[1][3] = nodeWorld.d2;

	localWorld[2][0] = nodeWorld.a3;
	localWorld[2][1] = nodeWorld.b3;
	localWorld[2][2] = nodeWorld.c3;
	localWorld[2][3] = nodeWorld.d3;
	
	localWorld[3][0] = nodeWorld.a4;
	localWorld[3][1] = nodeWorld.b4;
	localWorld[3][2] = nodeWorld.c4;
	localWorld[3][3] = nodeWorld.d4;

	pObject->SetLocalWorld( localWorld );
	// call load node on each of its children

	if ( pNode->mMeshes )
		{
		std::unique_ptr<CRender> pCRender( std::make_unique<CRender>("", pObject.get(), mMeshes.ResourceGet( pNode->mMeshes[0] ), mpShaderDefault.get() ) );

		pObject->ComponentAdd(std::move(pCRender));
		}

	auto pObjectPtr = pObject.get();
	pParent->ChildAdd( std::move(pObject) );

	for ( UInt i = 0; i < pNode->mNumChildren; ++i )
		{
		LoadNode(pNode->mChildren[i], pObjectPtr);
		}
	}

GameObject * Scene::FindObjectByID( const std::string & id, GameObject * pStartObject)
	{
	if ( pStartObject == nullptr )
		pStartObject = mpRoot.get();

	return pStartObject->FindChildByID(id);
	}
}