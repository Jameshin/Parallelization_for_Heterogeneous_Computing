#include "cuda_runtime.h" 
#include "device_launch_parameters.h" 
#include "stdio.h" 
#include <omp.h>

#define TILE_WIDTH 16

void matrixMultiplyCPU(float *a, float *b, float *c, int width) 
{
  float result;
  
  for(int row=0; row<width; row++) 
  {
    for(int col=0; col<width; col++)
    {
      result = 0;
      for(int k = 0; k<width; k++)
      {
        result += a[row * width + k] * b[k * width + col];
      }
      c[row * width + col] = result;
    }
  }
}

__global__ void matrixMultiplySimple(float *a, float *b, float *c, int width) 
{ 
  //calculate the row and column index of the element 
  int row = blockIdx.y * blockDim.y + threadIdx.y; 
  int col = blockIdx.x * blockDim.x + threadIdx.x; 
  float result = 0; 
  //do dot product between row of a and column of b 
  for(int i=0; i<width; i++) 
  { 
    result += a[row*width+i] * b[i*width+col]; 
  } 
  //write out this thread's result 
  c[row*width+col] = result; 
}

__global__ void matrixMultiplyOptimised(float *a, float *b, float *c, int width) 
{ 
  //create shorthand names for threadIdx & blockIdx 
  int tx = threadIdx.x; 
  int ty = threadIdx.y; 
  //allocate 2D tiles in __shared__ memory 
  __shared__ float s_a[TILE_WIDTH][TILE_WIDTH]; 
  __shared__ float s_b[TILE_WIDTH][TILE_WIDTH]; 
  //calculate the row & column index of the element 
  int row = blockIdx.y * blockDim.y + threadIdx.y; 
  int col = blockIdx.x * blockDim.x + threadIdx.x; 
  float result = 0;
  //loop over the tiles of the input in phases   
  for(int p=0; p<width/TILE_WIDTH; p++) 
  { 
    //collaboratively load tiles into __shared__ 
    s_a[ty][tx] = a[row*width + (p*TILE_WIDTH + tx)]; 
    s_b[ty][tx] = b[(p*TILE_WIDTH + ty) * width + col]; 
    //wait until all data is loaded before allowing any thread in this block to continue 
    __syncthreads(); 
    //do dot product between row of s_a and column of s_b 
    for(int i=0; i<TILE_WIDTH; i++) 
    { 
      result += s_a[ty][i] * s_b[i][tx]; 
    } 
    //wait until all threads are finished with the data before allowing any thread in this block to continue 
    __syncthreads(); 
  } 
  //write out this thread's result 
  c[row*width+col] = result; 
}

int main(void)
{
  //the width of the matrix (not the number of total elements)
  int N = 1024;
  
  //grid and block size
  dim3 block(TILE_WIDTH, TILE_WIDTH);
  dim3 grid(N/block.x, N/block.y);

  //host memory pointers
  float *a_h = NULL;
  float *b_h = NULL;
  float *c_h = NULL;

  //allocate host memory
  size_t memSize = (N*N) * sizeof(float);
  a_h = (float *) malloc(memSize);
  b_h = (float *) malloc(memSize);
  c_h = (float *) malloc(memSize);

  //generate random input
  for(int i = 0; i < N*N; ++i)
  {
    a_h[i] = (float)(rand()/RAND_MAX);
    b_h[i] = (float)(rand()/RAND_MAX);
  }

  //device memory pointers
  float *a_d = NULL;
  float *b_d = NULL;
  float *c_d = NULL;

  //allocate device memory
  cudaMalloc((void**)&a_d, (N * N) * sizeof(float));
  cudaMalloc((void**)&b_d, (N * N) * sizeof(float));
  cudaMalloc((void**)&c_d, (N * N) * sizeof(float));

  //copy input to the device
  cudaMemcpy(a_d, a_h, (N * N) * sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(b_d, b_h, (N * N) * sizeof(float), cudaMemcpyHostToDevice);

  //get start time
  double cpuStart = omp_get_wtime();

  printf("Measuring CPU execution time...\n");
  matrixMultiplyCPU(a_h, b_h, c_h, N);

  //get end time
  double cpuEnd = omp_get_wtime();
  double cpuTime = (cpuEnd-cpuStart)*1000;

  //CUDA events to measure time
  cudaEvent_t start;
  cudaEvent_t stop;

  float simpleKernelTime;
  float optimisedKernelTime;

  //start timer
  cudaEventCreate(&start);
  cudaEventCreate(&stop);
  cudaEventRecord(start, 0);

  //launch simple kernel multiple times
  printf("Measuring execution time of the simple kernel...\n");
  matrixMultiplySimple<<<grid, block>>>(a_d, b_d, c_d, N);

  //stop timer
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&simpleKernelTime, start, stop);

  //start timer
  cudaEventRecord(start, 0);

  //launch optimised kernel multiple times
  printf("Measuring execution time of the optimised kernel...\n");
  matrixMultiplyOptimised<<<grid, block>>>(a_d, b_d, c_d, N);

  //stop timer
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&optimisedKernelTime, start, stop);

  //print out execution times
  printf("Naive CPU implementation time: %f ms\n", cpuTime);
  printf("Naive GPU implementation time: %f ms\n", simpleKernelTime);
  printf("Optimised GPU implementaion time: %f ms\n", optimisedKernelTime);

  //free device memory
  cudaFree(a_d);
  cudaFree(b_d);
  cudaFree(c_d);

  //free host memory
  free(a_h);
  free(b_h);

  return 0;
}