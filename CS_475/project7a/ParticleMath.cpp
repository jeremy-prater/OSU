#include "Project7a.hpp"

float4 ParticleSystem::GetXYZfromPolar(float distanceFromOrigin, float theta, float phi)
{
	float4 point;

	point.x = distanceFromOrigin * cosf(theta) * sinf(phi);
	point.y = distanceFromOrigin * sinf(theta) * cosf(phi);
	point.z = distanceFromOrigin * cosf(phi);
	point.w = 1.;

	return point;
}
