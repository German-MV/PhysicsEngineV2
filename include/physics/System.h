#pragma once

#include "PhysicBase.h"
#include "physics/Object.h"
#include "physics/Force.h"
#include "physics/ApplicationPoint.h"
#include "physics/Constraint.h"

#include <vector>

START_PHYSICS_NAMESPACE

class System : public PhysicBase
{
protected:
	using PtrObj = std::shared_ptr<Object>;
	using PtrFrc = std::shared_ptr<Force>;
	using PtrApp = std::shared_ptr<ApplicationPoint>;
	using PtrCst = std::shared_ptr<Constraint>;

public:
	System() : PhysicBase(PhysicType::SYSTEM) {}

protected:
	friend class PhysicsEngine;

	virtual void addToEngine(PhysicsEngine& engine) = 0;
	virtual void removeFromEngine(PhysicsEngine& engine) {};
};

END_PHYSICS_NAMESPACE