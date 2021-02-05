//CS2211a 2020
//Assignment 4
//Shanker Nadarajah
//250877841
//snadar5
//Nov 16 2020
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct words {
	char *actualWord; 
	int charTotal;
	int position;
} word; 

typedef struct sentences {
	word *wordArray;
	int wordTotal;
	int linePosition;
} line;

//First method createLine creates a pointer to a dynamic memory array to be used for the structures above 
void createLine(line **lineArray, int lineNumber, char inputString[]) {
	//either creating the dynamic array, or reallocating if we've already done so
	if(lineNumber ==1) {
		*lineArray = (line *) calloc (1, sizeof(line));
	} 
	else {
		*lineArray = (line *) realloc (*lineArray, lineNumber*sizeof(line));
	}
	//Looks messy but this is perfect I swear...
	//First I add the first word structure, that allows me to use calloc
	//Then I have a second loop for each following word, using realloc
	int i =0; //index to go through user input character array
	int index = lineNumber - 1; //this index is for the index of the SENTENCE STRUCTURE array 
	while((inputString[i] == ' ') && (inputString[i] != '\0')) i++;
	if (inputString[i] != '\0' ) {
		int n = 0; 
		//initialize word and char dynamic arrays for the FIRST ENTRIES 
		(*lineArray)[index].wordArray= (word *)calloc(1, sizeof(word)); 
		(*lineArray)[index].wordArray[0].actualWord = (char *) calloc (1, sizeof(char));
			
		//now we add the first character into the first word structure
		//making sure to update each of the structure variables along the way  
		(*lineArray)[index].wordArray[0].actualWord[0] = inputString[i];
		i++; n++;
		(*lineArray)[index].wordArray[0].charTotal = n; 
		(*lineArray)[index].wordTotal = 1;
		(*lineArray)[index].linePosition = lineNumber; 
		(*lineArray)[index].wordArray[0].position = 1;
			
		//adding the rest of the first word
		while((inputString[i]!=' ')&&(inputString[i] != '\0')) {
			(*lineArray)[index].wordArray[0].actualWord = (char *) realloc((*lineArray)[index].wordArray[0].actualWord, (n+1)*sizeof(char));
			(*lineArray)[index].wordArray[0].actualWord[n] = inputString[i];
			n++; i++; 
			(*lineArray)[index].wordArray[0].charTotal = n;
		}
		//need to add a null char to end of dynamic array to make it a valid string
		(*lineArray)[index].wordArray[0].actualWord = (char *) realloc((*lineArray)[index].wordArray[0].actualWord, (n+1)*sizeof(char));
		(*lineArray)[index].wordArray[0].actualWord[n] = '\0' ; 
		//once we exit the above loop, we are either at a null value or a space in the input string given to us 
		while(inputString[i] != '\0') {
			while(inputString[i] == ' ') i++; //this is just to find the next word, incase there are multiple spaces
				
			if (inputString[i] != '\0') {
				//this is a new word
				//updating variables and reallocating memory
				(*lineArray)[index].wordTotal ++; 
				(*lineArray)[index].wordArray = (word *) realloc ((*lineArray)[index].wordArray, ((*lineArray)[index].wordTotal)*sizeof(word));
					
				//starting to add characters to the new word structure
				int current = 0;
				(*lineArray)[index].wordArray[((*lineArray)[index].wordTotal)-1].charTotal = current; 
				(*lineArray)[index].wordArray[((*lineArray)[index].wordTotal)-1].actualWord = (char *) calloc(1, sizeof(char)); 
				(*lineArray)[index].wordArray[((*lineArray)[index].wordTotal)-1].actualWord[0]= inputString[i];
				current++; i++;
				
				//adding >1 letters using realloc until next space or null
				while((inputString[i] != ' ') && (inputString[i]!= '\0')) {
					current++;
(*lineArray)[index].wordArray[(*lineArray)[index].wordTotal-1].actualWord = (char *)realloc ((*lineArray)[index].wordArray[(*lineArray)[index].wordTotal-1].actualWord , current*sizeof(char));
					//please ignore that ridiculously long line :) 
					(*lineArray)[index].wordArray[((*lineArray)[index].wordTotal-1)].actualWord[current-1]=inputString[i];
					(*lineArray)[index].wordArray[((*lineArray)[index].wordTotal-1)].charTotal = current; 
					i++;
				}
				//Need to add null at the end of the actualWord array to make it a valid string
				(*lineArray)[index].wordArray[(*lineArray)[index].wordTotal-1].actualWord = (char *)realloc ((*lineArray)[index].wordArray[(*lineArray)[index].wordTotal-1].actualWord , (current+1)*sizeof(char));
				 (*lineArray)[index].wordArray[((*lineArray)[index].wordTotal-1)].actualWord[current] = '\0';
			}	
		}
	}	
}

//printing each word on its own line
//using structure variables to limit the indexes 
void printWords(line **lineArray, int lineMax) {
	for (int i =0;i< lineMax;i++) {
		int wordMax = (*lineArray)[i].wordTotal; 
		for(int j =0;j<wordMax;j++){
			int charMax = (*lineArray)[i].wordArray[j].charTotal;
			for(int k = 0; k<charMax; k++){
				printf("%c",((*lineArray)[i].wordArray[j].actualWord[k]));
				if(k==charMax-1) printf("\n");
			}
		}
	}
}

//to print each line on its own
//Using our structures variables as index markers 
void printLines (line **lineArray, int lineMax) {
	for(int i =0; i<lineMax; i++) {
		int wordMax= (*lineArray)[i].wordTotal;	
		for (int j = 0; j<wordMax;j++){
			int charMax = (*lineArray)[i].wordArray[j].charTotal;
			printf("%s ", ((*lineArray)[i].wordArray[j].actualWord));
			if(j==wordMax-1) printf("\n");
			
		}
	}
}
//search function to take input, and then look to find a match
void search(line **lineArray, int lineNumber, char input[]){
	//loop through the each word in each sentence, if we match with the input string then should print
	//since we have a null at the end of each actualWord array, string function should suffice
	//using structure's variables to find position and line numbers, and using them as indexes as well
	int found = 0;
       	if(input[0]!='\0'){	
	
		for(int i=0; i<lineNumber; i++){
		
			int wordMax = (*lineArray)[i].wordTotal;
		
			for(int j =0;j<wordMax;j++){
			
				char test[100];
				strcpy(test,(*lineArray)[i].wordArray[j].actualWord); 
				if (strcasecmp(test, input)==0) {
					found = 1;
					//add 1 to the indexes to get the position of the lines and words
					int linePos = i+1;
					int wordPos = j+1;
					printf("%s found in line %d, position %d \n", test, linePos, wordPos);
				}
			}
		}
		if (found==0)
			printf("%s was not found.\n", input);
	}	
}
