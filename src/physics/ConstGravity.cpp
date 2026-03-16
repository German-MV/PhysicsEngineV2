#include <physics/ConstGravity.h>

START_PHYSICS_NAMESPACE

ConstGravity::ConstGravity(const glm::vec3& gravity, std::vector<std::shared_ptr<Object>> object) : gravity(gravity)
{
	for (auto& obj : object)
		targets.push_back(obj);
}

void ConstGravity::applyForce()
{
	for(auto& weakObj : targets)
	{
		if (auto obj = weakObj.lock())
		{
			obj->applyAcceleration(gravity);
		}
	}
}

END_PHYSICS_NAMESPACE