////////////////////////////////////////////////////////////////////////
//
// Open CL kernel for Array Multiplication + Addition + Reduction
//
//

kernel void ArrayMultAddReduce(global const float *dA, global const float *dB, local float * products , global float *dD)
{
	int gid = get_global_id(0);
	dD[gid] = (dA[gid] * dB[gid]) + dC[gid];
}
