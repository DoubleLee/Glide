#include "Logger.hpp"

#include <fstream>
#include <iostream>

namespace gl
{

Logger gLogger("Log.txt");

Logger::Logger(const std::string & logFile)
	{
	this->open(logFile, std::ios_base::out);

	if ( !is_open() )
		throw std::runtime_error("Failed to open log file.");
	}

Logger::~Logger()
	{
	flush();
	close();
	}

}