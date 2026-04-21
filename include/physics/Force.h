#pragma once

#include "physics/PhysicBase.h"

START_PHYSICS_NAMESPACE

class Force : public PhysicBase
{
public:
	Force() : PhysicBase(PhysicType::FORCE) {}
	
	virtual void applyForce() = 0;
};

END_PHYSICS_NAMESPACE