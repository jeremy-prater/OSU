#ifndef PROJECT_7A
#define PROJECT_7A

#include "ParticleSystem.hpp"

class Project7a
{
public:
    // title of these windows:
    static const char *WINDOWTITLE;
    static const char *GLUITITLE;

    // random parameters:
    static const float XMIN;
    static const float XMAX;
    static const float YMIN;
    static const float YMAX;
    static const float ZMIN;
    static const float ZMAX;

    static const float VMIN;
    static const float VMAX;

    static const int NUM_PARTICLES;
    static const int LOCAL_SIZE;
    static const char *CL_FILE_NAME;
    static const char *CL_BINARY_NAME;

    static const int INIT_WINDOW_SIZE;

    static const float ANGFACT;
    static const float SCLFACT;
    static const float MINSCALE;

    static const int LEFT;
    static const int MIDDLE;
    static const int RIGHT;


    static const float BACKCOLOR[];

    static const GLfloat AXES_COLOR[];
    static const GLfloat AXES_WIDTH;

    Project7a();
    ~Project7a();
};

#endif // PROJECT_7A