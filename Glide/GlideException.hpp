#pragma once

#include "BasicTypes.hpp"

#include <stdexcept>

namespace gl
{

/**
Use this to throw exceptions,
it is std::except compatable.

Any time this is throw the data is also wrote to the gLogger.
*/
class GlideException : public std::exception
{
public:
	GlideException( const std::string & message );
	GlideException( const std::string & message, Long code );
	GlideException( const std::string & message, Long code, const std::string & codeStr );

	virtual const char * what() const;

protected:
	Void BuildMessage(const std::string & message);
	Void BuildMessage_Code(const std::string & message, Long code);
	Void BuildMessage_Code_CodeStr(const std::string & message, Long code, const std::string & errorCodeStr);

	std::string mWhat;
};
}