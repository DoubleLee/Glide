#include "ResourceManager.hpp"
#include "RTexture.hpp"
#include "GraphicsManager.hpp"

#include <Windows.h>

const std::string gTextureFolder("../Resources/Textures/");

int CALLBACK WinMain(
	_In_  HINSTANCE hInstance,
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,
	_In_  int nCmdShow
	)
	{
	gl::GraphicsManager graphics;
	gl::ResourceManager<gl::RTexture> textureManager;
	std::string str;

	textureManager.ResourceAdd( gl::ResourceConfig(gTextureFolder + "smileyFace.png", 1) );

	while( graphics.WindowOpen() )
		{
		graphics.Update();
		}

	return 0;
	}