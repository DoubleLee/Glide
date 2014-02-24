#include "Logger.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include <chrono>

using namespace std;

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
	// This code only runs if the program doesn't crash.
	// As long as the log call sites end with std::endl 
	// everything has been flushed to file already
	// so even during a crash the log up to that point is
	// in the file.
	(*this) << '\n';
	LogTime() << "Closing file correctly." << std::endl;
	close();
	}

Logger & Logger::LogTime()
	{
	time_t rawTime = chrono::system_clock::to_time_t(chrono::system_clock::now());

	string buffer;
	buffer.resize(30, 0);

	strftime(&buffer[0], buffer.size(), "%c", localtime(&rawTime));
	
	buffer.resize(strlen(&buffer[0]));
	buffer += "  ";
	(*this) << buffer;
	return *this;
	}
}