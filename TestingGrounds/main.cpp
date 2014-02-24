#include "ResourceManager.hpp"
#include "RTexture.hpp"
#include "GraphicsManager.hpp"
#include "Scene.hpp"
#include "Logger.hpp"

#include <Windows.h>

#include <string>

const std::string gTextureFolder("../Resources/Textures/");



enum class TexturesEnum
	{
	Wall,
	Couch,
	Table
	};

int CALLBACK WinMain(
	_In_  HINSTANCE hInstance,
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,
	_In_  int nCmdShow
	)
	{
	enum Texs
		{
		Trash,
		Crash,
		Rash
		};
	Logger log;

	std::string textureNameAndPath(gTextureFolder);
	std::string textureName("smileyFace.png");
	textureNameAndPath += textureName;

	gl::GraphicsManager graphics;
	gl::ResourceManager< gl::RTexture<std::string> > textureManager;

	gl::ResourceManager< gl::RTexture< TexturesEnum > > textureEnumManager;
	textureEnumManager.ResourceAdd(gl::ResourceConfig<TexturesEnum>(textureNameAndPath, TexturesEnum::Table));

	gl::RTexture<TexturesEnum> * pTex = textureEnumManager.ResourceGet( TexturesEnum::Table );
	
	textureManager.ResourceAdd(gl::ResourceConfig<std::string>(textureNameAndPath, textureName));

	gl::RTexture<std::string> * pTex2 = textureManager.ResourceGet( textureName );

	gl::ResourceManager< gl::RTexture< Texs > > man;
	man.ResourceAdd(gl::ResourceConfig<Texs>(textureNameAndPath, Texs::Trash));

	gl::RTexture<Texs> * pRes = man.ResourceGet( Texs::Trash );

	gl::Scene scene("../Resources/scenes/testScene.dae");

	while( graphics.WindowOpen() )
		{
		graphics.Update();
		}

	return 0;
	}