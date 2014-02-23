#include "GLCheckError.hpp"

#include "GL/glew.h"

#include <string>

std::string StripPath(const std::string & fileName)
	{
	char lookFor;
#ifdef WIN32
	lookFor = '\\';
#else
	lookFor = '/';
#endif
	std::string::size_type indexLastSlash = fileName.find_last_of(lookFor);
	if(indexLastSlash == std::string::npos)
		{
		return fileName;
		}
	else
		{
		++indexLastSlash; // move past '\'
		if(indexLastSlash < fileName.size())
			{
			return fileName.substr(indexLastSlash);
			}
		else
			{
			return fileName.substr(--indexLastSlash);
			}
		}

	}

GLException::GLException(int code, int line, std::string filePath)
	{
	std::string file = StripPath(filePath);
	std::string codeStr = std::to_string(code);
	std::string glErrorStr = (char*) glewGetErrorString(static_cast<GLenum>(code));

	mErrorString = "OpenGL threw an error with code: ";
	mErrorString += codeStr;
	mErrorString += '\n';
	mErrorString += "File: " + file;
	mErrorString += " Line: " + std::to_string(line);
	mErrorString += '\n';
	mErrorString += "GL error string: ";
	mErrorString += glErrorStr;
	mErrorString += '\n';
	}

const char * GLException::what() const NOEXCEPT
	{
	return mErrorString.c_str();
	}
