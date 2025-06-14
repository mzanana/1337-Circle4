<h1 align= "center"><b>Minishell</b></h1>

---
 **Table of Contents :**  
[Processes](#processes)   

---
# Processes

We will take a look how to work with multiple processes inside our C programs and how to communicate between them.  

**But first! What is a process ?**  
A process is an instance of a computer program that is being executed, the program is a static set of instructions, while the process is a dynamic execution of those instructions.  

## fork() Function 

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

**Fork multiple times**  
The mathematical equation on multiple forks is : `2^n` so 2 forks produce 4 processes, and for 4 forks 16 processes.   

On this example there is two forks on the main function, if we run the program we gonna notice that 4 "hello world" are printed.  
<p align="center"> 
	<img src="https://i.imgur.com/IZNC3GT.png" width=400>
</p>

**How to `wait` for processes to finish**  
The `wait()` function is used in C by a parent process to pause its execution until one of its child processes has finished executing.   
It returns the process ID of the terminated child process, if there are no child processes to wait for, or if an error occurs it returns `-1`.  
 