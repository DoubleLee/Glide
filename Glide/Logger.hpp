#pragma once

#include <fstream>

namespace gl
{

/*
Logger is used for logging text to file.
There is a global one for most uses.
Typical use case is below
gLogger.LogTime() << "Some error occured, code: " << errorCode << std::endl;
The std::endl is important because it adds a new line but also it
flushes the log buffer to file.  So even when a crash occurs somewhere,
each log has been wrote to file immediately.
*/
class Logger : public std::ofstream
{
public:
	Logger( const std::string & logFile );
	~Logger();

	// puts the time in the log
	// returns a reference to itself
	// so call site looks like this
	// gLogger.LogTime() << "Error some where. Code: " << errorCode << std::endl;
	Logger & LogTime();
};

extern Logger gLogger;
}