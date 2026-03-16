#include "physics/Object.h"

START_PHYSICS_NAMESPACE

std::string toStr(ObjectType objectType)
{
	switch (objectType)
	{
	case ObjectType::PARTICLE:
		return "PARTICLE";
	case ObjectType::RIGID_BODY:
		return "RIGID_BODY";
	case ObjectType::NO_OBJECT:
		return "NO_OBJECT";
	default:
		return "UNKNOWN_OBJECT_TYPE";
	}
}

Object::Object() :
	Physic(PhysicType::OBJECT), objectType(ObjectType::NO_OBJECT) {}

ObjectType Object::getObjectType() const  { return objectType; }

Object::Object(ObjectType objectType) : 
	Physic(PhysicType::OBJECT), objectType(objectType) {}

END_PHYSICS_NAMESPACE