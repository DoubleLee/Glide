#pragma once
#include "Resource.hpp"
#include "ResourceConfig.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <GL/glew.h>

namespace gl
{

/**
RShader class represents a shader program.
A shader program is made of two files at least.
There must be a vertex shader and a fragment shader.

TODO: write a function that loads vertex and fragment independantly.
This way you can write a virtual LoadShader and have it load other shader like geometry
and tesselation.
*/
class RShader : public Resource
{
public:
	class Configuration;
	typedef RShader::Configuration ConfigType;

public:
	RShader(const RShader::Configuration & config);
	virtual ~RShader();

	std::string GetVertexFile() const;
	std::string GetFragFile() const;

	Void SetUniform(const char * pUniformName, const glm::mat4 & mat);
	Void SetUniform(const char * pUniformName, const glm::vec3 & vec3);
	Void SetUniform(const char * pUniformName, const GLfloat f);
	Void SetUniform(const char * pUniformName, const GLint i);
	Void SetUniform(const char * pUniformName, const GLboolean b);

	/**
	Binds this shader program to openGL rendering system.
	*/
	Void Bind() const;
	/**
	Binds null program to openGL rendering system.
	*/
	static Void BindNull();

protected:
	Void LoadShaders();
	std::string mVertexFile;
	std::string mFragFile;

	GLuint mProgramID;
	GLuint mVertID;
	GLuint mFragID;
};

/**
RShader needs at least 2 files so we inherit from the default
resource config and then add our files.
*/
class RShader::Configuration : public Resource::ConfigType
{
public:
	Configuration(const std::string & vertexFile, const std::string & fragFile);
	virtual ~Configuration();

	std::string mVertexFile;
	std::string mFragFile;
};

}