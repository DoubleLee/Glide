#pragma once

#include <string>

namespace gl
{

class ResourceConfig
{
public:
	ResourceConfig(const std::string & file);
	virtual ~ResourceConfig();

	const std::string & GetFileNamePath() const;

protected:
	std::string mFileNamePath;
};

}