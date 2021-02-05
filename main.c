//CS2211a 2020
//Assignment 4
//Shanker Nadarajah
//250877841
//snadar5
//Nov 16 2020

 
#include "mainHeader.h" 

int main () {
	//initialize input array, current line number and double pointer for sentence structure array 
	char str[1000];
	int lineNumber = 0;
	input = (line **) calloc (1, sizeof(line));
	
	//loop to initiate the program to ask for input
	do{
	printf("Please enter a string, or just enter to proceed: ");
	fgets(str, 1000, stdin);
	lineNumber ++;
	str[strcspn(str,"\n")]=0; //to remove the newline character kept by fgets 
	createLine(input, lineNumber, str); //this adds the entered line into a sentence structure 
	}while(str[0]!='\0');
 	
	printf("\nThese are all the words printed out one at a time:\n");
	printWords(input, lineNumber);
	printf("\nThese are all the lines printed out as you had entered them:\n");
	printLines(input, lineNumber); 	
	
	//Now for the search function
	do{
	printf("Now enter a word to search:\n");
	fgets(str,1000, stdin);
	str[strcspn(str, "\n")]=0; //getting rid of the pesky newline again
	search(input, lineNumber, str);
	} while(str[0]!= '\0');
	
	//free memory at the end	
	free(input);
}


