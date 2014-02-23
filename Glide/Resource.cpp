#include "Resource.hpp"

using namespace std;
namespace gl
{
Resource::Resource(Resource && other)
	:
	mFile(std::move(other.mFile)),
	mID(std::move(other.mID))
	{

	}

Resource::Resource(const ResourceConfig & config)
	:
	mFile(config.GetFile()),
	mID(config.GetID())
	{

	}

Resource::~Resource()
	{

	}

const string & Resource::GetFile() const
	{
	return mFile;
	}

UniqueID Resource::GetID() const
	{
	return mID;
	}

ResourceConfig::ResourceConfig( const string & file, const UniqueID id )
	:
	mFile(file),
	mID(id)
	{

	}

ResourceConfig::~ResourceConfig()
	{

	}

const string & ResourceConfig::GetFile() const
	{
	return mFile;
	}

UniqueID ResourceConfig::GetID() const
	{
	return mID;
	}
}