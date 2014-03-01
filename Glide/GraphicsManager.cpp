#include "GraphicsManager.hpp"

#include "Logger.hpp"
#include "GLCheckError.hpp"
#include "GlideException.hpp"

#include "tinyxml2.hpp"
#include "XML_Handler.hpp"
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
		throw GlideException("Failed to load xml file, " + file);
		}

	int width = 0;
	int height = 0;

	XMLElement * pGraphics = config.RootElement();

	XML::CheckError( pGraphics->QueryIntAttribute("width", &width) );
	XML::CheckError( pGraphics->QueryIntAttribute("height", &height) );

	const char * pWindowTitle = nullptr;

	if ( !(pWindowTitle = pGraphics->Attribute("window_title")) )
		{
		pWindowTitle = "Glide Engine";
		}

	if ( glfwInit() != GL_TRUE )
		{
		throw GlideException("Failed to init glfw3.");
		}

	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE ,GLFW_OPENGL_CORE_PROFILE);

	mpWindow = glfwCreateWindow(width, height, pWindowTitle, nullptr, nullptr);

	if ( !mpWindow )
		throw GlideException("Failed to create glfw3 window and/or context.");

	glfwMakeContextCurrent(mpWindow);

	glewExperimental = true;
	if ( glewInit() != GLEW_OK )
		{
		throw GlideException("Failed to initialize glew.");
		}

	glGetError(); // clear error from experimental

	// This is where we check for particular openGL version.
	if(!GLEW_VERSION_3_3)
		{
		// We must get above version at least, or we throw this exception.
		throw GlideException("Failed to get atleast openGL 3.3.");
		}
	else
		{
		// we got at least what we need.  Print to 
		int Maj,Min;
		GLCHECKERROR(glGetIntegerv(GL_MAJOR_VERSION, &Maj))
		GLCHECKERROR(glGetIntegerv(GL_MINOR_VERSION, &Min))

		gLogger.LogTime() << "OpenGL context version [" << Maj << '.' << Min << "] created." << std::endl;
		}

	// setup default openGL settings
	GLCHECKERROR( glClearColor(0.5f, 0.5f, 0.5f, 1.0f) )

	GLCHECKERROR(glEnable(GL_DEPTH_TEST))

	GLCHECKERROR(glDepthFunc(GL_LESS))

	GLCHECKERROR(glEnable(GL_CULL_FACE))
	//glFrontFace( GL_CW );
	GLCHECKERROR(glCullFace(GL_BACK))
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
	GLCHECKERROR( glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) )
	}
}