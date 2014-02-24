#pragma once

#include <iosfwd>
#include <memory>

class Logger
{
public:
	Logger();
	~Logger();


private:
	std::unique_ptr< std::ofstream > mpLogStream;
};

