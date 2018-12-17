#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

const int pastAmount = 100; // The maximum amount of time you can go back with PAST

/*
  Notes:
________________________________________________________________________________________________________________________________________________________________________________________________________  
  Token values:
     Nothing       : 0
     Numbers       : -1 * (value + 1). I.E. 0 = -1, 1 = -2, 12 = -13, 117 = -118, etc.
     Symbols       : @ = 200 + = 201 - = 202 & = 100 . = 101
     Numerical Ops : RAND = 300 ADDN = 301 SUBN = 302 MULN = 303 DIV = 304 MODN = 305 PAST = 306 LOCN = 307
     IFs           : EQ = 400 NQ = 401 GT = 402 GE = 403 LT = 404 LE = 405
  
     Special       : 10 is the beginning of the array, and is ignored. 0 is a blank value. 7 is whitespace.
  
  Miscellanea:
     The old base 64 single-digit system has been overturned in favor of a base ten system. All whole numbers are valid (floating point and negative numbers may come in a revision of the languge)
     The reason no 1xx tokens are used is they originally referred to base 64 numbers, and I'm lazy and haven't changed the token scheme. (And probably won't) (& was added after this was typed)
     PAST support is coming, probably in AE4
     PAST in 2D will require a bit of special code, as it will use 3 values (time, x coordinate, y coordinate)
     TSNI will use the tokens values desribed above, because I'm lazy :P (I'm not sure why this was listed under "Things to come in AE4")
  AE5 new features:
     
     Infinite dimensions!
     Support for EQ, NQ, GT, LT, GE and LE
     Removal of comments (sorry future me)
  
  License:
      
      DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
      Version 2, December 2004
      Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
      Everyone is permitted to copy and distribute verbatim or modified
      copies of this license document, and changing it is allowed as long
      as the name is changed.
      DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
      TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
      0. You just DO WHAT THE FUCK YOU WANT TO.        
________________________________________________________________________________________________________________________________________________________________________________________________________                   
*/

int AEND (int *tokens, int tokenAmount, int *cell, int *cellSizes, int dimensions, int *cellPointerCoors, int *pastCell)  {
  int i;
  int i2;
  int i3;
  int i4;
  int i5;
  int currMultiOp;
  int currLoc;
  int *valS = malloc(sizeof(int) * (dimensions + 1));
  if (tokenAmount == 1 && *(tokens + 1) == 100) {
    return -1;
  }
  if (tokenAmount == 1 && *(tokens + 1) == 1738) {
    printf("This is a dead meme\n");
    return 609;
  }
  for (;;)  {
    for (i = tokenAmount; *(tokens + i) < 300 && *(tokens + i) != 10; i--) {
    }
    currMultiOp = *(tokens + i);
    currLoc = i;
    if (currMultiOp != 10)  {
      for (i2 = 0; i2 != ((currMultiOp == 306) ? dimensions + 1 : ((currMultiOp == 307) ? (2 * dimensions) : 2)); i2++)  {
	for (i = currLoc; *(tokens + i) >= 300 || *(tokens + i) == 0; i++);
        if (*(tokens + i) < 0)  {
	  *(valS + i2) = (*(tokens + i) * -1) - 1;
	}
	else {
	  *(valS + i2) = *(tokens + i);
	}
	*(tokens + i) = 0;
      }
      if (currMultiOp == 300)  {
 	*(tokens + currLoc) = (((rand() % (*(valS + 1))) + *valS) + 1) * -1;
      }
      if (currMultiOp == 301)  {
 	*(tokens + currLoc) = ((*valS + *(valS + 1)) + 1)  * -1;
      }
      if (currMultiOp == 302)  {
 	*(tokens + currLoc) = ((*valS - *(valS + 1)) + 1) * -1;
 	if (*(tokens + currLoc) > 0)  {
 	  *(tokens + currLoc) = 0;
 	}
      }
      if (currMultiOp == 303)  {
 	*(tokens + currLoc) = ((*valS * *(valS + 1)) + 1) * -1;
      }
      if (currMultiOp == 304)  {
 	*(tokens + currLoc) = ((*valS / *(valS + 1)) + 1) * -1;
      }
      if (currMultiOp == 305)  {
 	*(tokens + currLoc) = ((*valS % *(valS + 1)) + 1) * -1;
      }
      if (currMultiOp == 306)  {
	i3 = 0;
	for (i2 = 0; i2 != dimensions; i2++)  {
	  i4 = 1;
	  for (i5 = 0; i5 <= i2 - 1; i5++)  {
	    i4 *= *(cellSizes + i5);
	  }
	  i3 += *(valS + i2) * i4;
	}
	i3 += *(valS + dimensions) * i4 * pastAmount;
	*(tokens + currLoc) = (*(pastCell + i3) + 1) * -1;
      }
      if (currMultiOp == 307)  {
	i3 = 0;
	for (i2 = 0; i2 != dimensions; i2++)  {
	  if (*(valS + (2 * i2)) == 200) {
	    while (*(valS + (2 * i2) + 1) > *(cellSizes + i2))  {
	      *(valS + (2 * i2) + 1) -= *(cellSizes + i2);
	    }
	    i4 = 1;
	    for (i5 = 0; i5 < i2; i5++)  {
	      i4 *= *(cellSizes + i5);
	    }
	    i3 += *(valS + (2 * i2 + 1)) * i4;
	  }
	  if (*(valS + (2 * i2)) == 201) {
	    while (*(cellPointerCoors + i2) + *(valS + (2 * i2) + 1) > *(cellSizes + i2))  {
	      *(valS + (2 * i2) + 1) -= *(cellSizes + i2);
	    }
	    i4 = 1;
	    for (i5 = 0; i5 < i2; i5++)  {
	      i4 *= *(cellSizes + i5);
	    }
	    i3 += (*(cellPointerCoors + i2) + *(valS + (2 * i2 + 1))) * i4;
	  }
	  if (*(valS + (2 * i2)) == 202) {
	    while (*(cellPointerCoors + i2) - *(valS + (2 * i2) + 1) > *(cellSizes + i2))  {
	      *(valS + (2 * i2) + 1) -= *(cellSizes + i2);
	    }
	    i4 = 1;
	    for (i5 = 0; i5 < i2; i5++)  {
	      i4 *= *(cellSizes + i5);
	    }
	    i3 += (*(cellPointerCoors + i2) - *(valS + (2 * i2 + 1))) * i4;
	  }
	}
	*(tokens + currLoc) = (*(cell + i3) + 1) * -1;
      }
      if (currMultiOp == 400)  {
	if (*valS == *(valS + 1))  {
	  *(tokens + currLoc) = -2;
	}
	else {
	  *(tokens + currLoc) = -1;
	}
      }
      if (currMultiOp == 401)  {
	if (*valS != *(valS + 1))  {
	  *(tokens + currLoc) = -2;
	}
	else {
	  *(tokens + currLoc) = -1;
	}
      }
      if (currMultiOp == 402)  {
	if (*valS > *(valS + 1))  {
	  *(tokens + currLoc) = -2;
	}
	else {
	  *(tokens + currLoc) = -1;
	}
      }
      if (currMultiOp == 403)  {
	if (*valS >= *(valS + 1))  {
	  *(tokens + currLoc) = -2;
	}
	else {
	  *(tokens + currLoc) = -1;
	}
      }
      if (currMultiOp == 404)  {
	if (*valS < *(valS + 1))  {
	  *(tokens + currLoc) = -2;
	}
	else {
	  *(tokens + currLoc) = -1;
	}
      }
      if (currMultiOp == 405)  {
	if (*valS <= *(valS + 1))  {
	  *(tokens + currLoc) = -2;
	}
	else {
	  *(tokens + currLoc) = -1;
	}
      }
    }
    else {
      return (*(tokens + 1) * -1) -1;
    }
  }
}

int main (void)  {
  srand(time(0)); // Seed the Random Number Generator with the current time

  int i; // General Purpose Counter
  int i2; // General Purpose Counter
  int i3; // General Purpose Counter

  int step = 0;

  int input = 10; // General purpose input variable, used only in TSXX interperters

  int D = 1; // Dimensions (infinite)

  int it;
  
  int *cellSizes = calloc(D, sizeof(int)); // The number of numbers used to describe the length / area / volume etc.
  
  it = 1;
  
  for (i = 0; i != D; i++)  { // Figure out how big the cell array needs to be
    it *= *(cellSizes + i);
  }

  int *cell = calloc(i2, sizeof(int)); // Pointer to the cells

  int *cellPointerCoors = calloc(D, sizeof(int)); // Stores the cell pointer coordinates

  int *pastCell = calloc(i2 * pastAmount, sizeof(int));

  int tokenAmount; // Stores the number of tokens in the list
  int tracker;
  int executed;

  int *tokens;

  int argAmount;

  int *arguments;

  int argStop;

  int currCommand;

  char inptStr [1000000];

  int inStrPtr;

  int init = 1; // Are we in initialization mode?

  int c;

  for (;;)  {
    argStop = 0;
    arguments = malloc(sizeof(int));
    inStrPtr = 4;
    printf("S>>> ");
    fgets(inptStr, 1000000, stdin);
    if (init == 1)  {
      if (*(inptStr) == 'D' && *(inptStr + 1) == 'I' && *(inptStr + 2) == 'M' && *(inptStr + 3) == 'N')  {
	currCommand = 500;
      }
      else if (*(inptStr) == 'S' && *(inptStr + 1) == 'I' && *(inptStr + 2) == 'Z' && *(inptStr + 3) == 'E')  {
	currCommand = 501;
      }
      else if (*(inptStr) == 'S' && *(inptStr + 1) == 'E' && *(inptStr + 2) == 'T' && *(inptStr + 3) == 'P')  {
	currCommand = 502;
      }
      else if (*(inptStr) == '~' && *(inptStr + 1) == 'U' && *(inptStr + 2) == 'P' && *(inptStr + 3) == 'T')  {
	currCommand = 503;
      }
      else if (*(inptStr) == '~' && *(inptStr + 1) == 'U' && *(inptStr + 2) == 'P' && *(inptStr + 3) == 'T')  {
	currCommand = 504;
      }
      else if (*(inptStr) == 'B' && *(inptStr + 1) == 'E' && *(inptStr + 2) == 'G' && *(inptStr + 3) == 'N')  {
	currCommand = 505;
      }
      else  {
	printf("ERR: ILLEGAL COMMAND \"%c%c%c%c\"\n", *(inptStr), *(inptStr + 1), *(inptStr + 2), *(inptStr + 3));
	return -1;
      }
    }
    else  {
      if (*(inptStr) == 'O' && *(inptStr + 1) == 'U' && *(inptStr + 2) == 'P' && *(inptStr + 3) == 'T')  {
	currCommand = 600;
      }
      else if (*(inptStr) == 'C' && *(inptStr + 1) == 'R' && *(inptStr + 2) == 'P' && *(inptStr + 3) == 'T')  {
	currCommand = 601;
      }
      else if (*(inptStr) == 'I' && *(inptStr + 1) == 'N' && *(inptStr + 2) == 'P' && *(inptStr + 3) == 'T')  {
	currCommand = 602;
      }
      else if (*(inptStr) == '~' && *(inptStr + 1) == 'U' && *(inptStr + 2) == 'P' && *(inptStr + 3) == 'T')  {
	currCommand = 603;
      }
      else if (*(inptStr) == '~' && *(inptStr + 1) == 'U' && *(inptStr + 2) == 'P' && *(inptStr + 3) == 'T')  {
	currCommand = 604;
      }
      else if (*(inptStr) == '~' && *(inptStr + 1) == 'U' && *(inptStr + 2) == 'P' && *(inptStr + 3) == 'T')  {
	currCommand = 605;
      }
      else if (*(inptStr) == '~' && *(inptStr + 1) == 'U' && *(inptStr + 2) == 'P' && *(inptStr + 3) == 'T')  {
	currCommand = 606;
      }
      else if (*(inptStr) == '~' && *(inptStr + 1) == 'U' && *(inptStr + 2) == 'P' && *(inptStr + 3) == 'T')  {
	currCommand = 607;
      }
      else if (*(inptStr) == '~' && *(inptStr + 1) == 'U' && *(inptStr + 2) == 'P' && *(inptStr + 3) == 'T')  {
	currCommand = 608;
      }
      else if (*(inptStr) == '~' && *(inptStr + 1) == 'U' && *(inptStr + 2) == 'P' && *(inptStr + 3) == 'T')  {
	currCommand = 609;
      }
      else if (*(inptStr) == 'E' && *(inptStr + 1) == 'X' && *(inptStr + 2) == 'I' && *(inptStr + 3) == 'T')  {
	currCommand = 610;
      }
      else  {
	printf("ERR: ILLEGAL COMMAND \"%c%c%c%c\"\n", *(inptStr), *(inptStr + 1), *(inptStr + 2), *(inptStr + 3));
	return -1;
      }
    }
    for (argAmount = 0; argStop != 1; argAmount++)  {
      input = 10;
      tracker = 0;
      executed = 0;
      tokens = malloc(sizeof(int)); // Pointer to the list of tokens
      for (tokenAmount = 0; tracker != 0 || executed == 0; tokenAmount++)  { // Loop to fill tokens
	executed = 1;
	if (input != 7)  {
	  *(tokens + tokenAmount) = input; // Put the input into tokens
	  tokens = realloc(tokens, (sizeof(int) * tokenAmount + 1)); // Increase the size of tokens to fit the amount of tokens
	}
	if ((input < 0 || input == 100 || (input >= 200 && input < 203)) && input != 7)  {
	  tracker--;
	}
	else if (input != 7)  {
	  tracker += ((input == 306) ? D + 1 : ((input == 307) ? (2 * D) : 2)) - 1;
	}
	if (tracker != 0)  {
	  if (isdigit(*(inptStr + inStrPtr)))  { // Gets numbers
	    input = 0;
	    while (*(inptStr + inStrPtr) != 'i')  {
	      input *= 10;
	      input += *(inptStr + inStrPtr) - '0';
	      inStrPtr++;
	    }
	    input = (-1 * input) - 1;
	    inStrPtr++;
	  }
	  else if (isalpha(*(inptStr + inStrPtr)))  { //Gets multiOps
	    if (*(inptStr + inStrPtr) == 'E' && *(inptStr + inStrPtr + 1) == 'Q')  {
	      input = 400;
	      inStrPtr += 2;
	    }
	    else if (*(inptStr + inStrPtr) == 'N' && *(inptStr + inStrPtr + 1) == 'Q')  {
	      input = 401;
	      inStrPtr += 2;
	    }
	    else if (*(inptStr + inStrPtr) == 'G' && *(inptStr + inStrPtr + 1) == 'T')  {
	      input = 402;
	      inStrPtr += 2;
	    }
	    else if (*(inptStr + inStrPtr) == 'G' && *(inptStr + inStrPtr + 1) == 'E')  {
	      input = 403;
	      inStrPtr += 2;
	    }
	    else if (*(inptStr + inStrPtr) == 'L' && *(inptStr + inStrPtr + 1) == 'T')  {
	      input = 404;
	      inStrPtr += 2;
	    }
	    else if (*(inptStr + inStrPtr) == 'L' && *(inptStr + inStrPtr + 1) == 'E')  {
	      input = 405;
	      inStrPtr += 2;
	    }
	    else if (*(inptStr + inStrPtr) == 'R' && *(inptStr + inStrPtr + 1) == 'A' && *(inptStr + inStrPtr + 2) == 'N' && *(inptStr + inStrPtr + 3) == 'D')  {
	      input = 300;
	      inStrPtr += 4;
	    }
	    else if (*(inptStr + inStrPtr) == 'A' && *(inptStr + inStrPtr + 1) == 'D' && *(inptStr + inStrPtr + 2) == 'D' && *(inptStr + inStrPtr + 3) == 'N')  {
	      input = 301;
	      inStrPtr += 4;
	    }
	    else if (*(inptStr + inStrPtr) == 'S' && *(inptStr + inStrPtr + 1) == 'U' && *(inptStr + inStrPtr + 2) == 'B' && *(inptStr + inStrPtr + 3) == 'N')  {
	      input = 302;
	      inStrPtr += 4;
	    }
	    else if (*(inptStr + inStrPtr) == 'M' && *(inptStr + inStrPtr + 1) == 'U' && *(inptStr + inStrPtr + 2) == 'L' && *(inptStr + inStrPtr + 3) == 'N')  {
	      input = 303;
	      inStrPtr += 4;
	    }
	    else if (*(inptStr + inStrPtr) == 'D' && *(inptStr + inStrPtr + 1) == 'I' && *(inptStr + inStrPtr + 2) == 'V' && *(inptStr + inStrPtr + 3) == 'N')  {
	      input = 304;
	      inStrPtr += 4;
	    }
	    else if (*(inptStr + inStrPtr) == 'M' && *(inptStr + inStrPtr + 1) == 'O' && *(inptStr + inStrPtr + 2) == 'D' && *(inptStr + inStrPtr + 3) == 'N')  {
	      input = 305;
	      inStrPtr += 4;
	    }
	    else if (*(inptStr + inStrPtr) == 'P' && *(inptStr + inStrPtr + 1) == 'A' && *(inptStr + inStrPtr + 2) == 'S' && *(inptStr + inStrPtr + 3) == 'T')  {
	      input = 306;
	      inStrPtr += 4;
	    }
	    else if (*(inptStr + inStrPtr) == 'L' && *(inptStr + inStrPtr + 1) == 'O' && *(inptStr + inStrPtr + 2) == 'C' && *(inptStr + inStrPtr + 3) == 'N')  {
	      input = 307;
	      inStrPtr += 4;
	    }
	    else {
	      printf("ERR: ILLEGAL CHARACTER '%c' AT %i\n", *(inptStr + inStrPtr), inStrPtr);
	      return -1;
	    }
	  }
	  else {
	    if (*(inptStr + inStrPtr) == ' ' || *(inptStr + inStrPtr) == '\t' || *(inptStr + inStrPtr) == '\n')  {
	      input = 7;
	      tokenAmount--;
	      inStrPtr++;
	    }
	    else if (*(inptStr + inStrPtr) == '&')  {
	      input = 100;
	      inStrPtr++;
	    }
	    else if (*(inptStr + inStrPtr) == '.')  {
	      input = 101;
	      inStrPtr++;
	    }
	    else if (*(inptStr + inStrPtr) == '@')  {
	      input = 200;
	      inStrPtr++;
	    }
	    else if (*(inptStr + inStrPtr) == '+')  {
	      input = 201;
	      inStrPtr++;
	    }
	    else if (*(inptStr + inStrPtr) == '-')  {
	      input = 202;
	      inStrPtr++;
	    }
	    else {
	      printf("ERR: ILLEGAL CHARACTER '%c' AT %i\n", *(inptStr + inStrPtr), inStrPtr);
	      return -1;
	    }
	  }
	  if (tokenAmount == 0 && input == 101)  {
	    argStop = 1;
	    break;
	  }
	}
      }
      if (argStop == 0)  {
	tokenAmount--;
	*(arguments + argAmount) = AEND(tokens, tokenAmount, cell, cellSizes, D, cellPointerCoors, pastCell);
	arguments = realloc(arguments, sizeof(int) * (argAmount + 1));
	free(tokens);
      }
    }
    // Execute commands:
    argAmount -= 2;
    if (init == 1)  {
      if (currCommand == 500 && step == 0)  { // DIMN
	if (*arguments <= 0)  {
	  printf("ERROR 001: DIMENSIONS LESS THAN 1\n");
	  return -1;
	}
	step = 1;
	free(cellSizes);
	cellSizes = calloc(D, sizeof(int));
      }
      if (currCommand == 501 && step == 1)  { // SIZE
	for (i = 0; i != D; i++)  {
	  input = *(i + arguments);
	  if (input <= 0)  {
	    printf("ERROR 003: CELL DIMENSION LESS THAN 1");
	    return -1;
	  }
	  *(cellSizes + i) = input;
	}
	it = 1;
  
	for (i = 0; i != D; i++)  { // Figure out how big the cell array needs to be
	  it *= *(cellSizes + i);
	}
	free(cell);
	cell = calloc(i2, sizeof(int)); // Pointer to the cells
	free(cellPointerCoors);
	cellPointerCoors = calloc(D, sizeof(int)); // Stores the cell pointer coordinates
	free(pastCell);
	pastCell = calloc(i2 * pastAmount, sizeof(int));
      }
      if (currCommand == 502)  { // SETP
	for (i = 0; i != it; i++)  {
	  *(cell + i) = *(arguments + i);
	}
      }
      if (currCommand == 505)  {
	init = 0;
      }
    }
    else if (currCommand == 600)  { // OUPT
      if (argAmount == 0 && *arguments == -1)  { // INFINITE
	i = 0;
	for (i3 = 1; i != D; i++)  {
	  i3 *= *(cellSizes + i);
	}
	for (i2 = 0; i2 != i3; i2++)  {
	  printf("%d ", *(cell + i2));
	}
      }
      else  {
        for (i2 = 0; i2 != argAmount + 1; i2++)  {
	  printf("%d ", *(cell + *(i2 + arguments)));
	}
      }
      printf("\n");
    }
    else if (currCommand == 601)  { // CRPT
      if (argAmount == 0 && *arguments == -1)  { // INFINITE
	i = 0;
	for (i3 = 1; i != D; i++)  {
	  i3 *= *(cellSizes + i);
	}
	for (i2 = 0; i2 != i3; i2++)  {
	  printf("%c ", *(cell + i2));
	}
      }
      else  {
        for (i2 = 0; i2 != argAmount + 1; i2++)  {
	  printf("%c ", *(cell + *(i2 + arguments)));
	}
      }
      printf("\n");
    }
    else if (currCommand == 602)  { // INPT
      if (argAmount == 0)  { // Correct amount of arguments
	scanf("%d", (cell + *arguments));
	while ((c = getchar()) != '\n' && c != EOF);
      }
      else  {
	printf("ERR 004: IMPROPER ARGUMENT AMOUNT (%i)\n", argAmount);
	return -1;
      }
    }
    else if (currCommand == 610)  { // EXIT
      if (argAmount == -1)  { // Correct amount of arguments
        return 0;
      }
      else  {
	printf("ERR 005: EXIT DOES NOT SUPPORT ARGUEMNTS\n");
	return -1;
      }
    }
    free(arguments);
  }
}