#pragma once
#include "Physic.h"

START_PHYSICS_NAMESPACE

enum class ObjectType
{
	PARTICLE, 
	RIGID_BODY,
	NO_OBJECT
};

std::string toStr(ObjectType objectType);

class Object : public Physic
{
public:
	Object();

	ObjectType getObjectType() const;

	virtual void update(float deltaTime) = 0;

	virtual void applyAcceleration(const glm::vec3& acceleration) = 0;
	
	virtual float getMass() const { return 0.f; }
	virtual float getCharge() const { return 0.f; }

protected:

	Object(ObjectType objectType);
	
	virtual void correctVel(float deltaTime) = 0;

	ObjectType objectType;

	friend class PhysicsEngine;
};

END_PHYSICS_NAMESPACE