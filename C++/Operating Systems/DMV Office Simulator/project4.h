//--------------------------------------//
// Jordan Rosenberg            12-14-16 //
// CSCI 343 - Program 4                 //
// Prof. Ryder                          //
//--------------------------------------//

// HEADER FILE for project4_main.cpp

#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;

#define IFLAGS (IPC_CREAT|IPC_EXCL)
#define ERR ((struct myDataBuffer *) -1) // casting technique
#define PERMS 0600|IPC_CREAT|IPC_EXCL

// Memory Size of segment
const int MEMORY_SIZE = 1024;

//SEMAPHORE VALUES
const int INIT_SEMVAL = 1;
const int WAIT = -1;
const int RELEASE = 1;

// Prints any error msg and then quits
void fatal(char * msg)
{
	perror(msg);
	exit(1);
}

//--------------------------------------//
// Jordan Rosenberg            12-04-16 //
//                                      //
// Creates and initializes a semaphore  //
// ID                                   //
//                                      //
// Pre-conditions: none                 //
//                                      //
// Post-conditions: returns a semaphore //
// ID                                   //
//--------------------------------------//
int crtInitSem()
{
int semid;


if((semid = semget(IPC_PRIVATE, 1, PERMS)) < 0){ // NO_ERRORS
	fatal("ERROR: creating semaphore!");
}

// else initialize semaphore to 1
else{
	if (semctl(semid, 0, SETVAL, INIT_SEMVAL) < 0){ // NO_ERRORS
		fatal("ERROR: initializing semaphore!");
	}
	
}

return semid;

}

//--------------------------------------//
// Jordan Rosenberg            12-04-16 //
//                                      //
// A function to delete a semaphore     //
//                                      //
// Pre-conditions: requires a semaphore //
// ID                                   //
//                                      //
// Post-conditions: none                //
//--------------------------------------//
int removeSemaphore(int semid)
{
	int status;
	
	
	if ((status = semctl(semid, 0, IPC_RMID, 0)) < 0) // NO ERRORS
	{
		fatal("ERROR: removing semaphore!");
	}
	
	
	return(0);
	
}



//--------------------------------------//
// Jordan Rosenberg            12-04-16 //
//                                      //
// Semaphore Wait function              //
//                                      //
// Pre-conditions: requires a semaphore //
// ID                                   //
//                                      //
// Post-conditions: none                //
//--------------------------------------//
int p(int semid) // WAIT SEMAPHORE
{
	struct sembuf p_buf;
	p_buf.sem_num = 0;
	p_buf.sem_op = WAIT;
	
	// SEM_UNDO cleans up semaphore mistakes so the program doesn't crash!
	p_buf.sem_flg = SEM_UNDO;
	
	// semaphore ID, address of the argument structure, number of entries in semaphore set (1)
	if (semop(semid, &p_buf, 1) < 0) // NO ERRORS
	{
		fatal("ERROR: P() failed!");
	}
	
	return (0);
}

//--------------------------------------//
// Jordan Rosenberg            12-04-16 //
//                                      //
// Semaphore Signal function            //
//                                      //
// Pre-conditions: requires a semaphore //
// ID                                   //
//                                      //
// Post-conditions: none                //
//--------------------------------------//
int v(int semid) // SIGNAL SEMAPHORE
{
	struct sembuf v_buf;
	v_buf.sem_num = 0;
	v_buf.sem_op = RELEASE;
	
	// SEM_UNDO cleans up semaphore mistakes so the program doesn't crash!
	v_buf.sem_flg = SEM_UNDO;
	
	// semaphore ID, address of the argument structure, number of entries in semaphore set (1)	
	if (semop(semid, &v_buf, 1) < 0) // NO ERRORS
	{
		fatal("ERROR: V() failed!");
	}
	
	
	return (0);
}


