
class: bottom, left
background-image: url(images/g.png)

<h2 class="title_headings_sml">COURSE - Parallel and Distributed Computing</h2>

<h1 class="title_headings_sml"> Lecture 2 - Processes in Unix </h1>



---
## Reading
* Chapter 1, 7 and start chapter 8 from **Advanced Programming in the UNIX environment**
* **UNIX Programming Tools** - should be mostly revision
* **Assignment 1** Description
* **COURSE Unit Information and Assessment Overview** - Pay Special Attention to the Assessment and Study Plan

---

##Summary

* The Structure of a Program
* Process Control Basics
* The `fork()` System Call
* Examples

---

## The Structure of a Program

* Every C program has a `main` function:

```
int main(int argc, char* argv[]);

```
* This function is specified as the staring address for the program in the linking process during compilation.
* `argc` Specifies the number of command-line arguments
* `argv` is an array of string pointers that provide access to the command-line argument values (these are populated during start-up by a routine that obtains the values from the kernel)

---

## The Structure of a Program
* The example below shows the usage of command line arguments:

```
int
main(int argc, char *argv[])
{
	int i;

	for (i = 0; i < argc; i++)		/* echo all command-line args */
		printf("argv[%d]: %s\n", i, argv[i]);
	exit(0);
}
```

* `argc` is used as a loop termination condition to print the contents of `argv` to standard output.

---

## The Structure of a Program
* Environment Variables are name-value pairs managed by the operating system that typically store configuration information.
* Environment Variables are made available to a C program via a 3rd argument to the `main` function or via a global variable `extern char **environ;`.
* Most UNIX systems can use:

```
int main(int argc, char *argv[], char *envp[]);
```
* Environment variables can be accessed in `char *envp[]`.
* However ISO C specifies that the main function should only have two arguments. Therefore, your programs should use `extern char **environ;`

---

## The Structure of a Program
* The Structure of `extern char **environ;`

.center[![default-aligned image](img/lecture_02/environ.png)]

---

## The structure of a Program
* Upon execution, the machine instructions are loaded from some form of secondary storage into the main memory.
* The start-up routine that initialises the process sets up a contiguous memory space (the *image*) for the execution.
* This memory space consists of:
    1. The Text Area - Stores the program instructions (read-only)
    2. The **Initialized data area** - Initialised variables
    3. The **Uninitialized data area** - Empty variables
    4. **The heap** - Dynamically allocated memory (e.g. `malloc`, `calloc`)
    5. **The stack** - Automatic variables. (Variables in function calls)     

---

## The structure of a Program

* Below is an outline of the memory structure

.center[![default-aligned image](img/lecture_02/memory.png)]

---

## The structure of a Program

* Memory that is dynamically allocated at run-time is sourced from the heap.

```c
#include <stdlib.h>

// size_t is an integer (or long actually) type defined in stdlib
//Allocate a single block of size bytes
void *malloc(size_t size);

//Allocate an noObj length array of size bytes
void *calloc (size_t noObj, size_t size);

//Re-allocate the memory at ptr to be of newSize
void *realloc(void *ptr, size_T newSize);

//De-allocate and return the memory to the heap
void free(void *ptr)


```

---

## Process Control Basics

* POSIX defines the process ID a unique (non-zero) integer.
* It is used by the operating system to identify a process and it is often used as part of other identifiers.
* The scheduler, which is responsible for managing the execution of the process on a unix system, has a process ID of 0.
* Like size_t, process IDs are stored in a wrapper type `pid_t`, which will either be a long or an int. (IS pid_t signed or unsigned? why/why not?)

---
 
## Process Control Basics
* A process can access its own ID using `pid_t getpid(void)`

```c
#include <sys/types.h>
#include <unistd.h>

pid_t getpid(void);

```

---

## Process Control Basics
* `getpid(...)` is part of an entire family of system calls:

```c
#include <sys/types.h>
#include <unistd.h>
// Calling Process ID
pid_t getpid(void);
	   
// Parent of calling processes ID
pid_t getppid(void);
   
// Calling processes user ID
uid_t getuid(void); 
   
// Calling processes effective user ID
uid_t geteuid(void);
    
//  Calling processes group ID
gid_t getgid(void);
    
// Calling processes effective group ID
gig_t getegid(void);

```

---

## Process Control Basics

* Each process has a parent process (except the scheduler)
* A processes parent is the one that created it (`getppid(void)`)
* Each process has an owner (i.e. a particular user - `getuid(void)`)
* Each owner has specific privileges on the system
* Each owner is identified by a unique *user ID* (uid_t)

---

## Process Control Basics

* Every process has an effective user ID. This determines the privileges that a process has for accessing resources such as files.
* The effective user ID can change during execution and is determined by a call to `uid_t geteuid(void);`
* The effective user ID of a process is important for various reasons:
   1. for one process to send another process a signal,
   2. the two processes involved must both have the same effective user ID,or the sender should be root.
   3. so you can only kill processes with the same effective user ID.

---

## Process Control Basics

* A quick play on turing...

```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(void){
   printf("Process ID: %ld\n", (long)getpid());
   printf("Parent process ID: %ld\n", (long)getppid());
   printf("Owner user ID: %ld\n", (long)getuid());
   printf("Effective user ID: %ld\n", (long)geteuid());
   return 0;
}

```

---

## Process Control Basics

* Each process currently in execution will be in one of **five** states (on most systems) that reflect its status.
* Remember - Concurrency is the *potential* for parallelism... if there aren't enough cores to go around, swapping and scheduling is required

| State         | Meaning| 
|---------------|---------|
| New           | Process is being created|
| Running       | The process' instructions are currently being executed|
| Blocked       | The process is waiting for an event (e.g. i/o).|
| Ready         | The process is waiting to run (i.e. can execute but currently scheduled of the processor)|
| Done          | The process is finished and is being de-allocated|

---

## Process Control Basics

* In UNIX a process can become a zombie!
    * A zombie is a child process that has terminated prior to its parent waiting for it's exit status.
    * It remains until it is waited for.
* In UNIX a process can also become an orphan:
    * An orphan's original parent has died.
    * The orphan is adopted by the Init process!

---

## Process Control Basics

* There are a set of possible transitions between the process states:
 
.center[![default-aligned image](img/lecture_02/process_tans.png)]

---

## Process Control Basics

* The act of swapping out a running process (and replacing it with another process) is called a context switch.
* The ***context*** of a process is the information about the process (and its environment) that the operating system needs to restart it after a context switch.

---
## Process Control Basics
* The context contains such things as:
    1. the executable program
    2. the process state (stack, registers, program counter etc)
    3. the memory allocated to the process (static & automatic)
    4. the status of the processes i/o
    5. the process ID
    6. the parent process ID etc
    7. scheduling & accounting information
    8. signal status

---

## The `fork()` System Call

* This is the only way to create a new process (aside from system start-up)

```c
#include <sys/types.h>
 #include <unistd.h>
 pid_t fork ( void );	//Returns -1 on failure

```

---

## The `fork()` System Call
* When executed, `fork()` creates a new *child* process.
* The function executes once, but returns twice:
    1. The return value in the child is 0
    2. The return value to the parent is the ID of the child
* Both process (parent and child) continue executing from the instruction *following* the `fork()` call.
* The child is an exact copy of the parent (i.e. the child gets copy of the parents data-space, heap and stack)

---

## The `fork()` System Call
* A couple of quick points about `fork()`
    1. Most modern implementations don't *actually* create a complete copy of the parent's memory space.
    2. ***Copy-On-Wite*** (COW) is used - Memory space between the two process is shared until one of them executes a write operation. A copy in the child is then created
    
---

## The `fork()` System Call

* A call to `fork()` can fail, resulting in a `fork()`ing mess if you don't check for errors
* In this situation, `fork()` only returns once, with a -1
* `errno` is also set:
    1. `EAGAIN` - you already have too many processes going
    2. `ENOMEM` - you haven't got enough space left for this process

* Always check for `fork()`ing failures!

---
## The Make Utility 
* `make` is a UNIX utility for building application from source.
* It simplifies complex build processes
* Basically the `make` utility uses the instructions in the `makefile` to compile the code 

---

## The Make Utility

```makefile
COMPILER = gcc
CFLAGS = -Wall -pedantic

EXES = example01 forkex01  forkex02 forkex03 forkex04 forkex05 forkex06

all: ${EXES}


example01:  example01.c 
	${COMPILER} ${CFLAGS}  example01.c -o example01
forkex01:  forkex01.c 
	${COMPILER} ${CFLAGS}  forkex01.c -o forkex01
forkex02:  forkex02.c
	${COMPILER} ${CFLAGS}  forkex02.c -o forkex02
forkex03:  forkex03.c
	${COMPILER} ${CFLAGS}  forkex03.c -o forkex03
forkex04:  forkex04.c
	${COMPILER} ${CFLAGS}  forkex04.c -o forkex04
forkex05:  forkex05.c
	${COMPILER} ${CFLAGS}  forkex05.c -o forkex05
forkex06:  forkex06.c
	${COMPILER} ${CFLAGS}  forkex06.c -o forkex06
clean: 
	rm -f *~ *.o ${EXES}

```

---

## The Make Utility
* Constants defined in the first two lines
    1. Compiler is the GNU C Compiler
    2. Compiler options -Wall (warn-all) and -pedantic (looks for non-standard syntax etc.)
    3. The compilation targets (EXES) i.e. the Executables we want to compile
* Then the instructions for the compilation targets
    1. *all* is the default and is a super-set of the EXES
    2. *clean* executes `rm -f *~ *.o ${EXES}` to remove the object files and executables for a fresh build
* **All** of your assignments **WILL** have a makefile submitted with them otherwise they won't be marked.

---

## Example Applications
* We will look at a series of Examples to illustrate the `fork()` call

```c
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int main(void){
  pid_t foo;
  foo = fork();
  printf("hey i'm %ld and my foo is %ld\n", 
          (long)getpid(),
          (long)foo);
  return 0;
}

```

---

## Example Applications
* What will this example return?
* What is missing?

```c
foo = fork();
if(foo) 
  { /* parent code goes here */ }
else { /* child code goes here */ };
```
* **NO ERROR CHECKING!!!**

---

## Example Applications
* Lets try again:

```c
if((foo = fork()) < 0){ 
    /* fork error */
    perror("error in fork"); 
    exit(1); 
  } else if(foo){ 
    /* parent code here */ 
  } else { 
    /* child code  here */ 
}

/* code here will be executed by both  */
/* child and parent as long as they do */
/* not execute an call to exit or      */
/* abort in their code above           */
```
* This is the template that will get you good marks!

---

## Example Applications
* A *chain* of processes

```c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(void){
  int i, n = 4;
  pid_t childpid;
  for (i = 1; i < n;  ++i)
    if((childpid = fork()) < 0){ 
      /* fork error */
      perror("error in fork"); 
      exit(EXIT_FAILURE); 
    } else if(childpid){ 
      /* parent code */ 
*      break;
    } else { 
      /* child code */ 
    } 
  /* mutual code */ 
  printf("This is process %ld with parent %ld\n",
         (long)getpid(), (long)getppid());
  return 0;
}


```
---
## Example Applications

* Running this looks like:

```
turing.Examples> forkex02
This is process 25906 with parent 21711
This is process 25907 with parent 25906
This is process 25909 with parent 25908
turing.Examples> This is process 25908 with parent 25907
Note that the prompt returned before one of the spawned processes.
```

---

## Example Applications
* A *fan* of processes

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(void){
  int i, n = 4;
  pid_t childpid;
  for (i = 1; i < n;  ++i)
    if((childpid = fork()) < 0){ 
      /* fork error */
      perror("error in fork"); 
      exit(EXIT_FAILURE); 
    } else if(childpid){ 
      /* parent code */ 
    } else { 
      /* child code  */ 
*      break; 
    }
  /* mutual code */   
  printf("This is process %ld with parent %ld\n",
         (long)getpid(), (long)getppid());
  return 0;
}
```
---
##Example Applications

* Running it looks like:

```
turing.Examples> forkex03
This is process 25977 with parent 25975
This is process 25976 with parent 25975
This is process 25975 with parent 21711
This is process 25978 with parent 25975
turing.Examples>
```
* We can see who the point of the fan was, just by noticing that 25975 had a different parent than all the rest (and was the parent of all the others).

---
## Example Applications
* A *tree* of processes

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(void){
  int i, n = 4;
  pid_t childpid;
  for (i = 1; i < n;  i++)
    if((childpid = fork()) < 0){ 
      /* fork error */
      perror("error in fork"); 
      exit(EXIT_FAILURE); 
    } else if(childpid){ 
*      /* parent code */ 
    } else { 
*      /* child code  */ 
    } 
  /* mutual code */
  printf("This is process %ld with parent %ld\n",
         (long)getpid(), (long)getppid());
  return 0;
}
```

---
## Example Applications

```
turing.Examples> forkex04
This is process 26140 with parent 21711
This is process 26142 with parent 26140
This is process 26143 with parent 26141
This is process 26141 with parent 26140
turing.Examples> This is process 26146 with parent 1
This is process 26147 with parent 1
This is process 26145 with parent 1
This is process 26144 with parent 1
```

* Whats happening here? We've got some poor *Orphaned* process.
* Don't worry *Init* (the scheduler with process ID 1) has adopted them!

---
##Example Applications
* It's much better for us to wait for the children?

```c
/*See example07.c for includes*/

int main(void){
  int i, n = 4;
  pid_t childpid;
  int status;
  for (i = 1; i < n;  ++i)
    if((childpid = fork()) < 0){ 
      /* fork error */
      perror("error in fork"); 
      exit(EXIT_FAILURE); 
    } else if(childpid){ 
      /* parent code */ 
    } else { 
      /* child code  - sleep to force some orphans*/ 
      sleep(1);
      break; 
    }
  /* mutual code */   
  printf("This is process %ld with parent %ld\n",
         (long)getpid(), (long)getppid());
  return 0;
}

```

---
##Example Applications

* Well on turing we see the following:

```
./example07
This is process 19518 with parent 22381
[turing CZ120] $ This is process 19523 with parent 1
This is process 19521 with parent 1
This is process 19522 with parent 1

```

* Orphans!

---

## Example Applications
* Now with the wait() in place?

```c
/*See example07.c for includes*/
int main(void){
  int i, n = 4;
  pid_t childpid;
  int status;
  for (i = 1; i < n;  ++i)
    if((childpid = fork()) < 0){ 
      /* fork error */
      perror("error in fork"); 
      exit(EXIT_FAILURE); 
    } else if(childpid){ 
      /* parent code */ 
    } else { 
      /* child code  - sleep to force some orphans*/ 
      sleep(1);
       break; 
    }  
  printf("This is process %ld with parent %ld\n",
         (long)getpid(), (long)getppid());
  /* Very simple wait with no error checking */
  for (i=1; i < n; i++){
    wait(&status);
  }
  return 0;
}
```
---
##Example Applications

* Now we see the following:


```
turing CZ120] $ ./example07
This is process 6039 with parent 22381
This is process 6043 with parent 6039
This is process 6042 with parent 6039
This is process 6044 with parent 6039
[turing CZ120] $ 
```

---
##Example Applications

* One final example to demonstrate that memory between processes is **Not** shared.

```c
int		globvar = 6;		/* external variable in initialized data */
char	buf[] = "a write to stdout\n";

int main(void){
	int var;			/* automatic variable on the stack */
	pid_t	pid;
	var = 88;
	if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
		err_sys("write error");
	printf("before fork\n");	/* we don't flush stdout */

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {		/* child */
		globvar++;		/* modify variables */
		var++;
	} else {
		sleep(2);		/* parent */
	}
	printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,var);
	exit(0);
}


``` 

---

##Summary

* The Structure of a Program
* Process Control Basics
* The `fork()` System Call
* Examples
---
class: middle, center

#Questions?

---
# Reading
* Chapter 1, 7 and start chapter 8 from **Advanced Programming in the UNIX environment**
* **UNIX Programming Tools** - should be mostly revision
* **Assignment 1** Description
* **COURSE Unit Information and Assessment Overview** - Pay Special Attention to the Assessment and Study Plan

---
