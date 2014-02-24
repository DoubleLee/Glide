#pragma once

#include "Component.hpp"

#include <map>
#include <memory>
#include <vector>

#include "glm/mat4x4.hpp"

namespace gl
{
class GameObject;

typedef std::unique_ptr<GameObject> GameObjectPtr;

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

	Void CalculateWorlds( glm::mat4 & globalWorld );

	Void ChildAdd( GameObjectPtr & pChild );

private:
	TypeID mTypeID;

	typedef std::map< Component::FamilyID, ComponentPtr > ComponentMap;
	ComponentMap mComponents;

	typedef std::vector< GameObjectPtr > GameObjects;
	GameObjects mChildren;

	glm::mat4 mLocalWorld;
	glm::mat4 mGlobalWorld;
};

}