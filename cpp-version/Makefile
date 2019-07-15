
###########################################
# 			PLEASE NOTE TO USE			  #
# 			  target=<name>				  #
# WHEN INVOCKING THE COMMANDS ON TERMINAL #
###########################################

# Terminal command to compile in C++
CC = g++

# Flags for default C-Grasp version
CFLAGS = -Ofast

# Flags for parallel C-Grasp version
PFLAGS = -fopenmp


# Compiles for the default version of C-Grasp
#compile:
#	$(CC) $(target).cpp -o $(target) $(CFLAGS)

# Compiles for the parallel version of C-Grasp
#pcompile:
#	$(CC) $(target).cpp -o $(target) $(CFLAGS) $(PFLAGS)

# Compiles for the GPU parallel version of C-Grasp
#gpcompile:
#	$(CC) $(target).cpp -o $(target) $(CFLAGS) $(PFLAGS)


# Compiles the function only target to be executed
# by the default version of C-Grasp
compile:
	$(CC) $(target).cpp -o $(target) $(AUTO_DIR)/exec.cpp $(CFLAGS)

# Compiles the function only target to be executed
# by the parallel version of C-Grasp
pcompile:
	$(CC) $(target).cpp -o $(target) $(AUTO_DIR)/pexec.cpp $(CFLAGS) $(PFLAGS)

#Compiles the function only target to be executed
# by the GPU parallel version of C-Grasp
gpcompile:
	$(CC) $(target).cpp -o $(target) $(AUTO_DIR)/gpexec.cpp $(CFLAGS) $(PFLAGS)


DIR = ./cgrasplib
AUTO_DIR = $(DIR)/autoexec
