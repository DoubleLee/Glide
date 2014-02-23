#pragma once
#ifndef GLCHECKERROR_HPP
#define GLCHECKERROR_HPP

#include <stdexcept>

#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

/**
* @brief The GLException class.
*
* This is the class to use for throwing an exception when an openGL error is detected.
*
* It inherits from std::exception
*/
class GLException : public std::exception
	{
	public:

		/**
		* @brief GLException
		* @param code The openGL error code.
		* @param line The line which the error occurred.
		* @param file The file which the error occurred.
		*/
		GLException(int code, int line, std::string file);

		/**
		* @brief what
		* @return The c-string to explain what happend.
		*/
		virtual const char * what() const NOEXCEPT;

	private:
		std::string mErrorString;
	};

/**
* @brief GLCHECKERROR macro.
*
* This is how you throw check gl commands for errors,
* it will throw an exception with all the relevant info.
*/
#define GLCHECKERROR( callCode ) { callCode; GLenum errorCode = glGetError(); if (errorCode != GL_NO_ERROR) {throw GLException( errorCode, __LINE__, __FILE__);} }

/**
* @brief GLCHECKERRORWARNING macro.
*
* Use this instead of GLCHECKERROR in dtors which should not throw exceptions,
* and other cases where you can't throw an exception.
*/
#define GLCHECKERRORWARNING( callCode ) { callCode; GLenum errorCode = glGetError(); if ( errorCode != GL_NO_ERROR) { std::cerr << "OpenGL error code: " << errorCode << '\n' << "File: " << __FILE__ << " Line: " << __LINE__ << '\n'; } }

#endif // GLCHECKERROR_HPP