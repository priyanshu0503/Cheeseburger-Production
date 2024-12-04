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
gcc -c driver.c -o driver.o
gcc -c producer.c -o producers.o
gcc producers.o driver.o -o cheeseburger_production -lpthread
How to run:
./cheeseburger_production
The program will prompt you to enter the number of burgers you want to produce.
******************************************************************************
OVERVIEW:
The program includes 3  producers as follows: 
	Three milk producers produce milk bottles.
	Two cheese producers consume milk to create cheese slices.
	One cheeseburger producer consumes cheese to produce cheeseburgers.
******************************************************************************
The program manages two buffers: a glass of milk in size 9 and cheese in size 4. Each milk producer thread makes milk bottles, which is used by cheese producers to make cheese once there are at least three bottles on hand. The cheeseburger producer will use two slices of cheese to make a cheeseburger.
Milk Producers produce milk bottles and store them in a shared buffer. Whereas Cheese Producers convert three milk bottles into a slice of cheese, represented by a unique ID. Cheeseburger Producers consume two slices of cheese to make  a cheeseburger and prints the cheeseburger ID.
The program uses semaphores to synchronize access to shared buffers. Semaphores ensure that only one thread can access a buffer at a time, preventing race conditions and ensuring correct production and consumption of resources. The semaphore's initial value determines how many threads can access the resource concurrently.
Synchronization to make different threads work safely with shared resources is done by using semaphores, mutexes. With the help of pthread_join the program then waits for all the threads to exit. The output also consists of the cheques that have printed cheeseburger IDs as evidence of success of various production processes.


