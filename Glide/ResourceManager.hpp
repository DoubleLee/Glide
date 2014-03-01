#pragma once

#include "BasicTypes.hpp"
#include "Resource.hpp"
#include "GlideException.hpp"

#include <map>
#include <memory>
#include <string>

namespace gl
{

/**
template class for managing resources.
Simple manages resources, by a template key type and the tempate resource type.
You can use any type that can be compaired as a key.
Resources are stored internally in a map.
To create and load a resource call ResourceAdd with the configuration type of your resource and the
key you wish to use for that resource.
You can get the resource pointer by calling ResourceGet with the key.
*/
template< class ResType, class KeyType >
class ResourceManager
{
public:
	inline ResourceManager();
	inline ~ResourceManager();

	/**
	ResourceAdd adds resource to the map.  Will create the resource internally.
	The Key is the template paramter on ResourceConfig.  The manager will grab the key from the 
	config.
	*/
	inline Void ResourceAdd( const typename ResType::ConfigType & config, const KeyType & key );

	/**
	ResourceGet returns a resource pointer by the map key, which is the Comparer template argument of the resource.
	*/
	inline ResType * ResourceGet(const KeyType & key);

	inline UInt Size() const;

protected:
	std::map< KeyType, std::unique_ptr< ResType > > mResources;
};

template< class ResType, class KeyType >
inline ResourceManager< ResType, KeyType >::ResourceManager()
	{

	}

template< class ResType, class KeyType >
inline ResourceManager<ResType, KeyType>::~ResourceManager()
	{

	}

template< class ResType, class KeyType >
inline Void ResourceManager<ResType, KeyType>::ResourceAdd(const typename ResType::ConfigType & config, const KeyType & key)
	{
	auto result = mResources.find(key);

	if ( result == mResources.end() )
		{
		mResources.emplace( std::make_pair( key, std::make_unique<ResType>(config) ) );
		}
	}

template< class ResType, class KeyType >
inline ResType * ResourceManager<ResType, KeyType>::ResourceGet(const KeyType & id)
	{
	auto result = mResources.find(id);

	if ( result != mResources.end() )
		{
		return (*result).second.get();
		}

	throw GlideException("Failed to find resource.");
	}

template< class ResType, class KeyType >
inline UInt ResourceManager<ResType, KeyType>::Size() const
	{
	return mResources.size();
	}
}