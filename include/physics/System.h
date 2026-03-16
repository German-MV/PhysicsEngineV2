#pragma once

#include "Physic.h"
#include "physics/Object.h"
#include "physics/Force.h"
#include "physics/ApplicationPoint.h"
#include "physics/Constraint.h"

#include <vector>

START_PHYSICS_NAMESPACE

class System : public Physic
{
protected:
	using PtrObj = std::shared_ptr<Object>;
	using PtrFrc = std::shared_ptr<Force>;
	using PtrApp = std::shared_ptr<ApplicationPoint>;
	using PtrCst = std::shared_ptr<Constraint>;

public:
	System() : Physic(PhysicType::SYSTEM) {}

protected:
	friend class PhysicsEngine;

	virtual void addToEngine(PhysicsEngine& engine) = 0;
};

END_PHYSICS_NAMESPACE