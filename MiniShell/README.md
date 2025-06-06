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
	fork();
	printf("Hello world!");
}
```

If we use the fork() function on a normal code like printing `hello world` we gonna notice that the message is printed twice, but why ?
<p align="center"> 
	<img src="https://i.imgur.com/3cIDvk1.png" width=500>
</p>

