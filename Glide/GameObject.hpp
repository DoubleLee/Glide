#pragma once

#include "Component.hpp"

#include <map>
#include <memory>

namespace gl
{

class GameObject
{
public:
	typedef std::string TypeID;
public:
	GameObject( const TypeID & id );
	~GameObject();

	Void TypeIDSet( const TypeID & id );
	const TypeID & TypeIDGet() const;

	Void ComponentAdd( ComponentPtr & pComp );
	Component * ComponentGet( const Component::FamilyID & familyID );

private:
	TypeID mTypeID;

	typedef std::map< Component::FamilyID, ComponentPtr > ComponentMap;
	ComponentMap mComponents;
};

typedef std::unique_ptr<GameObject> GameObjectPtr;

}