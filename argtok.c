//
//	EE 4374 Lab # 2 Shell (Test Function)
//	Author: Hector Tejada
//

#include <stdio.h>
#include <stdlib.h>
#include "htejada_argtok.h"

char ** argtok(char * str, char delim){
	int i = 0;
	int PosOfString = 0;
	int PosOfChar = 0;
	int pos = 0;
	int numToken = 0;
	int tokenLength = 0;
	char prevchar = str[pos];

	//Checks to see if we are at a delim, we increment the number of tokens
	//We go until the end of the array
	for(pos = 1; ;pos++){
		if((str[pos] == delim || str[pos] == '\0') && prevchar != delim)
			numToken++;
		if(str[pos] == '\0')
			break;
		prevchar = str[pos];
	}

	//Allocating space for the array of the number of tokens
	char **PosArray = calloc(numToken+1, sizeof(char *));

	//This cehcks to see whether or not the current position is a char
	//if it is then we increment the tokenlength variable
	for(i = 0; ;i++){
		if(str[i] != delim && str[i] != '\0'){
			tokenLength++;
		}else if((str[i] == delim || str[i] == '\0') && tokenLength > 0){
			//This is when the current position is a delimiter. We allocate
			//space for the array of the characters of the string
			PosArray[PosOfString] = calloc(tokenLength+3, sizeof(char));
			int currentChar = i-tokenLength;
			int j = 0;
			for(;currentChar<i; currentChar++){
						PosArray[PosOfString][j] = str[currentChar];
						j++;
			}
			PosOfString++;
			tokenLength = 0;
		}

		if(str[i] == '\0')
			break;
	}
	return PosArray;

}

void print(char ** out){
  int pos;
  //printf("testing 1");
  for(pos = 0; out[pos] != 0; pos++){
    //printf("testing 2");
    printf("[%i]: %s\n", pos, out[pos]);
    free(out[pos]);
  }
}
