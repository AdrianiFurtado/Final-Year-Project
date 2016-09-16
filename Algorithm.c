#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

// Structure creation
typedef struct node{
	
	int ID;
	int NUT;
	int NUTRESET;
	char STATE;
	int CONTINUOUS;
	int REC;
	int DEADLINE;
	int CYCLES;
	int DONE;
	struct node *next;

} node;
//******************

//Function initiation

void addTail(node * normalQ, int NUT, int id, int continuous, int cycles);

void fileReader(node * normalQ, node* contQ );

void roundRobin(node * normalQ, node * contQ ,int Quanta);

void realtime(node * normalQ, node * contQ, int Quanta);

void listValues(node * normalQ, int quanta);
//******************
 

//Creation of global variables
static int counter =-1;
static int warden =0;
static int idAlloc = 1;
static int lateArrival = 0;
static int print = 1;
//*******************

int main(){

	//Initial Node allocation for both queues
	node * normalQ = NULL;	
	normalQ = malloc(sizeof(node));
	normalQ->next = NULL;

	node * contQ = NULL;
	contQ = malloc(sizeof(node));
	contQ->next = NULL;
	//************************************

	int quanta =2;

	//Check node pointer for problem
	//if(first == NULL){

	//	return 1;
	//}
	//****************************


	//Call functions to start the program 	
	fileReader(normalQ, contQ);	
	listValues(contQ, quanta);
	realtime(normalQ, contQ, quanta);
	//**********************************
	
	return(0);
}


//Function to list values held inside all allocated nodes
void listValues(node * normalQ, int quanta){

	node * current = normalQ;

	//Loop to print value held inside continuous nodes	
	while(current != NULL){
		printf("P%i NUT:%i CONTINUOUS:%i RECURRE EVERY:%i\n",current->ID , current->NUT, current->CONTINUOUS, current->DEADLINE);	
		current = current->next;
			
	}
	//*****************

	printf("Quanta = %i\n\n", quanta);
}
//****************


//Function to perform the Round Robin Algorithm
void roundRobin(node * normalQ , node * contQ,int Quanta){

	node * first = normalQ;
	node * current = first;
	node * delete = first;
	int quanta = Quanta;
	int qCounter = 0;
	
	//Main loop of function
	while(first != NULL){
		qCounter = quanta;

		while(qCounter != 0){
			qCounter--;
			if((first->NUT-=1) ==0)break;
		}
		first->STATE = 'W';

		current = first;
		//print all node values
		while(current != NULL){

			printf("P%i NUT:%i",current->ID , current->NUT);	
			current = current->next;
			printf("\n");

		//free the nodes with the values of 0
			node * delete = first;
			if(first->NUT <=0){
			
				delete = first;
				if(first->next != NULL){
					first = first->next;
					free(delete);
				}else{
					first = NULL;
				break;
				}		
			}

		}

		printf("\n");
		current = first;
		
		//Move processes in and out of the CPU
		if(first != NULL && first->next != NULL){
			while(current != NULL){
				current = current->next;
				if(current->next == NULL){
					current->next = first;
					current = current->next;
					first = first->next;
					current->next = NULL;
					break;
				}
			
			}
		}
		//*****************
	
		fileReader(normalQ, contQ);

	}
	//---------------------------------

	printf("\n");

}
//**************


//Function to perform the "Fitting" algorithm
void realtime(node * normalQ, node* contQ, int Quanta){

	node * currentN = normalQ;
	node * currentC = contQ;
	node * process;
	int quanta = Quanta;

	while(1){

		int quanta = Quanta;
		currentC = contQ;
		//Assign deadline values
		while(currentC){

			currentC->CYCLES = currentC->DEADLINE - currentC->NUT;
			if(currentC->next == NULL) break;
			currentC = currentC->next;

		}//********************

		printf("Before sorting\n");
		currentC = contQ;
		while(currentC != NULL){

			printf("P%i DEADLINE IN%i\n", currentC->ID, currentC->CYCLES);
			if(currentC->next == NULL)break;
			currentC = currentC->next;

		}

		//sort nodes from lowest deadline to highest
		currentC = contQ;
		int qHead = 1;
		while(currentC){
			node * temp;
			node * previous;

			//Swap nodes around	
			if(currentC->CYCLES > currentC->next->CYCLES){
			
				if(qHead){
	
					temp = currentC->next;
					currentC->next = currentC->next->next;
					temp->next = currentC;
					currentC = temp;
					temp = NULL;
					contQ = currentC;
				}else{

					temp = currentC->next;
					currentC->next = currentC->next->next;
					temp->next = currentC;
					currentC = temp;
					previous->next = currentC;
					temp = NULL;

				}

				currentC = contQ;
				qHead = 1;
			}else{
				previous = currentC;
				currentC = currentC->next;
				qHead = 0;
				if(currentC->next == NULL)break;

			}

		}//******************

		printf("\n");
		printf("After Sorting\n");
		currentC = contQ;

		//Print nodes after sorting has been performed
		while(currentC != NULL){

			printf("P%i NUT%i DEADLINE%i DEADLINE IN%i DONE%i\n", currentC->ID, currentC->NUT,currentC->DEADLINE, currentC->CYCLES, currentC->DONE);
			if(currentC->next == NULL)break;
			currentC = currentC->next;
	
		}
		//*****************

		printf("\n");
		currentC = contQ;
	
		//Process the head of the queue
		while(quanta){

			currentC = contQ;
		
			//Check if current task is already done
			while(currentC->DONE == 1){

				if(currentC->next == NULL) break;
				currentC = currentC->next;


			}
			//***************

			//process the task
			printf("Processing P%i\n", currentC->ID);
			currentC->NUT--;
			//**********

			//Check if task has been fully processed 
			currentC = contQ;
			if(currentC->NUT == 0){

				currentC->DONE = 1;
				currentC->NUT = 0;
				while(currentC->next != NULL){
					
					currentC = currentC->next;
	
				}

				currentC->next = contQ;
				contQ = contQ->next;
				currentC->next->next = NULL;
				break;

			}	
			//****************

			currentC = contQ;

			//Cycle continuous queue and decrement each node's deadline value
			while(currentC != NULL){

			        if(currentC->DEADLINE > 0){
					
					currentC->DEADLINE--;
				}
				if(currentC->next == NULL) break;
				currentC = currentC->next;
			}
			//**************

			quanta--;

		}//************************

		//Given that all tasks are completed, switch to normal queue
		currentC = contQ;
		while(currentC != NULL && currentC->DONE == 1){

			if(currentC->next == NULL){printf("Switching to normal processes\n"); exit(1);}
			currentC = currentC->next;

		}
		//**********************

	}
}

//function to read from text file
void fileReader(node * normalQ, node * contQ){

	FILE *fp = fopen("proc.txt","r");

	char buffer[50];
	int tempNUT;
	int tempAT;
	int continuous;
	int recurring;

	while(1){
		//read from file until all values have been read
		if(fgets(buffer,50,fp)!= NULL){
			
			counter++;
			if(counter > 0){
			
				//Error checking not fully implemented yet
				//if((buffer[0] < 0 || buffer[0] > 9) || (buffer[2] < 0 || buffer[2] > 9 )|| (buffer[4] < 0 || buffer[4] > 9 ) || (buffer[6] < 0|| buffer[6] > 9 )){

				//	printf("Error! program exiting\n");
				//	exit(99);
				//}
				//******************

				//Store buffer values into temporary variables
				tempAT = buffer[0] - '0';
				tempNUT = buffer[2] - '0';
				continuous = buffer[4] - '0';

				//Check if recurrence is greater than 9 
				if(buffer[7] != '\n'){

					//if recurrence is greater than 9 read first value
					//and multiply by 10 to get the decimal equivalent
					recurring = (buffer[6] - '0') * 10;
					recurring += (buffer[7] - '0');

				}else{
				
					//if value is between 1-9 just read value normally
					recurring = (buffer[6] - '0');

				}
			
				//Check if task arrival time matches the warden to allocate it into a node
				if(tempAT == warden){

					//check if task is continuous or not
					if(continuous == 1){
						addTail(contQ, tempNUT, idAlloc, continuous, recurring );
						idAlloc++;
					}else{
					
						//code for normal queue
					}
				}
				//******************
			}
		}else{
			warden++;
			print = 0;
			break;
		}
	}
	
	fclose(fp);
}

//add nodes to the end of the queue*
void addTail(node * normalQ, int NUT, int id, int continuous, int recurring){

	node * current = normalQ;




	//if its the first process
	if(id == 1){
		current->NUT = NUT;
		current->NUTRESET = NUT;
		current->ID = id;
		current->CONTINUOUS = continuous;
		current->REC = recurring;
		current->DEADLINE = recurring;
	}else if(id > 1){

		while(current->next != NULL){
		
			current = current->next;

		}
	//other process
		current->next = malloc(sizeof(node));
		current->next->ID = id;
		current->next->NUT=NUT;
		current->next->NUTRESET = NUT;	
		current->next->CONTINUOUS = continuous;	
		current->next->REC = recurring;
		current->next->DEADLINE = recurring;
		current->next->next = NULL;
	}
}
