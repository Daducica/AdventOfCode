#include "GPUSolutionCUDA.h"

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

namespace GPUSolution
{
    static __global__ void CheckVisibilityFromLeft_Kernel (bool* visibility, const short* forest,
                                                           size_t width, size_t height)
    {
        size_t row {blockIdx.x * blockDim.x + threadIdx.x};
        if (row >= height)
            return;

        int maxHeightInRow = -1;
        for (size_t column = 0; column < width; ++column) {
            size_t index = row * width + column;
            const short treeHeight = forest[index];

            if (treeHeight > maxHeightInRow) {
                maxHeightInRow = treeHeight;
                if (!visibility[index]) {
                    visibility[index] = true;
                }
            }
        }
    }


    static __global__ void CheckVisibilityFromRight_Kernel (bool* visibility, const short* forest,
                                                            size_t width, size_t height)
    {
        size_t row {blockIdx.x * blockDim.x + threadIdx.x};
        if (row >= height)
            return;

        int maxHeightInRow = -1;
        for (int column = int (width - 1); column >= 0; --column) {
            size_t index = row * width + column;
            const short treeHeight = forest[index];

            if (treeHeight > maxHeightInRow) {
                maxHeightInRow = treeHeight;
                if (!visibility[index]) {
                    visibility[index] = true;
                }
            }
        }
    }


    static __global__ void CheckVisibilityFromTop_Kernel (bool* visibility, const short* forest,
                                                          size_t width, size_t height)
    {
        size_t column {blockIdx.x * blockDim.x + threadIdx.x};
        if (column >= width)
            return;

        int maxHeightInRow = -1;
        for (size_t row = 0; row < height; ++row) {
            size_t index = row * width + column;
            const short treeHeight = forest[index];

            if (treeHeight > maxHeightInRow) {
                maxHeightInRow = treeHeight;
                if (!visibility[index]) {
                    visibility[index] = true;
                }
            }
        }
    }


    static __global__ void CheckVisibilityFromBottom_Kernel (bool* visibility, const short* forest,
                                                             size_t width, size_t height)
    {
        size_t column {blockIdx.x * blockDim.x + threadIdx.x};
        if (column >= width)
            return;

        int maxHeightInRow = -1;
        for (int row = int (height - 1); row >= 0; --row) {
            size_t index = row * width + column;
            const short treeHeight = forest[index];

            if (treeHeight > maxHeightInRow) {
                maxHeightInRow = treeHeight;
                if (!visibility[index]) {
                    visibility[index] = true;
                }
            }
        }
    }


    static cudaError_t CheckVisibilityFromLeft (bool* visibility, const short* forest,
                                                size_t width, size_t height)
    {
        size_t arraySize = width * height;

        short* deviceForest;
        bool* deviceVisibility;
        cudaError_t cudaStatus;

        cudaStatus = cudaSetDevice (0);
        if (cudaStatus != cudaSuccess) {
            fprintf (stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
            goto Error;
        }

        cudaStatus = cudaMalloc ((void**)&deviceVisibility, arraySize * sizeof (bool));
        if (cudaStatus != cudaSuccess) {
            fprintf (stderr, "cudaMalloc failed!");
            goto Error;
        }

        cudaStatus = cudaMalloc ((void**)&deviceForest, arraySize * sizeof (short));
        if (cudaStatus != cudaSuccess) {
            fprintf (stderr, "cudaMalloc failed!");
            goto Error;
        }

        cudaStatus = cudaMemcpy (deviceForest, forest, arraySize * sizeof (short), cudaMemcpyHostToDevice);
        if (cudaStatus != cudaSuccess) {
            fprintf (stderr, "cudaMemcpy failed!");
            goto Error;
        }

        cudaStatus = cudaMemcpy (deviceVisibility, visibility, arraySize * sizeof (bool), cudaMemcpyHostToDevice);
        if (cudaStatus != cudaSuccess) {
            fprintf (stderr, "cudaMemcpy failed!");
            goto Error;
        }

        if (height >= 1024 || width >= 1024) {
            printf ("Matrix dimensions are too large.\n");
            goto Error;
        }
        CheckVisibilityFromLeft_Kernel <<<1, (int)height>>> (deviceVisibility, deviceForest, width, height);
        CheckVisibilityFromRight_Kernel <<<1, (int)height>>> (deviceVisibility, deviceForest, width, height);
        CheckVisibilityFromTop_Kernel <<<1, (int)width>>> (deviceVisibility, deviceForest, width, height);
        CheckVisibilityFromBottom_Kernel <<<1, (int)width>>> (deviceVisibility, deviceForest, width, height);

        cudaStatus = cudaGetLastError ();
        if (cudaStatus != cudaSuccess) {
            fprintf (stderr, "Kernel launch failed: %s\n", cudaGetErrorString (cudaStatus));
            goto Error;
        }

        cudaStatus = cudaDeviceSynchronize ();
        if (cudaStatus != cudaSuccess) {
            fprintf (stderr, "cudaDeviceSynchronize returned error code %d after launching kernel!\n", cudaStatus);
            goto Error;
        }

        cudaStatus = cudaMemcpy (visibility, deviceVisibility, arraySize * sizeof (bool), cudaMemcpyDeviceToHost);
        if (cudaStatus != cudaSuccess) {
            fprintf (stderr, "cudaMemcpy failed!");
            goto Error;
        }

    Error:
        cudaFree (deviceVisibility);
        cudaFree (deviceForest);

        return cudaStatus;
    }


    static short* Convert2DVectorTo1DArray (const std::vector<std::vector<short>>&forest)
    {
        const size_t height = forest.size ();
        const size_t width = forest[0].size ();
        const size_t arraySize = height * width;

        short* array = new short [arraySize];
        for (size_t row = 0; row < height; row++) {
            for (size_t col = 0; col < width; col++) {
                array[row*width + col] = forest[row][col];
            }
        }
        return array;
    }


    uint64_t RunVisibleTreeCalculationOnGPU (const std::vector<std::vector<short>>& forest)
    {
        const size_t height = forest.size ();
        const size_t width = forest[0].size ();
        const size_t arraySize = height * width;

        short* forestArray = Convert2DVectorTo1DArray (forest);
        bool* visibility = new bool[arraySize];
        std::fill_n (visibility, arraySize, false);

        cudaError_t cudaStatus = CheckVisibilityFromLeft (visibility, forestArray, width, height);
        if (cudaStatus != cudaSuccess) {
            fprintf (stderr, "addWithCuda failed!");
            return 1;
        }

        cudaStatus = cudaDeviceReset ();
        if (cudaStatus != cudaSuccess) {
            fprintf (stderr, "cudaDeviceReset failed!");
            return 1;
        }

        uint64_t visibilityCount = 0;
        for (size_t index = 0; index < arraySize; index++)
            if (visibility[index])
                visibilityCount++;

        delete[] forestArray;
        delete[] visibility;

        return visibilityCount;
    }

}
