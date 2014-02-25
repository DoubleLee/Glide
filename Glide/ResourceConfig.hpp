#pragma once

#include "Resource.hpp"

#include <string>

namespace gl
{

class Resource::Configuration
{
public:
	Configuration(const std::string & file);
	virtual ~Configuration();

	const std::string & GetFileNamePath() const;

protected:
	std::string mFileNamePath;
};

}