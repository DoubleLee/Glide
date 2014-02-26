#include "GlideException.hpp"

#include "Logger.hpp"
#include <string>

namespace gl
{

GlideException::GlideException( const std::string & message )
	:
	std::exception(),
	mWhat()
	{
	BuildMessage(message);
	gLogger.LogTime() << mWhat << std::endl;
	}

GlideException::GlideException( const std::string & message, Long code )
	:
	std::exception(),
	mWhat()
	{
	BuildMessage_Code(message,code);

	gLogger.LogTime() << mWhat << std::endl;
	}

GlideException::GlideException(const std::string & message, Long code, const std::string & codeStr)
	:
	std::exception(),
	mWhat()
	{
	BuildMessage_Code_CodeStr(message, code, codeStr);

	gLogger.LogTime() << mWhat << std::endl;
	}

Void GlideException::BuildMessage(const std::string & message)
	{
	mWhat = "Glide Exception thrown: Message[";
	mWhat += message;
	mWhat += ']';
	}

Void GlideException::BuildMessage_Code(const std::string & message, Long code)
	{
	BuildMessage(message);
	mWhat += " Code[";
	mWhat += std::to_string(code);
	mWhat += ']';
	}

Void GlideException::BuildMessage_Code_CodeStr(const std::string & message, Long code, const std::string & errorCodeStr)
	{
	BuildMessage_Code(message, code);
	mWhat += " CodeStr[";
	mWhat += errorCodeStr;
	mWhat += ']';
	}

const char * GlideException::what() const
	{
	return mWhat.c_str();
	}
}