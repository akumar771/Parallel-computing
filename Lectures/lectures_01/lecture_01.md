
class: bottom, left
background-image: url(images/g.png)

<h2 class="title_headings_sml">COSC330/530 - Parallel and Distributed Computing</h2>

<h1 class="title_headings_sml"> Lecture 1 - Introduction </h1>

<h3 class="title_headings_sml"> Dr. Mitchell Welch </h3>

---

# Reading
* Chapter 1, 7 and start chapter 8 from **Advanced Programming in the UNIX environment**
* **UNIX Programming Tools** - should be mostly revision
* **Assignment 1** Description
* **COSC330/530 Unit Information and Assessment Overview** - Pay Special Attention to the Assessment and Study Plan

---

##Summary

* Welcome to COSC330/530
* House-Keeping
* Concurrency and Parallelism
* Resources and Machines
* Why Construct Concurrent Implementations?
* UNIX Environment Overview

---

## Welcome to COSC330/530
* This course will introduce concurrent, distributed and parallel programming approaches
* The course will provide practical experience in concurrent programming paradigms
* The emphasis will be on
    * POSIX (I.e. UNIX system) concurrent primitives (e.g. multi-processes and multi-threaded applications)
    * The Message Passing Interface via the C language bindings
    * An introduction to Nvidia CUDA 

---

## Welcome to COSC330/530

* Through this course you will learn how do develop high-performance applications
* You will be prepared to write software capable of running on high-performance computing systems
* Within Australia, the key provider of high-perfromance computing systems is the [National Computational Infrastructure](http://nci.org.au/)
* Researchers at UNE have access to these systems through [Intersect](http://www.intersect.org.au/time/introduction)

---

## House-Keeping

* All programming will use C and all programs will need to compile on turing using the gcc compiler
* Through your previous study, you should be familiar with C and the gcc compiler 
* Please review the material from you previous studies

---

## House-Keeping

* Revision Areas to focus on:
    1. IO (`fprintf`, `printf` and `scanf` etc.)
    2. Memory management in C (`malloc`, `calloc` and `free`)
    3. Structures (`struct`)
    4. pointers in C
* Please review the material in the additional reading section

---
## House-Keeping
* This unit will be run via MyLearn
* Assignment submission will be via `submit` on turing.une.edu.au
* There are **4** assignments for COSC330
* There is an **additional project** for COSC530
* Your assignments account for **40%** of your overall mark, with the exam making up the final 60%
* You must achieve at least **50%** in the assignment component and 50% in the exam to pass the unit

---

## House-Keeping
* Questions about assignments, practicals and lectures should be communicated via the relevant discussion board
* Remember your discussion board etiquette!
* Make sure you use a descriptive subject line for your post.
* An Example post:

.center[![center-aligned image](img/lecture_01/sample_post.png)]

---

## House-Keeping
* Questions about your personal issue/progression/studies in COSC330/530 should be communicated by email
* The subject line of you email should be in the form: *Student Number, First Name Last Name - Subject*
* For example: **222211113333, John Smith - Extension on Assignment 2**
* Sample email:

> Hi Mitchell, 
>
> Would it be possible for you to grant me an extension on assignment 2 till next Friday?
> 
> Kind regards,

> John

---
## House Keeping

* All code in your assignments should have a consistent style used throughout:
    * Tabs and braces should be consistent through all sections.
    * Comments should be organised in an easily readable fashion.
    * Comments should outline *what* your code is doing not *how* it is doing it
    * Your code should not be more than 80 characters wide on any given line
* Please review the [Linux kernel coding style](https://www.kernel.org/doc/html/v4.10/process/coding-style.html) for guidance on your style.

---

## Concurrency and Parallelism

* *Concurrency* is a programming language concept (i.e. concurrent processes execute by sharing the resources of the system)
* *Parallelism* is implemented at the hardware level. On multiple processor systems, all processes overlap in time without sharing
* For example, it is possible to have a multiple-process program executing on a single core machine
through the use of context shifts.
* ***Therefore concurrency refers to the potential for parallelism***

---
## Concurrency and Parallelism

* Concurrency is achieved through the use of *Processes* and *Threads*
* A **Process** is an instance of a program during execution
* A **Thread** is a sequence of computation within a process (i.e. A thread of control through a process)
* A process can be single-threaded or multi-threaded
* A thread can be thought of as a light-weight process due to the lower
overhead in terms of memory and management- More on this later

---

## Concurrency and Parallelism
* Multi-process applications and multi-threaded processes can exploit the parallelism provided by multi-processor system
* In order to effectively solve problems, processes and threads within a process need to be able to interact.
* Communication involves the exchange of information. This can be through message passing between processes and threads through shared memory locations.
* Synchronization involves the coordination of activities between threads or processes, usually to ensure there are no clashes regarding the use of shared resources

---
## Concurrency and Parallelism
* We will be looking at shared files, signals, pipes, message
queues and message passing (in MPI) for interprocess
communication
* We will be looking at mutexes (mutual exclusion) and semaphores for process
synchronization
* We will also examine some classic problems and algorithms
that use these.

---

## Resources and Machines

* We will be using two machines in this course:
    * `turing` - A multiprocessor System with 16 Cores (Technically turing.une.edu.au is a virtual environment, so we donâ€™t work directly on the hardware)
    * `turing.une.edu.au` is a linux which will provide a platform for developing multiprocess and multithreaded software
    * `bourbaki` - A Virtual 8 node beowulf cluster set up on the turing infrastructure, accessed via turing.une.edu.au
    * `bourbaki` will provide a distributed processing environment for using *MPI*

---

## Resources and Machines

* A Beowulf cluster is a networked group of off-the-shelf
computers or processing devices, that are programmed to solve
problems by using their combined processing capabilities
* Most beowulf clusters consist of a set of PCâ€™s connected to a
switch or router, however other platforms can be used. (e.g.
Raspberry Pi or Cubie board)
â€¢ The Links:
    * [Cubieboard Cluster](http://cubieboard.org/2014/04/08/the-first-sparkhadoop-arm-cluster-runs-atop-cubieboards/)
    * [RaspberryPi Cluster](http://www.zdnet.com/article/build-your-own-supercomputer-out-of-raspberry-pi-boards/)

---

## Why Construct Concurrent Implementations?

.center[![center-aligned image](img/lecture_01/48-years-processor-trend.png)]

Source: [https://github.com/karlrupp/microprocessor-trend-data](https://github.com/karlrupp/microprocessor-trend-data)


---
## Why Construct Concurrent Implementations?

* For many years, software developers got their performance increase from the hardware
* Clock speeds got faster and faster
* Eventually, an engineering barrier was reached
    * Higher clock speeds were no longer feasible due to the power requirements and heat produced
* Modern processors use multiple processing cores
* Software must be written so that it can make use of the additional processing cores - we can't rely on clock speed increases  

---

## Why Construct Concurrent Implementations?

* Most modern processors make use of multi-core architectures:
    * [Intel i9 Processor](https://www.intel.com/content/www/us/en/products/details/processors/core/i9.html)
    * [AMD Ryzen Processors](https://www.amd.com/en/products/cpu/amd-ryzen-9-5900x)
    * [Raspberry Pi](https://www.raspberrypi.com/products/raspberry-pi-5/) 
    * [A14 Bionic (Iphone 12 Chip)](https://en.wikipedia.org/wiki/Apple_A14)

* Most Mobile devices contain multi-core hardware.

---

## UNIX Environment Overview
* This section contains a very quick overview of some key UNIX
features you should have already seen
* You can also re-familiarise yourselve's with the syntax and
features of C programming
    * Take note of the fundamentals:
    * The main function (in-fact functions in general)
    * Command line arguments - e.g. argc and argv
    * Datatypes e.g. int, char, long etc.
    * Pointers and passing arguments by reference to functions

---

## UNIX Environment Overview

* The UNIX Environment consists of 5 Components:
    * The ***Kernel***
    * The ***System Calls***
    * The ***Shell***
    * ***Library Routines***
    * The user ***Applications***

.center[![center-aligned image](img/lecture_01/architecture.png)]

---

## UNIX Environment Overview

* The Kernel controls the hardware resources and provides the
system environment for the applications e.g. *Disk/File IO*, *Process Management*, *Memory Management* and *Hardware Access*
* The System Calls provide the interface between the
Application software and the Kernel
* Libraries provide common functions for Applications
* The Applications are the users' software that use the Library functions
and System Calls to carry out operations
* The Shell is a special piece of application software that
provides an interface for running other applications

---
## UNIX Environment Overview
* The UNIX file system is a hierarchical set of Directories the
contain Files
* The root directory is the start of this hierarchy
* In UNIX everything is a file
* Directories are files that contains directory entries
* Devices are even mounted into the file system and can be accessed as file: 

```bash
ls -la /dev
```

* The `dev` directory contains the mount points
for devices

---
## UNIX Environment Overview
* File I/O within UNIX unix processes is managed using
*File Descriptors*
* **File Descriptors** are non-negative integers that the Kernel uses
to identify files that are accessed by processes.
* When ever a file is created or opened, its file descriptor is
provided by the kernel.

---

## UNIX Environment Overview
* A simple implementation of `ls`

```c
#include <stddef.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

void
main(int argc, char *argv[])
{
    DIR                *dp;
    struct dirent    *dirp;
    if (argc != 2)
        perror("usage: ls directory_name");
    if ((dp = opendir(argv[1])) == NULL )
        perror("can't open file");
    while ((dirp = readdir(dp)) != NULL )
        printf("%s\n", dirp->d_name);
    closedir(dp);
    exit(0);
}

```

---
## UNIX Environment Overview

* This example uses the `opendir` and `readdir` functions to list
the contents of a directory
* The loop in the program calls readdir which returns a pointer
to a `dirent` `struct`
* readdir returns `NULL` when there are no more entries to list
* The `dirent` contents are then accessed to list the name

---
## UNIX Evironment Overview

* File I/O is achieved using
`open, read, write, lseek` and `close`.
* By default, when a shell opens a program, it connects three file
descriptors that provide communication streams through to
the shell
    * Standard Input - `STDIN_FILENO`
    * Standard Output - `STDOUT_FILENO`
    * Standard Error - `STDERR_FILENO`
* The following example copies standard input to standard
output using unbuffered I/O

---

## UNIX Environment Overview

* A simple implementation of cat

```c
#include <stddef.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

#define    BUFFSIZE    4096
int
main(void)
{
    int        n;
    char    buf[BUFFSIZE];
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
        if (write(STDOUT_FILENO, buf, n) != n)
            perror("write error");
    if (n < 0)
        perror("read error");
    exit(0);
}
```

---


## UNIX Environment Overview
* The Standard I/O functions in stdio.h provide a buffered
interface to the unbuffered I/O functions
* This library provides the `getc` and `putc` functions
* The following example copies standard input to standard
output using unbuffered I/O

---

## UNIX Environment Overview
* Buffered I/O with `getc` and `putc`

```c
#include <stddef.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

int
main(void)
{
    int        c;
    while ((c = getc(stdin)) != EOF)
        if (putc(c, stdout) == EOF)
            perror("output error");
    if (ferror(stdin))
        perror("input error");
    exit(0);
}
```

---

## UNIX Environment Overview
```
int open(const char *path, int oflags [,mode_t mode]);
```
* `path` - A character string containing the file path
* `oflags` - The method in which the file is opened (e.g. reading,
writing etc.). This is specified by OR-ing the contants in the
<fcntl.h> lib. The most commonly used are O_RDONLY,
O_WRONLY, O_RDWR and O_APPEND, Chapter 3 has the full list.
* `mode_t` (optional) - The permissions if the file is created
* Open returns a file descriptor if the file is opened successfully or -1
if there is a failure.
* ***Your code should always check for a failure!***

---
## UNIX Environment Overview

```
int close(int fildes);
```
* Closes the file once the process is finished using it
* `fildes` - The file descriptor of the file to be closed
* Returns 0 upon success and -1 on failure

---
## UNIX Environment Overview

```c
#include <unistd.h>
#include <fcntl.h>
 
int main(){
    int filedesc = open("testfile.txt", O_WRONLY | O_APPEND);
    if(filedesc < 0)
        return 1;
    if(write(filedesc,"Output to testfile.txt\n", 36) != 36){
        write(2,"Error writing to testfile.txt\n",30);
        return 1;
    }
    close(filedesc);
    return 0;
}	
```

---
## UNIX Environment Overview

* A *program* is the executable residing on the disk, an executing
instance of this program is called a **process**
* The UNIX system assigns a unique numeric identifier to each
process - the `getpid()` function returns this id
* Processes can be created and managed using the `fork` and `exec`
family of functions

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    printf("My Process ID \%ld\n", (long)getpid());
    exit(0);
}
```

---

## UNIX Environment Overview

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>

int main(void){
   pid_t pid = fork();
   if (pid == -1){
      exit(EXIT_FAILURE);
   }
   else if (pid == 0) {
      printf("Hello from the child process!\n");
      _exit(EXIT_SUCCESS);  
   }
   else {
      int status;
      (void)waitpid(pid, &status, 0);
   }
   return EXIT_SUCCESS;
}	
```

---
## UNIX Environment Overview

* Error handling is very important for producing robust software
and for debugging
* Most library calls return a negative number and set the errno
integer which can be used to identify errors
* The error codes are defined in `errno.h`
* The `perror(...)` function can be used to produce an error message
to `STDERR`

```
void perror(const char* msg);

```

* `msg` - Contains a message to append to the start of the errno
message

---

## UNIX Environment Overview

* The UNIX environment provides both System Call and Library
Functions to the applications
* Library functions often add more specific functionality to the
system calls
* E.g. `sbrk` is the UNIX system call for managing memory - it
simply increases and decreases the address space for a specific
process
* `malloc` is the library function uses `sbrk` to allocate the space
and then provides the functionality to manage it. (i.e. The
ability to set up references to use the new memory space)

---

## Summary

* Welcome to COSC330/530
* House-Keeping
* Concurrency and Parallelism
* Resources and Machines
* Why Construct Concurrent Implementations?
* UNIX Environment Overview

---
class: middle, center

# Questions?

---

# Next Lecture

* The Process environment

* Process Control Primatives - `fork()`

---

# Reading

* Chapter 1, 7 and start chapter 8 from **Advanced Programming in the UNIX environment**
* **UNIX Programming Tools** - should be mostly revision
* **Assignment 1** Description
* **COSC330/530 Unit Information and Assessment Overview** - Pay Special Attention to the Assessment and Study Plan

---
