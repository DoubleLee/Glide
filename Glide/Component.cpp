#include "Component.hpp"

namespace gl
{

Component::Component(const FamilyID & familyID, const TypeID & typeID, GameObject * pOwner)
	:
	mFamilyID(familyID),
	mTypeID(typeID),
	mpOwner(pOwner)
	{

	}

Component::Component()
	:
	mpOwner(nullptr)
	{

	}

Component::~Component()
	{
	}

const Component::FamilyID & Component::GetFamilyID() const
	{
	return mFamilyID;
	}

const Component::TypeID & Component::GetTypeID() const
	{
	return mTypeID;
	}

Void Component::SetFamilyID( const FamilyID & id )
	{
	mFamilyID = id;
	}

Void Component::SetTypeID( const TypeID & id )
	{
	mTypeID = id;
	}

GameObject * Component::GetOwner() const
	{
	return mpOwner;
	}

Void Component::SetOwner( GameObject * pObject )
	{
	mpOwner = pObject;
	}

Void Component::Update()
	{

	}
}