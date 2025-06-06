<h1 align= "center"><b>Minishell</b></h1>

### Table of Contents
-[Processes](#processes)  

# Processes

We will take look at how to work with multiple processes inside our C programs, how to communicate between them.  

## fork() Function 

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

If we use the fork() function on a normal code like printing `hello world` we gonna notice that the message is printed twice, but why ?  

<p align="center"> 
	<img src="https://i.imgur.com/Lu0pybW.png" width=400>
</p>

**What happened ?**  
When calling `fork()` function a new **child process**  is born and start executing the following lines.  
The `fork()` function return an integer that represent the `Id` of the process, generally the child process got the `id = 0` when success  and `id = -1` if it fails.  

**Fork multiple times**  
The mathematical equation on multiple forks is : `2^n` so 2 forks gives us 2^2 processes which is 4, and for 4 forks we get 16 processes.   

On this example there is two forks on the main function, if we run the program we gonna notice that 4 "hello world" are printed.  
<p align="center"> 
	<img src="https://i.imgur.com/IZNC3GT.png" width=400>
</p>