#pragma once
#include "Resource.hpp"
#include "ResourceConfig.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <GL/glew.h>

namespace gl
{

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

	Void Bind() const;
	static Void BindNull();

protected:
	Void LoadShaders();
	std::string mVertexFile;
	std::string mFragFile;

	GLuint mProgramID;
	GLuint mVertID;
	GLuint mFragID;
};

class RShader::Configuration : public Resource::ConfigType
{
public:
	Configuration(const std::string & vertexFile, const std::string & fragFile);
	virtual ~Configuration();

	std::string mVertexFile;
	std::string mFragFile;
};

}