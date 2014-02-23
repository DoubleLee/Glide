#pragma once

#include "BasicTypes.hpp"

#include <string>

namespace gl
{
class ResourceConfig;

class Resource
{
public:
	Resource(const ResourceConfig & config);
	Resource( Resource && other );
	Resource( const Resource & other ) = delete;
	Resource & operator = ( const Resource & other ) = delete;
	virtual ~Resource();

	const std::string & GetFile() const;
	UniqueID GetID() const;

protected:
	std::string mFile;
	UniqueID mID;
};

class ResourceConfig
{
public:
	ResourceConfig( const std::string & file, const UniqueID id );
	virtual ~ResourceConfig();

	const std::string & GetFile() const;
	UniqueID GetID() const;

protected:
	std::string mFile;
	UniqueID mID;
};

}