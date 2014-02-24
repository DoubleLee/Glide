#include "GameObject.hpp"


namespace gl
{

GameObject::GameObject(const TypeID & id)
	:
	mTypeID(id)
	{

	}

GameObject::~GameObject()
	{

	}

Void GameObject::TypeIDSet( const TypeID & id )
	{
	mTypeID = id;
	}

const GameObject::TypeID & GameObject::TypeIDGet() const
	{
	return mTypeID;
	}

Void GameObject::ComponentAdd( ComponentPtr & pComp )
	{
	if( !(mComponents.emplace(std::make_pair(pComp->GetFamilyID(), std::move(pComp))).second) )
		{
		throw std::runtime_error("Failed to insert component, FamilyID may already exist.");
		}
	}

Component * GameObject::ComponentGet( const Component::FamilyID & familyID )
	{
	// make sure that nullptr is return if it doesn't exist
	auto result = mComponents.find(familyID);
	if ( result != mComponents.end() )
		{
		return (*result).second.get();
		}
	else
		return nullptr;
	}

Void GameObject::CalculateWorlds( glm::mat4 & globalWorld )
	{
	mGlobalWorld = globalWorld * mLocalWorld;

	for ( auto & pIndex : mChildren )
		{
		pIndex->CalculateWorlds( mGlobalWorld );
		}
	}

Void GameObject::ChildAdd( GameObjectPtr & pChild )
	{
	if ( pChild )
		{
		mChildren.emplace_back( std::move(pChild) );
		}
	}

}