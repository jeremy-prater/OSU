#include "Project7a.hpp"

void ParticleSystem::ResetParticles()
{
	glBindBuffer(GL_ARRAY_BUFFER, GLParticlePosition);
	float4 * points = (float4 *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		// Particle points are generated 1000 units from origin.
		float distanceFromOrigin = 300;
		float theta = ParticleSystem::Ranf(0, M_PI);
		float phi = ParticleSystem::Ranf(0, 2 * M_PI);
		points[i] = ParticleSystem::GetXYZfromPolar(distanceFromOrigin, theta, phi);
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);


	glBindBuffer(GL_ARRAY_BUFFER, GLParticleColor);
	float4 * colors = (float4 *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		colors[i].x = Ranf(.3f, 1.);
		colors[i].y = Ranf(.3f, 1.);
		colors[i].z = Ranf(.3f, 1.);
		colors[i].w = 1.;
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);


	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		GLParticleVelocity[i].x = Ranf(VMIN, VMAX);
		GLParticleVelocity[i].y = Ranf(0., VMAX);
		GLParticleVelocity[i].z = Ranf(VMIN, VMAX);
	}
}

float ParticleSystem::Ranf(float low, float high)
{
	long random();		// returns integer 0 - TOP

	float r = (float)rand();
	return(low + r * (high - low) / (float)RAND_MAX);
}