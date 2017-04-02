//--------------------------------------//
// Jordan Rosenberg            12-14-16 //
// CSCI 343 - Program 4                 //
// Prof. Ryder                          //
//--------------------------------------//

// CPP file for project4.h

#include "project4.h"
#include <string>

	// number of seats that are in the DMV office
	int seats = 5;
	
    // Amnt of time dealing with a clerk
	int waitTime = 3;
	int processCost = 7;

	int dmvSemID;
	
    // for keeping track of when to wake clerk up or not;
	int clerkSemID;	

struct myDataBuffer
{
	// How many seats are taken
	int seats_taken;
	
	// How many people are processed
	int peopleProcessed;
	
	// When the clerk is resting or not
	bool resting;
	
	// Number of people currently sitting at the chair next to the DMV Clerk's desk (0 or 1)
	bool serving;
	
	// How many people are turned away
	int turnedAway;
	
	// When the clerk should stop working/looping
	bool clockout;
};

struct myDataBuffer * attachSegment(int shmid);
int createSegment(int size);		

// Parent Process	
void bouncer(struct myDataBuffer *);

// Child Process
void clerk(struct myDataBuffer *);	

//--------------------------------------//
// Jordan Rosenberg            12-04-16 //
//                                      //
// Creates the shared memory segment and//
// and semaphores, and then deletes them//             
//                                      //
// Forks a new process and gives the    //
// "clerk" (child) process its own task //
//                                      //
// Pre-conditions: none                 //
//                                      //
// Post-conditions: program returns 0   //
// and ends                             //
//--------------------------------------//
int main()
{
    // The return code status from the child (clerk) process
	int status;
	
	// keeps track of process ID
	int pid;
	
	// the buffer that holds our stats/data
	struct myDataBuffer * dmvStats;
	
     // Creates and attaches the shared memory segments.
	int shmid = createSegment(MEMORY_SIZE);
    dmvStats = attachSegment(shmid);
	
	// for keeping track of the bouncer
	dmvSemID = crtInitSem();
	
	// for keeping track of when to wake clerk up or not
	clerkSemID = crtInitSem();
	
	// Set report data/stats to their initial values
	// =================================
	dmvStats->seats_taken = 0;
	dmvStats->turnedAway = 0;
	dmvStats->peopleProcessed = 0;
	
	dmvStats->resting = false;
	dmvStats->serving = false;
	dmvStats->clockout = false;
	// ==================================
	
	switch(pid = fork())
	{
		// Fork() Error
		case -1: 
		fatal("ERROR: fork failed!");

		// Clerk
		case 0:
		clerk(dmvStats);
		break;

		// Bouncer
		default:
		bouncer(dmvStats);
		wait(&status);
		removeSemaphore(dmvSemID);
		removeSemaphore(clerkSemID);
		
		shmctl(shmid, IPC_RMID, 0); // release shared memory segment

	}
	
	return 0;

}

//--------------------------------------//
// Jordan Rosenberg            12-04-16 //
//                                      //
// Dumps specific data processed        //
// throughout the program.              //
// (Code speaks for itself here)        //
//                                      //
// Pre-conditions: uses a myDataBuffer  //
// struct in the parameter              //
//                                      //
// Post-conditions: none                //
//--------------------------------------//
void report(struct myDataBuffer * dmvStats)
{
	// wait (asks permission for process to go)
	//p(semid);

	cout << "Total Seats: " << seats << endl;
	cout << "Occupied Seats: " << dmvStats->seats_taken << endl;
	// Number of people currently sitting at the chair next to the DMV Clerk's desk (0 or 1)
	cout <<"People dealing with Clerk: " << dmvStats->serving << endl;
	
	// Amnt of time dealing with a clerk - 3 seconds suggested
	cout << "Processing Time with Clerk: " << waitTime << " second(s)" << endl;
	
    cout << "# of people processed: " << dmvStats->peopleProcessed << endl;

    cout << "Process Fee: " << processCost << endl;	

    cout << "Today\'s profit: " << dmvStats->peopleProcessed * processCost << endl;	

	cout << "# of people turned away: " << dmvStats->turnedAway << endl;

    cout << "Lost Profit: " << dmvStats->turnedAway * processCost << endl;

	//signal (tells processes they can now go)
	//v(semid);
}

//--------------------------------------//
// Jordan Rosenberg            12-11-16 //
//                                      //
// Parent process which acts like a     //
// "bouncer".                           //
//                                      //
// - If user presses the ENTER key,     //
// a customer enters the DMV.           //
// - If the S key is pressed, the data  //
// report is dumped to the console      //
// - If the Q key is pressed, the program
// finishes, waiting for the clerk first//
//                                      //
// Pre-conditions: uses a myDataBuffer  //
// struct in the parameter              //
//                                      //
// Post-conditions: none                //
//--------------------------------------//
void bouncer(struct myDataBuffer * dmvStats)
{
	// user input
	string menuInput;
	
	cout<<"Welcome to the DMV Office"<<endl;
	cout<<"=========================="<<endl;
	
	do
	{	
	cout<<"Press the \'ENTER\' key to add a customer"<<endl;
	cout<<"Press the 's' key to dump a status report"<<endl;
	cout<<"Press the 'q' key to quit the program"<<endl;
	cout<<"\n-> ";
	
	getline(cin, menuInput);
		
	    // if S key was pressed
		if (menuInput == "s")
		{
			p(dmvSemID);
			report(dmvStats);
			v(dmvSemID);
		}
		
		// if ENTER key was pressed
		else if (menuInput.empty()) //if the entered string was empty
		{
			cout<<"A customer has walked in..."<<endl;
			p(dmvSemID);

			// if no seats are taken (implying clerk may be free to help someone)
			if (dmvStats->seats_taken == 0)
			{
			
			    // if no one is being served,
				// the clerk will serve the next customer
			    if (dmvStats->serving == false)
			    {
					dmvStats->serving = true;
				} 
							
				// if the clerk is already serving, 
				// put another customer on a waiting chair
				else
					dmvStats->seats_taken++;	
				
			}
			
			// otherwise if less than 5 seats are taken,
			// then place the customer in one of them
			else if (dmvStats->seats_taken < 5)
			{
				dmvStats->seats_taken++;
			}
			
			// otherwise we know there are no more chairs left, and we're full.
			// thus, turn the customer away and kick him out!
			else
			{
				cout<<"A customer has been turned away because seats are full."<<endl;
				dmvStats->turnedAway++;			
				
			}
			
			//Signal
			v(dmvSemID);		
			
			if (dmvStats->resting == true)
				v(clerkSemID);
			
		}
			
	}while(menuInput != "q"); // Keep looping if user did not want to quit
	
	// dump the report to the console after quiting
	report(dmvStats);
	
	// output # of customers that were still waiting in line
	cout<<dmvStats->seats_taken<<" customers were still waiting before office closed."<<endl;
	
	// this lets the clerk (child) process know it can finish for the "day"
	dmvStats->clockout = true;
	
}

//--------------------------------------//
// Jordan Rosenberg            11-1-16  //
//                                      //
// "Clerk" (child) process that "deals" //
// with the customers that the bouncer  //
// places into the chairs.              //
//                                      //
// Pre-conditions: uses a myDataBuffer  //
// struct in the parameter              //
//                                      //
// Post-conditions: none                //
//--------------------------------------//
void clerk(struct myDataBuffer * dmvStats)
{
	// if the bouncer says its not time to clock out of work for the day,
	// then keep looping (keep working).
	while(!dmvStats->clockout)
	{
		// if there are customers waiting to be served,
		// then start serving and take a waiting customer.
		if (dmvStats->seats_taken > 0)
		{
			// Wait
			p(dmvSemID);
			dmvStats->seats_taken--;
			dmvStats->serving = true;
			cout << "Clerk is serving."<<endl;
			
			// Signal
			v(dmvSemID);
		}
		
		// also, if the clerk is STILL serving, process that customer for
		// 3 seconds (recommended), and tally up a customer processed
		if (dmvStats->serving)
		{
			cout<<"Clerk processing a customer for 3 seconds"<<endl;
			sleep(3);
			cout<<"Finished processing customer"<<endl;
			// Wait
			p(dmvSemID);
			dmvStats->peopleProcessed++;
			dmvStats->serving = false;
			cout << "Clerk is not serving."<<endl;
			// Signal
			v(dmvSemID);
		}
		
		// otherwise, clerk rests when there isn't anyone left to be processed
		// while it's not closed yet
		else{
			
			dmvStats->resting = true;
			cout<<"clerk resting since no one is left to be processed"<<endl;
			
			// Wait
			p(clerkSemID);
	
			dmvStats->resting = false;		
		}			
	}		
}


//--------------------------------------//
// Jordan Rosenberg            12-06-16  //
//                                      //
// Creates a shared memory segment and  //
// returns the ID of it.                //
//                                      //
// Pre-conditions: Takes a integer for  //
// the byte size of the shared memory   //
// segment as a parameter.              //
//                                      //
// Post-conditions: returns the shared  //
// memory ID                            //
//--------------------------------------//
int createSegment(int pSize)
{
	    // shared segment id
        int shmid; 

		// Try to create the shared memory segment. (IPC_CREAT | IPC_EXCL) means it will only create
		// If shmget() returns a itemValue less than 0, it failed.
        if((shmid = shmget(IPC_PRIVATE, pSize, ( 0600 | IPC_CREAT | IPC_EXCL ))) < 0)
        {
                cout << "ERROR: Failed to create the shared memory!" << endl;
                exit(1); // Will terminate program with exit code of 1, because of a memory error
        }

        return shmid;
}

//--------------------------------------//
// Jordan Rosenberg            12-06-16  //
//                                      //
// Attaches the shared memory ID to a   //
// data buffer structure and returns    //
// a pointer to it                      //
//                                      //
// Pre-conditions: Takes a shared mem   //
// ID as the parameter.                 //
//                                      //
// Post-conditions: Returns a pointer to//
// the attached shared data buffer      //
//--------------------------------------//
struct myDataBuffer * attachSegment(int shmid)
{
	    // create a pointer to point to a data buffer
        struct myDataBuffer * dataBuf;

		// Attaches the shared memory ID to a data buffer, and dataBuf points to it  
        if((dataBuf = (struct myDataBuffer *) shmat(shmid,(char *)0, 0)) == ERR)
        {
                cout<<"ERROR: Failed to attach a shared memory buffer";
                exit(1);
        }

        // Returns a pointer to the newly attached data buffer		
        return dataBuf;
}




