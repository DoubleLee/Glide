#include "RShader.hpp"

#include "Logger.hpp"
#include "GlideException.hpp"
#include "GLCheckError.hpp"

namespace gl
{

RShader::RShader(const RShader::Configuration & config)
	:
	Resource( config ),
	mVertexFile( config.mVertexFile ),
	mFragFile( config.mFragFile ),
	mProgramID(0u),
	mVertID(0u),
	mFragID(0u)
	{
	LoadShaders();
	}

RShader::~RShader()
	{

	}


Void RShader::LoadShaders()
	{
	gLogger.LogTime() << "Compiling shader program from files [" << mVertexFile << ',' << mFragFile << ']' << std::endl;

	GLCHECKERROR( mVertID = glCreateShader(GL_VERTEX_SHADER) )
	GLCHECKERROR( mFragID = glCreateShader(GL_FRAGMENT_SHADER) )

	std::ifstream vertexFileStream(mVertexFile, std::ios_base::in | std::ios_base::ate);
	std::ifstream fragFileStream(mFragFile, std::ios_base::in | std::ios_base::ate);

	if ( !vertexFileStream.is_open() || !fragFileStream.is_open() )
		{
		throw GlideException("Couldn't find shader file, " + (!vertexFileStream.is_open()) ? mVertexFile : mFragFile);
		}

	// files were found

	// initialize string to file size.
	std::string vertexCode(Int(vertexFileStream.tellg()),0);

	// move stream back to beginning ( started at end )
	vertexFileStream.seekg(0);
	// write the file to string
	vertexFileStream.read(&vertexCode[0], vertexCode.size());

	// check for error
	if ( vertexFileStream.bad() )
		{
		throw GlideException("Error while loading vertex file, " + mVertexFile);
		}

	// close the file stream
	vertexFileStream.close();

	// create fragment code string, and set to file size
	std::string fragCode(Int(fragFileStream.tellg()), 0);

	// move stream back to beginning of file ( started at the end )
	fragFileStream.seekg(0);
	// read the file characters into the string
	fragFileStream.read(&fragCode[0], fragCode.size());

	// check for error
	if ( fragFileStream.bad() )
		{
		throw GlideException("Error while loading fragment file, " + mFragFile);
		}

	gLogger.LogTime() << "Success loading shader code into strings." << std::endl;
	gLogger.LogTime() << "Beginning compilation process." << std::endl;

	// declare result variables
	GLint result = GL_FALSE;
	GLint infoLogLength = 0;

	// Get vertex code pointer
	const GLchar * pVertexSource = vertexCode.c_str();
	// get vertex source code size
	GLint vertSourceSize = vertexCode.size() + 1;

	// Load source code into openGL
	GLCHECKERROR( glShaderSource(mVertID, 1, &pVertexSource, &vertSourceSize) )
	// tell openGL to compile vertex shader
	GLCHECKERROR( glCompileShader(mVertID) );
	// get error status from compilation
	GLCHECKERROR( glGetShaderiv(mVertID, GL_COMPILE_STATUS, &result) )
	// get error/warning log length from compilation
	GLCHECKERROR( glGetShaderiv(mVertID, GL_INFO_LOG_LENGTH, &infoLogLength) )
	// Initialize errorLogBuffer to the right size
	std::string vertexErrorBuffer(infoLogLength + 1, 0);
	GLCHECKERROR( glGetShaderInfoLog(mVertID, infoLogLength, NULL, &vertexErrorBuffer[0]) )

	if ( result != GL_TRUE )
		{
		// failed
		throw GlideException("Errors in compilation process for vertex shader, " + mVertexFile, result, vertexErrorBuffer);
		}
	else
		{
		if ( infoLogLength )
			{
			// just warnings
			gLogger.LogTime() << "Warnings in compilation process for vertex shader, " << mVertexFile << '[' << vertexErrorBuffer << ']' << std::endl;
			}
		else
			{
			// no errors or warnings
			gLogger.LogTime() << "Vertex shader complation successful, " << mVertexFile << std::endl;
			}
		}

	// FRAGMENT LOADING

	// reset results
	result = GL_FALSE;
	infoLogLength = 0;
	
	// Get fragment code pointer
	const GLchar * pFragSource = fragCode.c_str();
	// get fragment source code size
	GLint fragSourceSize = fragCode.size() + 1;

	// Load source code into openGL
	GLCHECKERROR(glShaderSource(mFragID, 1, &pFragSource, &fragSourceSize))
	// tell openGL to compile fragment shader
	GLCHECKERROR(glCompileShader(mFragID));
	// get error status from compilation
	GLCHECKERROR(glGetShaderiv(mFragID, GL_COMPILE_STATUS, &result))
	// get error/warning log length from compilation
	GLCHECKERROR(glGetShaderiv(mFragID, GL_INFO_LOG_LENGTH, &infoLogLength))
	// Initialize errorLogBuffer to the right size
	std::string fragErrorBuffer(infoLogLength + 1, 0);
	GLCHECKERROR(glGetShaderInfoLog(mFragID, infoLogLength, NULL, &fragErrorBuffer[0]))

	if(result != GL_TRUE)
		{
		// failed
		throw GlideException("Errors in compilation process for fragment shader, " + mFragFile, result, fragErrorBuffer);
		}
	else
		{
		if(infoLogLength)
			{
			// just warnings
			gLogger.LogTime() << "Warnings in compilation process for fragment shader, " << mFragFile << '[' << fragErrorBuffer << ']' << std::endl;
			}
		else
			{
			// no errors or warnings
			gLogger.LogTime() << "Fragment shader complation successful, " << mFragFile << std::endl;
			}
		}

	// Both shaders compiled successfully
	gLogger.LogTime() << "Compiled vertex and fragment shader successfull." << std::endl;
	// Load into program

	GLCHECKERROR(mProgramID = glCreateProgram())
	GLCHECKERROR(glAttachShader(mProgramID, mVertID))
	GLCHECKERROR(glAttachShader(mProgramID, mFragID))
	GLCHECKERROR(glLinkProgram(mProgramID))

	// check linking program for errors
	// reset results
	result = GL_FALSE;
	infoLogLength = 0;

	GLCHECKERROR(glGetProgramiv(mProgramID, GL_LINK_STATUS, &result))
	GLCHECKERROR(glGetProgramiv(mProgramID, GL_INFO_LOG_LENGTH, &infoLogLength))
	std::string programLinkLog(infoLogLength + 1, 0);
	GLCHECKERROR(glGetProgramInfoLog(mProgramID, infoLogLength, NULL, &programLinkLog[0]) )

	if ( result != GL_TRUE )
		{
		throw GlideException("Failed to link programs with files vertex[" + mVertexFile + "] fragment[" + mFragFile + ']', result, programLinkLog); 
		}
	else
		{
		if ( infoLogLength )
			{
			gLogger.LogTime() << "Linked successfully with warnings[" << programLinkLog << ']' << std::endl;
			}
		else
			{
			gLogger.LogTime() << "Linked successfully with no warnings." << std::endl;
			}
		}
	}

RShader::Configuration::Configuration(const std::string & vertexFile, const std::string & fragFile)
	:
	Resource::ConfigType(vertexFile),
	mVertexFile(vertexFile),
	mFragFile(fragFile)
	{

	}

RShader::Configuration::~Configuration()
	{

	}
}