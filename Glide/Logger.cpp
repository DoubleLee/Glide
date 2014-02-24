#include "Logger.hpp"

#include <fstream>
#include <iostream>

namespace gl
{

Logger gLogger;

Logger::Logger()
	{
	this->open("Log.txt", std::ios_base::out);

	if ( !is_open() )
		throw std::runtime_error("Failed to open log file.");
	}

Logger::~Logger()
	{
	flush();
	close();
	}

}