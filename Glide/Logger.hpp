#pragma once

#include <fstream>

namespace gl
{

class Logger : public std::ofstream
{
public:
	Logger();
	~Logger();
};

extern Logger gLogger;
}