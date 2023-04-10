# AdventOfCode

This is my solution for the Day 8 task of the 2022 Advent of Code challenge.

https://adventofcode.com/2022/day/8

The work is not yet finished, but here's a description of the current state of the project.

I have provided several solutions that approach the problem from different angles. The framework is easily extendable, so it is possible to add or experiment with more solutions. I started with the easiest approach, which is just the 'brute force' way of solving the issue (OriginalSolution), then applied some clean coding principles to make the code more readible (ProceduralSolution). I also implemented a faster solution to the first problem (OptimizedSolution) and used object oriented programming to implement yet another solution (OOPSolution). Additionally, I experimented with a version that utilizes threads (MultithreadSolution) and a version that uses the GPU (GPUSolution). I'll give a more detailed explanation of each of these approaches further below.

## Technicalities
I used Visual Studio (version Visual C++ 14.2) C++17 Standard and the CUDA Toolkit (version 12.1) to compile the project. To run the full solution, the CUDA Toolkit should be installed.

## The Test Framework

I have created a testing framework that can run the implementation of any number of solutions, measure the run times, and compare the results. In a typical project, this framework could be used for unit tests that check for regression or correctness. However, as the ultimate goal of this project is to just experiment with different solutions, and as a consequence there is no actual user/feature code, this is the code I run upon starting the program.

To be able to run the tests, we need to pass in a configuration object that specifies the file name, the number of test iterations, and choices about which part of the code we want to test (full solution, file read, first task, second task).

To include a solution in the test runs, we need to implement an adapter class that translates our requests into the target solution's 'language'. This is necessary because we cannot assume that every solution will use the same notation/interface for the different features. Once we have the adapter class, all we need to do is instantiate this class and append the instance to the test solution container that automatically manages everything for us from then on.

We can choose which item in the solution vector should be treated as the benchmark for run time comparisions and value checks. As it stands, I use the original solution for benchmarking purposes, but this could be changed if needed.

## Solutions

### Original Solution

The original solution is a naive implementation taht serves only as a benchmark for code readability and runtime comparisions. As a result, I have not optimized or modified it in any way, except for some basic changes that help with testing the code.

### Procedural Solution

For the procedural solution, I began with the code of the original solution. The purpose of this version was to keep the original algorithm while improving the code's readability. To achieve this, I organized the code into small functions with descriptive names and I renamed the variables so that their purpose is clear. In addition, I saved some frequently used values into local variables, and made variables 'const' wherever possible.

### Optimized (Procedural) Solution

In the optimized solution, I experimented with my own algorithm that iterates though the matrix only four times (one iteration for each of the four directions) and saves the largest height seen in the row / column so far. This means we are working with an O(n^2) algorithm, instead of O(n^3). I have implemented this logic for the first task, but the same idea can be used for the second task as well (not implemented yet). The purpose of this version is to be as fast as possible while also maintain basic code readability.

### OOP Solution

The OOP solution focuses on reusability and extendability. While it uses the algorithm behind the optimized solution, and thus it's faster than the original solution, it is expected to be slower than the optimized solution. Allocating memory for custom classes slows down the file read. Working with class instances (and a virtual class) should be more expensive in terms of memory and runtime. On the other hand, storing the results of the calculations means that we can work with the values later on if needed. The classes can be repurposed and extended for future use cases. Decoupling the calculation logic from the data class enables the reuse of the logic in other contexts. The algorithm can be easily swapped out, both at compile time and at runtime, allowing for experimentation and comparision of several different algorithms.

### Multithread Solution

The multithreaded solution utilizes the parallel std::for_each to make the calculation faster in case there are multiple cores. It has been implemented for the first task only. I expect a significant speedup for larger matrices. In case of small matrices (like the Advent of Code example), setting up the threads may outweigh the benefits of parallelization. It would be worthwile to experiment with custom threading solutions instead of the std::for_each.

### GPU Solution

The tasks require matrix calculations, an area where GPUs excel. The questions is, can we break down the tasks into highly parallelizable parts to reduce runtime? I experimented with this idea, but the results were inconclusive and the solution needs a rework. I attempted to delegate the calculations of the first task to the GPU, where sweeping through columns or rows can be done in parallel. The basic algorithm behind this comes from the optimized solution and allows for parallelization along one axes of the matrix (writing into the visibility cache matrix forces us to iterate through the data matrix sequentially four times). However, it would be a good idea to try and use some of the original logic instead, which would allow for parallelization along all four directions. 

## Test Data

I have included two test matrices into my project. The file named 'day8.txt' contains the original matrix that was given in the Advent of Code challenge. Additionally, I generated a larger matrix (file name: 'largeForest.txt') that can also be used for testing purposes, such as tesing for run time scalability. To generate random matrices, I implemented a utility function that accepts the file name and the matrix dimensions as parameters. (Although this function is currently unused, I kept it in the codebase in case it is needed in the future.) I have added a third file that could be used to test bad inputs, such as empty file input, matrix with bad dimensions, matrix with bad characters. 

## Results

With a few tasks left on the todo list, these are the current results.

FileName = day8.txt

LoopCount = 10

|             | Full        | Read        | VisC        | Scenic      |
| ----------- | ----------- | ----------- | ----------- | ----------- |
| Original    | 1.00x       | 1.00x       | 1.00x       | 1.00x       |
| Procedural  | 2.21x       | 1.70x       | 4.26x       | 2.56x       |
| Optimized   | 4.48x       | 1.72x       | 7.78x       | 2.73x       |
| OOP         | 1.32x       | 0.55x       | 37.48x      | 3.28x       |
| Multithread | 6.09x       | 1.87x       | 12.12x      | 2.69x       |
| GPU         | 0.83x       | 1.76x       | 0.47x       | failed      |

## Remarks

## TODO items
- optimize second task (similarly to the optimization of the first task)
- experiment with mirrored matrices
- finish GPU solution
- syntactic sugar check
- finish documentation



