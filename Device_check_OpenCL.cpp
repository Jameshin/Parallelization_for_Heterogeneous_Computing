#include <stdio.h> 
#include <stdlib.h>
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif


int main() {
	int i, j;
	char* value;
	size_t valueSize;
	cl_uint platformCount;
	cl_platform_id* platforms;
	cl_uint deviceCount;
	cl_device_id* devices;
	cl_uint maxComputeUnits;
	cl_uint max_clock;

	//get all platforms

	clGetPlatformIDs(0, NULL, &platformCount);
	platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * platformCount);
	clGetPlatformIDs(platformCount, platforms, NULL);

	cl_platform_info platform_info;


	for (i = 0; i < platformCount; i++) {
		clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);
		devices = (cl_device_id*)malloc(sizeof(cl_device_id) * (deviceCount));
		clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL);
		printf("Platform no. %d \n", i+1);

		for (j = 0; j < deviceCount; j++) {

			//print device name
			clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &valueSize);
			value = (char*)malloc(valueSize);
			clGetDeviceInfo(devices[j], CL_DEVICE_NAME, valueSize, value, NULL);
			printf("%d. Device: %s\n", j + 1, value);
			free(value);

			//print device version
			clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, 0, NULL, &valueSize);
			value = (char*)malloc(valueSize);
			clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, valueSize, value, NULL);
			printf("%d. Device: %s\n", j + 1, value);
			free(value);

			//print device driver version
			clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, 0, NULL, &valueSize);
			value = (char*)malloc(valueSize);
			clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, valueSize, value, NULL);
			printf("%d. Device: %s\n", j + 1, value);
			free(value);

			//print device OpenCL version
			clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, 0, NULL, &valueSize);
			value = (char*)malloc(valueSize);
			clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, valueSize, value, NULL);
			printf("%d. Device: %s\n", j + 1, value);
			free(value);

			//print device Vender
			clGetDeviceInfo(devices[j], CL_DEVICE_VENDOR, 0, NULL, &valueSize);
			value = (char*)malloc(valueSize);
			clGetDeviceInfo(devices[j], CL_DEVICE_VENDOR, valueSize, value, NULL);
			printf("%d. Device: %s\n", j + 1, value);
			free(value);


			clGetDeviceInfo(devices[j], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(max_clock), &max_clock, NULL);
			printf("%d, Device freq : %d  MHz\n", j + 1, max_clock);

			clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(maxComputeUnits), &maxComputeUnits, NULL);
			printf("%d, Device MaxComputeUnit : %d  \n", j + 1, maxComputeUnits);
		}

		cl_int error;
		cl_context context;
		context = clCreateContext(NULL, deviceCount, devices, NULL, NULL, &error);
		printf("%d \n", error);

		cl_command_queue cmdQueue;
		cmdQueue = clCreateCommandQueue(context, devices[0], 0, &error);
		printf("%d \n", error);

		free(devices);
	}
	getchar();
	free(platforms);
	return 0;

}