#pragma once

#include "BasicTypes.hpp"

#include <stdexcept>

namespace gl
{
class GlideException : public std::exception
{
public:
	GlideException( const std::string & message );
	GlideException( const std::string & message, ULong code );
	GlideException( const std::string & message, ULong code, const std::string & codeStr );

	virtual const char * what() const;

protected:
	Void BuildMessage(const std::string & message);
	Void BuildMessage_Code(const std::string & message, ULong code);
	Void BuildMessage_Code_CodeStr(const std::string & message, ULong code, const std::string & errorCodeStr);

	std::string mWhat;
};
}