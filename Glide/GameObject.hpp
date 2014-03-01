#pragma once

#include "Component.hpp"

#include <map>
#include <memory>
#include <vector>

#include "glm/mat4x4.hpp"

namespace gl
{
class GameObject;

/// convenience typedef for unique_ptr<GameObject>
typedef std::unique_ptr<GameObject> GameObjectPtr;

/**
GameObject are the actual objects in the scene.

They are capable of Node hiarchy, and transformations too.

GameObjects also store Components which handle the GameObjects
functionality and data.
*/
class GameObject
{
public:
	typedef std::string TypeID;
public:
	GameObject( const TypeID & id );
	~GameObject();

	Void TypeIDSet( const TypeID & id );
	const TypeID & TypeIDGet() const;

	GameObject * FindChildByID( const TypeID & id );

	Void ComponentAdd( ComponentPtr && pComp );
	Component * ComponentGet( const Component::FamilyID & familyID );

	Void CalculateWorlds( const glm::mat4 & globalWorld );

	Void ChildAdd( GameObjectPtr && pChild ); // may need & not && we'll see
	GameObjectPtr && ChildRelease( GameObject * pChild );

	UInt ChildCount() const;

	Void SetParent(GameObject * pParent);

	glm::mat4 & GetLocalWorld();
	const glm::mat4 & GetGlobalWorld() const;

	Void SetLocalWorld( const glm::mat4 & localWorld );

	Void Render(const glm::mat4 & camera);

private:
	GameObject * mpParent;
	TypeID mTypeID;

	typedef std::map< Component::FamilyID, ComponentPtr > ComponentMap;
	ComponentMap mComponents;

	typedef std::vector< GameObjectPtr > GameObjects;
	GameObjects mChildren;

	glm::mat4 mLocalWorld;
	glm::mat4 mGlobalWorld;
};

}