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

	gl::GraphicsManager graphics;

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