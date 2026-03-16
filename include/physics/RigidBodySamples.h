#pragma once

#include "physics/RigidBody.h"

START_PHYSICS_NAMESPACE

class THandle : private RigidBody
{
public:
	THandle(
		float mass,
		float length,
		float radius
	);
};

END_PHYSICS_NAMESPACE