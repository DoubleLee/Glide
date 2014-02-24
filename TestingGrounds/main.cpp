#include "ResourceManager.hpp"
#include "RTexture.hpp"
#include "GraphicsManager.hpp"
#include "Scene.hpp"

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
	std::string file(gTextureFolder);
	file += "smileyFace.png";

	gl::GraphicsManager graphics;
	gl::ResourceManager< gl::RTexture<std::string> > textureManager;

	gl::ResourceManager< gl::RTexture< TexturesEnum > > textureEnumManager;
	textureEnumManager.ResourceAdd(gl::ResourceConfig<TexturesEnum>(file, TexturesEnum::Table));

	gl::RTexture<TexturesEnum> * pTex = textureEnumManager.ResourceGet( TexturesEnum::Table );
	

	textureManager.ResourceAdd( gl::ResourceConfig<std::string>(file, gl::StripPath(file) ) );

	gl::RTexture<std::string> * pTex2 = textureManager.ResourceGet( gl::StripPath(file) );

	gl::Scene scene("../Resources/scenes/testScene.dae");

	while( graphics.WindowOpen() )
		{
		graphics.Update();
		}

	return 0;
	}