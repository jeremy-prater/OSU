#include "ParticleSystem.hpp"


ParticleSystem::ParticleSystem()
{
    size_t GlobalWorkSize[3] = { NUM_PARTICLES, 1, 1 };
    size_t LocalWorkSize[3]  = { LOCAL_SIZE,    1, 1 };
}

ParticleSystem::~ParticleSystem()
{
    
}