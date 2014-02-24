#include "ResourceManager.hpp"
#include "RTexture.hpp"
#include "GraphicsManager.hpp"
#include "Scene.hpp"

#include <Windows.h>

#include <string>

const std::string gTextureFolder("../Resources/Textures/");

int CALLBACK WinMain(
	_In_  HINSTANCE hInstance,
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,
	_In_  int nCmdShow
	)
	{
	
	gl::GraphicsManager graphics;
	gl::ResourceManager< gl::RTexture<std::string> > textureManager;
	
	std::string file(gTextureFolder);
	file += "smileyFace.png";

	textureManager.ResourceAdd( gl::ResourceConfig<std::string>(file, gl::StripPath(file) ) );

	gl::Scene scene("../Resources/scenes/testScene.dae");

	while( graphics.WindowOpen() )
		{
		graphics.Update();
		}

	return 0;
	}