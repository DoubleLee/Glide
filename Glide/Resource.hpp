#pragma once

#include "BasicTypes.hpp"


#include <string>


namespace gl
{
std::string StripPath(const std::string & fileNamePath);

class Resource
{
public:
	class Configuration;
	typedef Resource::Configuration ConfigType;
public:
	/*
	Resource, base resource class.  It's template argument is the comparer by which will be returned by GetID()
	and also is the template type of the ResourceConfig base class.
	*/
	Resource(const Resource::Configuration & config);
	Resource( Resource && other );
	Resource( const Resource & other ) = delete;
	Resource & operator = ( const Resource & other ) = delete;
	virtual ~Resource();

	const std::string & GetFile() const;

protected:
	std::string mFile;
};

}