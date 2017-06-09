#ifndef PROJECT_7A_DATA_TYPES
#define PROJECT_7A_DATA_TYPES

typedef struct
{
    float x;
    float y;
    float z;
    float w;
} float4;

typedef enum
{
	ORTHO,
	PERSP
} Projections;

typedef enum
{
	GO,
	PAUSE,
	RESET,
	QUIT
} ButtonVals;


#endif // PROJECT7A_DATA_TYPES