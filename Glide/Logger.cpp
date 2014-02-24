#include "Logger.hpp"

#include <fstream>
#include <iostream>

Logger gLogger;

Logger::Logger()
	:
	mpLogStream( std::make_unique<std::ofstream> ( "Log.txt", std::ios_base::out ) )
	{
	if ( !mpLogStream->is_open() )
		{
		throw std::runtime_error("Failed to create or open log file.");
		}

	(*mpLogStream) << "Opening file...\n";
	}


Logger::~Logger()
	{
	mpLogStream->flush();
	mpLogStream->close();
	}
