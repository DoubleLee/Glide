#pragma once
#pragma once

#include "BasicTypes.hpp"
#include "Resource.hpp"

#include <map>
#include <memory>

namespace gl
{

template<class ResType>
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	Void ResourceAdd( const ResourceConfig & config );

	ResType * ResourceGet( UniqueID id );

protected:
	std::map< UniqueID, std::unique_ptr<ResType > > mResources;
};

template<class ResType>
ResourceManager<ResType>::ResourceManager()
	{

	}

template<class ResType>
ResourceManager<ResType>::~ResourceManager()
	{

	}

template<class ResType>
Void ResourceManager<ResType>::ResourceAdd( const ResourceConfig & config )
	{
	auto result = mResources.find(config.GetID());

	if ( result == mResources.end() )
		{
		mResources.emplace( std::make_pair( config.GetID(), std::make_unique<ResType>(config) ) );
		}
	}

template<class ResType>
ResType * ResourceManager<ResType>::ResourceGet( UniqueID id )
	{
	auto result = mResources.find(id);

	if ( result != mResources.end() )
		{
		return result.second.get();
		}

	throw std::runtime_error("Failed to find resource with ID: " + std::to_string(id) );
	}
}