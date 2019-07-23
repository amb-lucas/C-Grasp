# C-Grasp

This is a library with the continuous grasp metaheuristic coded for the Optimization discipline at UFPE.

It is adapted for minimization problems with box constrains.

If you wish to test it or use it, I recommend the c++ version for better speed.

To use it, set the boundaries and the function as shown in the sample files and run it according to the makefile command:
````
make compile target=<name of the file>
````

There's also a version with openmp threads, to use it, make sure to set the parallel parameter in the sample file and run the following command:
````
make pcompile target=<name of the file>
````

You can also import is as a library and call the function as ordinary.
When compiling, remember to use the same flags as the makefile.
If you want to set the parameters, make sure they're in the order as declared in the library.
