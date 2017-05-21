#include "nonSimd.h"


void
Mul( float *a, float *b,   float *c,   int len )
{
	for( int i = 0; i < len; i++ )
	{
		c[i] = a[i] * b[i];
	}
}



float
MulSum( float *a, float *b, int len )
{
	float sum = 0.;
	for( int i = 0; i < len; i++ )
	{
		sum += a[i] * b[i];
	}

	return sum;
}
