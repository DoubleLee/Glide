#pragma once

#include <fstream>

namespace gl
{

class Logger : public std::ofstream
{
public:
	Logger( const std::string & logFile );
	~Logger();
};

extern Logger gLogger;
}