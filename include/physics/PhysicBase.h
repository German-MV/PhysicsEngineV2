#pragma once

#include <memory>
#include <string>
#include <glm/glm.hpp>

#define START_PHYSICS_NAMESPACE  namespace Physics {
#define END_PHYSICS_NAMESPACE    }

START_PHYSICS_NAMESPACE

enum class PhysicType
{
	OBJECT,
	CONSTRAINT,
	APPLICATION_POINT,
	FORCE,
	SYSTEM,
	NO_PHYSIC
};

std::string toStr(PhysicType physicType);

class PhysicBase
{
public:
	PhysicBase() : physicType(PhysicType::NO_PHYSIC) {}
	virtual ~PhysicBase() = default;

	PhysicType getPhysicType() const;

protected:
	PhysicBase(PhysicType physicType) : physicType(physicType) {}

	PhysicType physicType;
};


END_PHYSICS_NAMESPACE