#include "GameObject.hpp"

#include "Logger.hpp"
#include "GlideException.hpp"
#include "CRender.hpp"

namespace gl
{

GameObject::GameObject(const TypeID & id)
	:
	mTypeID(id),
	mpParent(nullptr)
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

GameObject * GameObject::FindChildByID(const TypeID & id)
	{
	if ( mTypeID == id )
		return this;
	else
		{
		for ( UInt i = 0; i < mChildren.size(); ++i )
			{
			GameObject * pReturned = mChildren[i]->FindChildByID(id);
			if ( pReturned )
				return pReturned;
			}
		return nullptr;
		}
	}

Void GameObject::ComponentAdd( ComponentPtr && pComp )
	{
	if( !(mComponents.emplace(std::make_pair(pComp->GetFamilyID(), std::move(pComp))).second) )
		{
		throw GlideException("Failed to insert component, FamilyID may already exist.");
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

Void GameObject::ChildAdd( GameObjectPtr && pChild )
	{
	if ( pChild )
		{
		pChild->SetParent(this);
		mChildren.emplace_back( std::move(pChild) );
		}
	else
		{
		gLogger.LogTime() << "GameObject requested to add child, but pointer was nullptr." << std::endl;
		}
	}

Void GameObject::ChildRelease( GameObject * pChild )
	{
	for ( auto iter = mChildren.begin(); iter != mChildren.end(); ++iter )
		{
		if ( (*iter).get() == pChild )
			{
			(*iter).release();
			mChildren.erase( iter );
			return;
			}
		}

	gLogger.LogTime() << "GameObject requested to remove child that didn't exist. address: " << pChild << std::endl;
	}

UInt GameObject::ChildCount() const
	{
	return mChildren.size();
	}

Void GameObject::SetParent( GameObject * pParent )
	{
	mpParent = pParent;
	}

glm::mat4 & GameObject::GetLocalWorld()
	{
	return mLocalWorld;
	}

const glm::mat4 & GameObject::GetGlobalWorld() const
	{
	return mGlobalWorld;
	}

Void GameObject::SetLocalWorld( const glm::mat4 & localWorld )
	{
	mLocalWorld = localWorld;
	}

Void GameObject::Render(const glm::mat4 & camera)
	{
	CRender * pRender = static_cast<CRender*>(ComponentGet("Render"));

	if ( pRender )
		pRender->Render(camera);

	for ( UInt i = 0; i < mChildren.size(); ++i )
		{
		mChildren[i]->Render(camera);
		}
	}
}