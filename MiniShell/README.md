<h1 align= "center"><b>Minishell</b></h1>

---
 **Table of Contents :**  
[Processes](#processes)   

---
# Processes

We will take a look how to work with multiple processes inside our C programs and how to communicate between them.  

**But first! What is a process ?**  
A process is an instance of a computer program that is being executed, the program is a static set of instructions, while the process is a dynamic execution of those instructions.  

## Fork Function 

`fork()` is a system call used for creating a new process in Linux systems which is called the **child process**, it returns :  
+ **Negative value** `-1` if the creation of a child process was failed;  
+ **Zero** returned to the new child process which created;  
+ **Positive value** returned to the parent or caller.

```C
#include<stdio.h>
#include<unistd.h>

int main ()
{
	printf("before fork()\n");
	fork();
	printf("After calling the function fork()\n");
}
```

If we use the `fork()` function on a normal code like printing `After calling the function fork()` we'll notice that the message printed twice, why ?  

<p align="center"> 
	<img src="https://i.imgur.com/Lu0pybW.png" width=400>
</p>

**What happened ?**  
When calling `fork()` function a new **child process**  is born and start executing **the following lines.**   
The `fork()` function return an integer that represent the `Id` of the process, the child process always got the `id = 0` when success  and `id = -1` if it fails.  

**How to `wait` for processes to finish**  
The `wait()` function is used in C by a parent process to pause its execution until **one** of its child processes has finished executing.   
It returns the process ID of the terminated child process, if there are no child processes to wait for, or if an error occurs it returns `-1`, example of an example when there is no children to wait.  

## Processes IDs

**Process IDs** are just identification numbers of running processes assigned by the operating system, each process in Linux has its own number ID that is **unique**.  

**`getpid();` :**  
To get the process ID of a process we call the function **`getpid();`** It returns an `pid_t` represented as an integer.  
 **`getppid();` :**  
 The function that help us to get directly the parent ID of a process is `getpid();` by reference to get the parent process ID.  

```C
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main ()
{
        int  i;

        i = fork();
        if (!i)
        {
	        sleep(1);
	        printf("Child Process : Current ID : %d, Parent ID : %d", getpid(), getppid());
        }
        else
	        printf("Main Process : Current ID : %d, Parent ID : %d", getpid(), getppid());
        printf("\n");
        return 0;
}

```

<p align="center">
	<img src="https://i.imgur.com/El1FwYI.png"  width="650">
</p>

We'll notice that the parent process of the child process is not the main process, why is that ?  
So because we sleep the child process, the main process which is the current child parent process has been terminated, so while the child process continue after sleeping, a new process assigned to it as its new parent process.  

That's why we need always to use the `wait()` function so the parent process wait until its child process terminate and then continue, simply we add  the next line to our code :  
```C
int main
{
	// previous code
	if (i)
		wait(NULL);
	return (0);
}
```

<p align="center">
	<img src="https://i.imgur.com/BpJL206.png"  width="550">
</p>

## Fork multiple times
 
The mathematical equation on multiple forks is : `2^n` so 2 forks produce 4 processes, and for 4 forks 16 processes.   

On this example there is two forks on the main function, if we run the program we gonna notice that 4 "hello world" are printed.  
<p align="center"> 
	<img src="https://i.imgur.com/IZNC3GT.png" width=400>
</p>


Let's make a code of this situation :   
```C
#include <stdio.h>
#include <unistd.h>

int main ()
{
	int id1;
	int id2;

	id1 = fork();
	id2 = fork();
}
```

Let's visualize that's going on here :  
<p align="center"> 
	<img src="https://i.imgur.com/wLGn2jL.png" width="500">
</p>

```C
#include <stdio.h>
#include <unistd.h>

int main ()
{
	int id1;
	int id2;

	id1 = fork();
	id2 = fork();
	if (!id1)
	{
		if (!id2)
			printf("We are process y\n");
		else
			printf("We are process x\n");
	}
	else
	{
		if (!id2)
			printf("We are process z\n");
		else
			printf("We are the parent process!\n");
	}
	while (wait(NULL) != -1 || errno != ECHILD);
	return (0);
}
```
**what `wait(NULL) != -1` mean ?**  
The `wait()` function return `-1` when it fails or where there is no child to wait;  

**What `errno`, `ECHILD` stands for ?**  
+ **`errno` :** is a global variable defined in `<errno.h>` that stores an error code when a function fails.   
  Error code is a number or a symbol used by a program or operating system to indicate that something went wrong, for example when a program tries to do something it might fail, instead of just saying "it failed" the system gives an error code (a number) that explains why it failed;

+ **`ECHILD` :** is a specific error code stored in `errno`, it means **NO CHILD PROCESS!**, we get `ECHILD` when calling `wait()` and there is no child process to wait for, so when checking `errno != ECHILD` that's mean that the while loop should check if there is a child to execute what is inside the loop;  


## Pipes

Pipe() system call it is a file-like that lives in the memory not on the disk, a connection between two processes,  pipe() is one-way communication only, such as the standard output from one process become the standard input of the other process.  


<p align="center"> 
	<img src="https://i.imgur.com/adcnQYi.png" width="600">
</p>

**Syntax :**  
`int pipe(int fds[2]);`. Parameters :  
+ **ft\[0] :** will be the file descriptor for the **read** end of pipe;  
+ **ft\[1] :** Will be the file descriptor for the **write** end of pipe;
+ **Returns :**
	+ **`0`** on success;
	+ **`-1`** on error.  

On the next example we gonna send a message from the child process to the parent :   

```C
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main ()
{
	int fd[2];
	int id;
	char str[29];

	if (pipe(fd) < 0)
		exit(1);
	id = fork();
	if (!id)
	{
		close(fd[0]);
		write(fd[1], "Sent from the Child process!", 29);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		read(fd[0], &str, 29);
		close(fd[0]);
		write(1, str, 29);
	}
}

```

Calling `pipe()` before `fork()` is essential to communicate between the child and the parent process, that's ensure that both processes inherit the same pipe file descriptors `fd[0]` and `fd[1]`;  
If you call `fork()` before the `pipe()` the child process won't know about the pipe the parent created.

<p align="center"> 
	<img src="https://i.imgur.com/RiVyW3D.png" width="400">
</p>

## FIFOs

FIFO also known as **named pipe** is a special type of file used for interprocess communication.   

**What is the difference between the traditional pipes (unnamed), and the named pipes (FIFOs) ? And why they called like that ?**  
+ **Unnamed Pipes :** They are the traditional pipes which are temporary and exist only as long as the process that created them is running, they called unnamed because they not exist as a file in the filesystem. 

+ **Named Pipes :** FIFOs are a powerful mechanism for inter-process communication, you can read and write from any open process as long as the system is up.  Called named because it has a name in the filesystem.

<p align="center"> 
	<img src="https://i.imgur.com/O1Lh0D1.png" width="400">
</p>

**Create a FIFO :**  
The file of the named pipe (FIFO) which allow the communication between two or more processes by reading and writing to the same file is created using the **`mkfifo();`** system call.  
Once created, any process can open the named pipe for reading and writing.  
We need to include :  

```C
	#include <sys/stat.h>
	#inlcude <sys/types.h>
```

So first we need to create the FIFO file :  `int mkfifo (const char *pathname, mode_t mode);`  

+ **pathname :** the name of the file or also with its path, for example `"newfile"` gonna create the file at my current directory, when using `"/tmp/newfile"` gonna create the file on the tmp path;  
+ **mode :** is the permissions of the file, represent who can access what in a file on  a UNIX system, 0777 to say this file is gonna be able to be read from or read to to **anybody** ;
<p align="center"> 
	<img src="https://i.imgur.com/CHZ5Iti.png" width="500">
</p>

+ **`mkfifiReturns values :** `0` when success and `-1` if it fails.


Let's create a FIFO file and write into it a message `"Am inside the fifo file!"` :  
```C
#inlcude <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main ()
{
	int fd;
	char str[25] = "Am inside the fifo file!";
	
	if (mkfifo ("myfifofile", 0777) == -1)
		return (1);
	fd = open ("myfifofile", O_WRONLY );
	if (write (fd, str, 25) == -1)
		return (2);
	close (fd);
	return (0);
}
```

If we execute this code you gonna notice that it will hang!  
The problem is from the `open` system call, on the manual of `open`  :  
<p align="center"> 
	<img src="https://i.imgur.com/8AbcgQg.png" width="700">
</p>
So we need another process to open the same FIFO file for reading.  

