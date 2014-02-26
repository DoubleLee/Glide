#include "ResourceConfig.hpp"

namespace gl
{

Resource::Configuration::Configuration(const std::string & file)
	:
	mFileNamePath(file)
	{

	}

Resource::Configuration::~Configuration()
	{

	}

const std::string & Resource::Configuration::GetFileNamePath() const
	{
	return mFileNamePath;
	}
}