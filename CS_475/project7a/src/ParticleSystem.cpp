#include "ParticleSystem.hpp"
#include "Project7a.hpp"

ParticleSystem * ParticleSystem::particleSystemSingleton;

ParticleSystem::ParticleSystem()
{
	ParticleSystem::particleSystemSingleton = this;
	// random parameters:
	WINDOWTITLE = "OpenCL/OpenGL Particle System -- Joe Parallel";
	GLUITITLE = "User Interface Window";

	// random parameters:
	XMIN = -100.0;
	XMAX = 100.0;
	YMIN = -100.0;
	YMAX = 100.0;
	ZMIN = -100.0;
	ZMAX = 100.0;

	VMIN = -100.;
	VMAX = 100.;

	NUM_PARTICLES = 1024 * 1024;
	LOCAL_SIZE = 32;
	CL_FILE_NAME = "src/particles.cl";
	CL_BINARY_NAME = "src/particles.nv";

	INIT_WINDOW_SIZE = 700; // window size in pixels

	drawDistance = 49172;
	ANGFACT = (float)M_PI / 512.0f;
	SCLFACT = 0.005f;
	MINSCALE = 0.001f;
	
	memset(&BACKCOLOR, 0, sizeof(BACKCOLOR));

	AXES_COLOR.x = 1.0f;
	AXES_COLOR.y = 0.5f;
	AXES_COLOR.z = 0.0f;
	
	AXES_WIDTH = 3.0f;

	GlobalWorkSize[0] = NUM_PARTICLES;
	GlobalWorkSize[1] = 1;
	GlobalWorkSize[2] = 1;
  
	LocalWorkSize[0] = LOCAL_SIZE;
	LocalWorkSize[1] = 1;
	LocalWorkSize[2] = 1;
}

ParticleSystem::~ParticleSystem()
{
    
}

//
// exit gracefully:
//

void ParticleSystem::Quit()
{
	Glui->close();
	glutSetWindow(MainWindow);
	glFinish();
	glutDestroyWindow(MainWindow);


	// 13. clean everything up:

	clReleaseKernel(Kernel);
	clReleaseProgram(Program);
	clReleaseCommandQueue(CmdQueue);
	clReleaseMemObject(CLParticlePosition);
	clReleaseMemObject(CLParticleColor);

	free(GLParticleVelocity);
}