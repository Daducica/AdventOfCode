# AdventOfCode

This is my solution for the Day 8 task of the 2022 Advent of Code challenge.

https://adventofcode.com/2022/day/8

The work is not yet finished, but here's a description of the current state of the project.

I have provided several solutions that approach the problem from different angles. The framework is easily extendable, so it is possible to add or experiment with more solutions. I started with the easiest approach, which is just the 'brute force' way of solving the issue (OriginalSolution), then applied some clean coding principles to make the code more readible (ProceduralSolution). I also implemented a faster solution to the first problem (OptimizedSolution) and used object oriented programming to implement yet another solution (OOPSolution). Additionally, I experimented with a version that utilizes threads (MultithreadSolution) and a version that uses the GPU (GPUSolution). I'll give a more detailed explanation of each of these approaches further below.

## Technicalities
I used Visual Studio C++17 Standard and CUDA Toolkit 12.1 to compile the project. To run the full solution, the CUDA Toolkit should be installed.

## The Test Framework

I have created a testing framework that can run the implementation of any number of solutions, measure the run times, and compare the results. In a typical project, this framework could be used for unit tests that check for regression or correctness. However, as the ultimate goal of this project is to just experiment with different solutions, and as a consequence there is no actual user/feature code, this is the code I run upon starting the program.

To be able to run the tests, we need to pass in a configuration object that specifies the file name, the number of test iterations, and choices about which part of the code we want to test (full solution, file read, first task, second task).

To include a solution in the test runs, we need to implement an adapter class that translates our requests into the target solution's 'language'. This is necessary because we cannot assume that every solution will use the same notation/interface for the different features. Once we have the adapter class, all we need to do is instantiate this class and append the instance to the test solution container that automatically manages everything for us from then on.

We can choose which item in the solution vector should be treated as the benchmark for run time comparisions and value checks (which will be implemented later). As it stands, I use the original solution for benchmarking purposes, but this could be changed if needed.

## Solutions

### Original Solution

### Procedural Solution

### Optimized (Procedural) Solution

### OOP Solution

### Multithread Solution

### GPU Solution

## Test Data

I have included two test matrices into my project. The file named 'day8.txt' contains the original matrix that was given in the Advent of Code challenge. Additionally, I generated a larger matrix (file name: 'largeForest.txt') that can also be used for testing purposes, such as tesing for run time scalability. To generate random matrices, I implemented a utility function that accepts the file name and the matrix dimensions as parameters. (Although this function is currently unused, I kept it in the codebase in case it is needed in the future.) I have added a third file that could be used to test bad inputs, such as empty file input, matrix with bad dimensions, matrix with bad characters. 

## Results

## Remarks

## TODO items
- test framework should check for actual results (in addition to runtime)
- check compiler warnings
- optimize second task (similarly to the optimization of the first task)
- finish GPU solution
- syntactic sugar check
- finish documentation



