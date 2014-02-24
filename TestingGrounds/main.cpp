#include "ResourceManager.hpp"
#include "RTexture.hpp"
#include "ResourceConfig.hpp"
#include "GraphicsManager.hpp"
#include "Scene.hpp"
#include "Logger.hpp"

#include <string>

const std::string gTextureFolder("../Resources/Textures/");


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
	std::string textureNameAndPath(gTextureFolder);
	std::string textureName("smileyFace.png");
	textureNameAndPath += textureName;

	gl::GraphicsManager graphics;

	// Using enum class as key
	// create manager
	gl::ResourceManager< gl::RTexture, TexturesEnum > textureEnumManager;
	// load a resource
	textureEnumManager.ResourceAdd(gl::ResourceConfig(textureNameAndPath), TexturesEnum::Table);
	// request a resource
	gl::RTexture * pTex = textureEnumManager.ResourceGet(TexturesEnum::Table);

	// Using std::string as key
	gl::ResourceManager< gl::RTexture, std::string > textureManager;
	// load a resource
	textureManager.ResourceAdd(gl::ResourceConfig(textureNameAndPath), textureName);
	// request a resource
	gl::RTexture * pTex2 = textureManager.ResourceGet(textureName);

	// Using enum as key
	gl::ResourceManager< gl::RTexture, Texs > enumManager;
	// load a resource
	enumManager.ResourceAdd(gl::ResourceConfig(textureNameAndPath), Texs::Trash);
	// request a resource
	gl::RTexture * pRes = enumManager.ResourceGet(Texs::Trash);

	gl::Scene scene("../Resources/scenes/testScene.dae");

	while(graphics.WindowOpen())
		{
		graphics.Update();
		}

	return 0;
	}

#ifdef WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

int CALLBACK WinMain(
	_In_  HINSTANCE hInstance,
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,
	_In_  int nCmdShow
	)
	{
	return main();
	}

#endif