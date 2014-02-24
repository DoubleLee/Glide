#pragma once

#include "BasicTypes.hpp"
#include "Resource.hpp"

#include <map>
#include <memory>
#include <string>

namespace gl
{

template< class ResType >
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	Void ResourceAdd( const ResourceConfig<typename ResType::CompareType> & config );

	ResType * ResourceGet(const typename ResType::CompareType & id);

protected:
	std::map< typename ResType::CompareType, std::unique_ptr< ResType > > mResources;
};

template< class ResType >
ResourceManager< ResType >::ResourceManager()
	{

	}

template< class ResType >
ResourceManager<ResType>::~ResourceManager()
	{

	}

template< class ResType >
Void ResourceManager<ResType>::ResourceAdd(const ResourceConfig<typename ResType::CompareType> & config)
	{
	auto result = mResources.find(config.GetID());

	if ( result == mResources.end() )
		{
		mResources.emplace( std::make_pair( config.GetID(), std::make_unique<ResType>(config) ) );
		}
	}

template< class ResType >
ResType * ResourceManager<ResType>::ResourceGet(const typename ResType::CompareType & id)
	{
	auto result = mResources.find(id);

	if ( result != mResources.end() )
		{
		return (*result).second.get();
		}

	throw std::runtime_error("Failed to find resource.");
	}
}