//
// Created by federico on 18/08/17.
//

#include "ocl_OCL.h"
#include <iostream>
#include <CL/cl.h>

JNIEXPORT void JNICALL Java_ocl_OCL_sayHello(JNIEnv *env, jobject obj)
{
	std::cout << "Hello" << std::endl;

	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_command_queue command_queue = NULL;
	cl_mem memobj = NULL;
	cl_program program = NULL;
	cl_kernel kernel = NULL;
	cl_platform_id platform_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret;


	/* Get Platform and Device Info */
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);


	std::cout << ret_num_platforms << std::endl;
}