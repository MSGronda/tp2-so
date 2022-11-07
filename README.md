# x64BareBones - starting a 64 Bits OS almost from scratch

x64BareBones  is a basic setup to develop operating systems for the Intel 64 bits architecture.

This project is based on a UNIX based operating system where we implement many key OS features:
- Syscalls
- Scheduling (Priority-Based Round-Robin)
- Memory Management (Buddy and Implicit List)
- Semaphores
- IPC (Pipes)

## Environment setup:

1. Install the following packages before building the Toolchain and Kernel:
```bash
    user@linux:$ nasm qemu gcc make
```
2. Go inside the root directory of the repository and run the following command in order to start the Docker container:
```bash
    user@linux:$ docker run -d -v ${PWD}:/root --security-opt seccomp:unconfined -ti --name dockerSO agodio/itba-so:1.0
```
from the directory where you have the x64Barebones project.

***Inside the Docker container***

3. Compile the Toolchain
```bash
    user@linux:$ cd root/x64Barebones/Toolchain
    user@linux:~/x64Barebones/Toolchain$ make all
```
4. Compile the Kernel, there are two options depending on the memory manager you want to use:

    - **Buddy**  
      4.1. Go to Kernel/Makefile  
      4.2. Uncomment line 27  
      4.3. Comment line 29
    
    - **Implicit List**  
      4.1. Go to Kernel/Makefile  
      4.2. Uncomment line 29  
      4.3. Comment line 27  
      
After that, compile the project. Go to the x64Barebones directory and run:  
```bash
    user@linux:~/x64Barebones$ make all
```
***From Bash terminal***

5. Inside the x64barebones directory, run:
```bash
    user@linux:~/x64barebones$ ./run.sh
```
