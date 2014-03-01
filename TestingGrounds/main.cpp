#include "ResourceManager.hpp"
#include "RTexture.hpp"
#include "ResourceConfig.hpp"
#include "GraphicsManager.hpp"
#include "Scene.hpp"
#include "Logger.hpp"
#include "GlideException.hpp"
#include "FilePaths.hpp"

#include "Matrix4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <string>

#define GLM_FORCE_RADIANS

int main()
	{
	gl::GraphicsManager graphics;

	gl::Scene scene("../Resources/Scenes/forestScene1.dae");
	
	while(graphics.WindowOpen())
		{
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