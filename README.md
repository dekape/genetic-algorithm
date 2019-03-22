# acse-4-project-3-iron

Duncan Hunter, Hitesh Kumar, Jia Ye Mao (Gary), Nitchakul Pipitvej (Irin), Zongpeng Chen (Frank), Deborah Pelacani Cruz

This program employs a Genetic Algorithm to optimise a simple model for a mineral processing circuit. Parallelised with both OpenMP and MPI, the model is quick and efficient, with an easy to use command line based interface. A technical report is provided in the repository, which includes results and an analysis of performance as well as other information.

# Usage
## Dependencies
 - OpenMP (OpenMP 5.0 or later)
 - MPI (MS-MPI or MPICH)
 - C++ compiler (g++, intel, Visual Studio (Windows))
## Install/Make
### Linux
On Linux based systems, the program can be built easily by navigating to the folder containing 'Makefile', and using the command:

$make

This should generate the appropriate binaries and executables, with the program 'Genetic_Algorithm' being stored in './bin/'.

### Windows
To compile, one can use GNUWin (and make as above) or open the files in Visual Studio (or another IDE) and compile/run from there. If done in this way, the options that you would normally enter on the command line must be changed manually in \src\main.cpp.

## Execute

The program can be executed with:

$bin/Genetic_Algorithm <no_units> <iter_max> <best_count_lim> <p_mutation> <no_threads>. The options are detailed below:

 <no_units> The number of units in the circuit to be optimised.

 <iter_max> The maximum number of iterations the program should run for.
 
 <best_count_lim> The number of iterations the program should run for without the best fit value changing. For example if the best fit doesn't change for <best_count_lim> iterations, the program will return as it thinks it has converged. This option needs to be thought about, as it will converge to minima throughout.
 
 <p_mutation> The probability per iteration of a unit in a circuit to mutate. 1 = every cell will mutate every time, 0, every cell will never mutate.
 
 <no_threads> The number of (OpenMP) threads to run with in certain functions

Some example configurations are listed below:

 No_units | iter_max | best_count_lim | p_mutation
 --- | --- | --- | ---
 5 | 300 | 100 | 0.01
 10 | 1500 | 500 | 0.01
 15 | 5000 | 1000 | 0.01

As you can see, 0.01 is a good choice for p_mutation. The effect of this is shown in the technical report.

Individual iterations are not printed (clutter) but the final result of each processes simulation is, and then the best circuit from all of the processes is chosen automatically and printed. 


