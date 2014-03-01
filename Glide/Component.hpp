#pragma once

#include "BasicTypes.hpp"

#include <string>
#include <memory>

namespace gl
{

class GameObject;

/**
Component is the base class for all components.
*/
class Component
{
public:
	/**
	Every direct child of Component should have a unique family id.
	*/
	typedef std::string FamilyID;
	/**
	If you need to differentiate between family components use this TypeID
	*/
	typedef std::string TypeID;
public:
	Component(const FamilyID & familyID, const TypeID & typeID, GameObject * pOwner);
	Component();

	virtual ~Component();

	/**
	Returns the family id.
	*/
	const FamilyID & GetFamilyID() const;

	/**
	returns the type id.
	*/
	const TypeID & GetTypeID() const;

	Void SetFamilyID(const FamilyID & id);
	Void SetTypeID(const TypeID & id);

	GameObject * GetOwner() const;
	Void SetOwner( GameObject * pObject );

	/**
	virtual call to update components.
	*/
	virtual Void Update();

private:
	GameObject * mpOwner;

	FamilyID mFamilyID;
	TypeID mTypeID;
};

typedef std::unique_ptr<Component> ComponentPtr;
}