#pragma once

#include "Resource.hpp"

#include <string>

namespace gl
{

/**
The default configuration for resources, simply takes in a file name.
If you need more data in your configuration inherit from this.
*/
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