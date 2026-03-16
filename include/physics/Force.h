#pragma once

#include "physics/Physic.h"

START_PHYSICS_NAMESPACE

class Force : public Physic
{
public:
	Force() : Physic(PhysicType::FORCE) {}
	
	virtual void applyForce() = 0;
};

END_PHYSICS_NAMESPACE