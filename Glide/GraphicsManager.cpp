#include "GraphicsManager.hpp"

#include "GLCheckError.hpp"

#include "tinyxml2.hpp"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <string>
#include <stdexcept>

using namespace std;
using namespace tinyxml2;

namespace gl
{

GraphicsManager::GraphicsManager()
	{
	const std::string file("..\\Resources\\Config\\graphics.xml");

	XMLDocument config;
	if ( config.LoadFile(file.c_str()) != XML_NO_ERROR )
		{
		throw std::runtime_error("Failed to load xml file, " + file);
		}

	int width = 0;
	int height = 0;

	XMLElement * pGraphics = config.RootElement();

	if ( pGraphics->QueryIntAttribute("width", &width) != XML_NO_ERROR )
		{
		throw std::runtime_error("Failed to find width attribute in, " + file);
		}

	if ( pGraphics->QueryIntAttribute("height", &height) != XML_NO_ERROR )
		{
		throw std::runtime_error("Failed to find height attribute in, " + file);
		}

	const char * pWindowTitle = nullptr;

	if ( !(pWindowTitle = pGraphics->Attribute("window_title")) )
		{
		pWindowTitle = "Glide Engine";
		}

	if ( glfwInit() != GL_TRUE )
		{
		throw std::runtime_error("Failed to init glfw3.");
		}

	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE ,GLFW_OPENGL_CORE_PROFILE);

	mpWindow = glfwCreateWindow(width, height, pWindowTitle, nullptr, nullptr);

	if ( !mpWindow )
		throw std::runtime_error("Failed to create glfw3 window and/or context.");

	glfwMakeContextCurrent(mpWindow);

	glewExperimental = true;
	if ( glewInit() != GLEW_OK )
		{
		throw std::runtime_error("Failed to initialize glew.");
		}
	glGetError(); // clear error from experimental

	// This is where we check for particular openGL version.
	if(!GLEW_VERSION_3_3)
		{
		// We must get above version at least, or we throw this exception.
		throw std::runtime_error("Failed to get atleast openGL 3.3.");
		}
	else
		{
		// we got at least what we need.  Print to 
		int Maj,Min;
		GLCHECKERROR(glGetIntegerv(GL_MAJOR_VERSION, &Maj))
		GLCHECKERROR(glGetIntegerv(GL_MINOR_VERSION, &Min))

		std::cout << "OpenGL context version [" << Maj << '.' << Min << "] created.\n";
		}

	glGetError();
	}

GraphicsManager::~GraphicsManager()
	{
	glfwDestroyWindow(mpWindow);
	glfwTerminate();
	}

Bool GraphicsManager::WindowOpen() const
	{
	return !glfwWindowShouldClose( mpWindow );
	}

Void GraphicsManager::Update()
	{
	glfwPollEvents();
	glfwSwapBuffers(mpWindow);
	}
}