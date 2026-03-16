#include "physics/DistConstraint.h"

#include "utils.h"

START_PHYSICS_NAMESPACE

void DistConstraint::solve(float deltaTime)
{
    if (deltaTime <= 0.0f) return;

    auto sp1 = p1.lock();
    auto sp2 = p2.lock();
    if (!sp1 || !sp2) return;

    glm::vec3 delta = sp2->getPosition() - sp1->getPosition();
    float length = glm::length(delta);
    if (length < EPSILON) return;

    glm::vec3 dir = delta / length;
    float C = length - restLength;

    float w1 = sp1->getEffectiveInverseMass( dir);
    float w2 = sp2->getEffectiveInverseMass(-dir);
    float W = w1 + w2;
    if (W <= EPSILON) return;

    float alpha = compliance / (deltaTime * deltaTime);

    // XPBD increment
    float deltaLambda = -(C + alpha * lambda) / (W + alpha);
    lambda += deltaLambda;

    glm::vec3 deltaX1 = -w1 * dir * deltaLambda;
    glm::vec3 deltaX2 =  w2 * dir * deltaLambda; 

    sp1->applyConstraintCorrection( dir, deltaLambda, w1);
    sp2->applyConstraintCorrection(-dir, deltaLambda, w2);
}


//void DistConstraint::solve(float deltaTime)
//{
//	auto sp1 = p1.lock();
//	auto sp2 = p2.lock();
//
//	if (!sp1 || !sp2) return;
//
//	glm::vec3 delta = sp2->getPosition() - sp1->getPosition();
//
//	float length = glm::length(delta);
//
//	if (length < EPSILON) return;
//
//	float w1 = sp1->getEffectiveInverseMass();
//	float w2 = sp2->getEffectiveInverseMass();
//	float W = w1 + w2;
//	if (W < EPSILON) return;
//
//	float compliance = 0.f;
//	float alpha = compliance / (deltaTime * deltaTime);
//
//	float lambda = (restLength - length) / length / (W + alpha);
//
//	glm::vec3 deltaX1 = -w1 * lambda * delta;
//	glm::vec3 deltaX2 =  w2 * lambda * delta;
//
//	sp1->applyConstraintCorrection(deltaX1);
//	sp2->applyConstraintCorrection(deltaX2);
//}

END_PHYSICS_NAMESPACE