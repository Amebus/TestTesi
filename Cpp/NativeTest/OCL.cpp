//
// Created by federico on 18/08/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <streambuf>

#include "ocl_OCL.h"
#include <CL/cl.h>

#define MEM_SIZE (128)




// Upload the OpenCL C source code to output argument source
// The memory resource is implicitly allocated in the function
// and should be deallocated by the caller
int ReadSourceFromFile(const char* fileName, char** source, size_t* sourceSize)
{
	int errorCode = CL_SUCCESS;

	FILE* fp = NULL;
	fp = fopen(fileName, "rb");
	if (fp == NULL)
	{
		//LogError("Error: Couldn't find program source file '%s'.\n", fileName);
		errorCode = CL_INVALID_VALUE;
	}
	else {
		fseek(fp, 0, SEEK_END);
		*sourceSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		*source = new char[*sourceSize];
		if (*source == NULL)
		{
			//LogError("Error: Couldn't allocate %d bytes for program source from file '%s'.\n", *sourceSize, fileName);
			errorCode = CL_OUT_OF_HOST_MEMORY;
		}
		else {
			fread(*source, 1, *sourceSize, fp);
		}
	}
	return errorCode;
}


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

	char string[MEM_SIZE];
	char* source = NULL;
	size_t src_size = 0;
	ReadSourceFromFile("../Cpp/NativeTest/OCL_Kernels/HelloWorld.cl", &source, &src_size);
	std::cout << source << std::endl;

	std::ifstream t("../Cpp/NativeTest/OCL_Kernels/HelloWorld.cl");
	std::stringstream source_str;
	source_str << t.rdbuf();

	//std::cout << source_str.str() << std::endl;



//	Get Platform and Device Info
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);

//	 Create OpenCL context
	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

//	 Create Command Queue
	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

//	 Create Memory Buffer
	memobj = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(char), NULL, &ret);


//	 Create Kernel Program from the source
	program = clCreateProgramWithSource(context, 1, (const char **)&source,
										(const size_t *)&src_size, &ret);

//	 Build Kernel Program
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

//	 Create OpenCL Kernel
	kernel = clCreateKernel(program, "hello", &ret);

	//Set OpenCL Kernel Parameters
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);

	//Execute OpenCL Kernel
	ret = clEnqueueTask(command_queue, kernel, 0, NULL,NULL);

	//Copy results from the memory buffer
	ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0,
							  MEM_SIZE * sizeof(char), string, 0, NULL, NULL);

	/* Display Result */
	std::cout << string << std::endl;

	/* Finalization */
	ret = clFlush(command_queue);
	ret = clFinish(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(memobj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);


}