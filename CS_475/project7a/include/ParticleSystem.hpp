#ifndef PARTICLE_SYSTEM
#define PARTICLE_SYSTEM

#define _USE_MATH_DEFINES
#include <math.h>

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4996)
#endif

#ifdef WIN32
#include "glew.h"
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"
#include "glui.h"

#include "cl.h"
#include "cl_gl.h"

#include "OpenCL.hpp"
#include "dataTypes.hpp"

class PartitleSystem
{
public:
	PartitleSystem();
    ~PartitleSystem();
    //
    // function prototypes:
    //

    inline
    float
    SQR( float x )
    {
        return x * x;
    }

    void	Animate( );
    void	Axes( float );
    void	Buttons( int );
    void	Display( );
    void	DoRasterString( float, float, float, char * );
    void	DoStrokeString( float, float, float, float, char * );
    void	InitCL( );
    void	InitGlui( );
    void	InitGraphics( );
    void	InitLists( );
    bool	IsCLExtensionSupported( const char * );
    void	Keyboard( unsigned char, int, int );
    void	MouseButton( int, int, int, int );
    void	MouseMotion( int, int );
    void	PrintCLError( cl_int, char * = "", FILE * = stderr );
    void	Quit( );
    float	Ranf( float, float );
    void	Reset( );
    void	ResetParticles( );
    void	Resize( int, int );
    void	Traces( int );
    void	Visibility( int );
    void	WriteFrame( );
    void    Wait(cl_command_queue);

private:

    // non-constant global variables:
    int	ActiveButton;		// current button that is down
    GLuint	AxesList;		// list to hold the axes
    int	AxesOn;			// ON or OFF
    int	Frame;
    GLUI *	Glui;			// instance of glui window
    int	GluiWindow;		// the glut id for the glui window
    int	MainWindow;		// window id for main graphics window
    int	Paused;
    GLfloat	RotMatrix[4][4];	// set by glui rotation widget
    float	Scale, Scale2;		// scaling factors
    GLuint	SphereList;
    Projection	WhichProjection;	// ORTHO or PERSP
    int	Xmouse, Ymouse;		// mouse values
    float	Xrot, Yrot;		// rotation angles in degrees
    float	TransXYZ[3];		// set by glui translation widgets

    double	ElapsedTime;
    int		ShowPerformance;

    size_t GlobalWorkSize[3];
    size_t LocalWorkSize[3];

    struct xyzw *	GLParticleVelocity;
    GLuint			GLParticlePosition;
    GLuint			GLParticleColor;

    cl_mem			CLParticlePosition;
    cl_mem			CLParticleColor;
    cl_mem			CLParticleVelocity;

    cl_command_queue	CmdQueue;
    cl_device_id		Device;
    cl_kernel		Kernel;
    cl_platform_id		Platform;
    cl_program		Program;
    cl_platform_id		PlatformID;
};

#endif // PARTICLE_SYSTEM