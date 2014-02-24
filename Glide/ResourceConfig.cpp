#include "ResourceConfig.hpp"

namespace gl
{

ResourceConfig::ResourceConfig(const std::string & file)
	:
	mFileNamePath(file)
	{

	}

ResourceConfig::~ResourceConfig()
	{

	}


const std::string & ResourceConfig::GetFileNamePath() const
	{
	return mFileNamePath;
	}
}