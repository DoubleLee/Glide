#pragma once

#include "BasicTypes.hpp"


#include <string>


namespace gl
{
std::string StripPath(const std::string & fileNamePath);

template<class TypeID>
class ResourceConfig;

template< class Compare >
class Resource
{
public:
	// this is what the resource manager references to use as its key type.
	typedef Compare CompareType;
public:
	/*
	Resource, base resource class.  It's template argument is the comparer by which will be returned by GetID()
	and also is the template type of the ResourceConfig base class.
	*/
	Resource(const ResourceConfig<Compare> & config);
	Resource( Resource<Compare> && other );
	Resource( const Resource<Compare> & other ) = delete;
	Resource<Compare> & operator = ( const Resource<Compare> & other ) = delete;
	virtual ~Resource();

	const std::string & GetFile() const;
	Compare GetID() const;

protected:
	std::string mFile;
	Compare mID;
};

template< class Compare >
Resource<Compare>::Resource(Resource<Compare> && other)
	:
	mFile(std::move(other.mFile)),
	mID(std::move(other.mID))
	{

	}

template< class Compare >
Resource<Compare>::Resource(const ResourceConfig<Compare> & config)
	:
	mFile(config.GetFileNamePath()),
	mID(config.GetID())
	{

	}

template< class Compare >
Resource<Compare>::~Resource()
	{

	}

template< class Compare >
const std::string & Resource<Compare>::GetFile() const
	{
	return mFile;
	}

template< class Compare >
Compare Resource<Compare>::GetID() const
	{
	return mID;
	}

// RESOURCE CONFIG

template< class Compare >
class ResourceConfig
{
public:
	ResourceConfig(const std::string & file, const Compare & id);
	virtual ~ResourceConfig();

	const std::string & GetFileNamePath() const;
	const Compare & GetID() const;

protected:
	std::string mFileNamePath;
	Compare mID;
};

template< class Compare>
ResourceConfig<Compare>::ResourceConfig(const std::string & file, const Compare & id)
	:
	mFileNamePath(file),
	mID(id)
	{

	}

template< class Compare>
ResourceConfig<Compare>::~ResourceConfig()
	{

	}

template< class Compare>
const std::string & ResourceConfig<Compare>::GetFileNamePath() const
	{
	return mFileNamePath;
	}

template< class Compare>
const Compare & ResourceConfig<Compare>::GetID() const
	{
	return mID;
	}

}