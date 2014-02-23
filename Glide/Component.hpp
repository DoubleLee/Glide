#pragma once

#include "BasicTypes.hpp"

#include <string>
#include <memory>

namespace gl
{

class GameObject;

class Component
{
public:
	typedef std::string FamilyID;
	typedef std::string TypeID;
public:
	Component(const FamilyID & familyID, const TypeID & typeID, GameObject * pOwner);
	Component();

	virtual ~Component();

	const FamilyID & GetFamilyID() const;
	const TypeID & GetTypeID() const;

	Void SetFamilyID(const FamilyID & id);
	Void SetTypeID(const TypeID & id);

	GameObject * GetOwner() const;
	Void SetOwner( GameObject * pObject );

	virtual Void Update();

private:
	GameObject * mpOwner;

	FamilyID mFamilyID;
	TypeID mTypeID;
};

typedef std::unique_ptr<Component> ComponentPtr;
}