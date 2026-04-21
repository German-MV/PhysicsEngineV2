#include "physics/PhysicBase.h"

START_PHYSICS_NAMESPACE

std::string toStr(PhysicType physicType)
{
	switch (physicType)
	{
	case PhysicType::OBJECT:
		return "OBJECT";
	case PhysicType::APPLICATION_POINT:
		return "APPLICATION_POINT";
	case PhysicType::FORCE:
		return "FORCE";
	case PhysicType::SYSTEM:
		return "SYSTEM";
	case PhysicType::NO_PHYSIC:
		return "NO_PHYSIC";
	default:
		return "UNKNOWN_PHYSIC_TYPE";
	}
}

PhysicType PhysicBase::getPhysicType() const { return physicType; }

END_PHYSICS_NAMESPACE