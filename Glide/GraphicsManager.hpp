#pragma once

#include "BasicTypes.hpp"

struct GLFWwindow;

namespace gl
{

/**
Initializes glfw window and context, followed by
glew to get the openGL function pointers.
*/
class GraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager();

	/**
	if this should return false the application should exit the main
	loop and return.
	*/
	Bool WindowOpen() const;

	/**
	This needs to be called every frame usually at the end of the main loop.
	*/
	Void Update();

	GLFWwindow * mpWindow;
};

}