#include "physics/Constraint.h"

START_PHYSICS_NAMESPACE

void Constraint::resetLambda() { lambda = 0.f; }

void Constraint::setCompliance(float newCompliance) { compliance = newCompliance; }

float Constraint::getCompliance() const { return compliance; }

END_PHYSICS_NAMESPACE