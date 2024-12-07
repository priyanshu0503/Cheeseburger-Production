# Cheeseburger-Production
The entire program was written using C language. The program uses POSIX threads and semaphores, which are available on Linux and macOS systems.
We must make sure following libraries are installed:
1)	pthread (for creating threads)
2)	semaphore.h (for semaphores)

****************************************************************************
Files Included:
1)	driver.c - the main driver program that create and joins the threads. Also, calls the producer functions.
2)	producer.c- program that contains all the logic and functionality of the Producer and Consumer. This includes milk producer, cheese producer and cheeseburger producer function.
3)	producer.o- header file that contains all the functions declaration and external variables.

****************************************************************************
How to compile:
I used C compiler GCC to compile and run the multithreaded program. 
gcc -pthread main.c producer.c -o cheeseburger_production 

****************************************************************************
How to run:
./cheeseburger_production
The program will prompt you to enter the number of burgers you want to produce. 
