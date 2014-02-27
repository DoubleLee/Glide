#include "ResourceManager.hpp"
#include "RTexture.hpp"
#include "ResourceConfig.hpp"
#include "GraphicsManager.hpp"
#include "Scene.hpp"
#include "Logger.hpp"
#include "GlideException.hpp"
#include "FilePaths.hpp"

#include <string>

#define GLM_FORCE_RADIANS

enum class TexturesEnum
	{
	Wall,
	Couch,
	Table
	};

enum Texs
	{
	Trash,
	Crash,
	Rash
	};

int main()
	{
	std::string textureNameAndPath(gl::gTexturesFolder);
	std::string textureName("smileyFace.png");
	textureNameAndPath += textureName;

	gl::GraphicsManager graphics;

	// Using enum class as key
	// create manager
	gl::ResourceManager< gl::RTexture, TexturesEnum > textureEnumManager;
	// load a resource
	textureEnumManager.ResourceAdd(gl::Resource::Configuration(textureNameAndPath), TexturesEnum::Table);
	// request a resource
	gl::RTexture * pTex = textureEnumManager.ResourceGet(TexturesEnum::Table);

	// Using std::string as key
	gl::ResourceManager< gl::RTexture, std::string > textureManager;
	// load a resource
	textureManager.ResourceAdd(gl::Resource::Configuration(textureNameAndPath), textureName);
	// request a resource
	gl::RTexture * pTex2 = textureManager.ResourceGet(textureName);

	// Using enum as key
	gl::ResourceManager< gl::RTexture, Texs > enumManager;
	// load a resource
	enumManager.ResourceAdd(gl::Resource::Configuration(textureNameAndPath), Texs::Trash);
	// request a resource
	gl::RTexture * pRes = enumManager.ResourceGet(Texs::Trash);

	gl::Scene scene("../Resources/Scenes/testScene.3ds");

	// Intentional error, with thrown exception
	//GLCHECKERROR(glBindTexture(GL_TEXTURE_2D, 900) )
	
	while(graphics.WindowOpen())
		{
		gl::GameObject * pLamp = scene.FindObjectByID("Lamp");
		scene.Render();
		graphics.Update();
		}

	return 0;
	}

#ifdef WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

int CALLBACK WinMain(_In_  HINSTANCE hInstance, 
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,
	_In_  int nCmdShow)
	{
	return main();
	}

#endif