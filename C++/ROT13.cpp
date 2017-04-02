
/*
Author: Jordan E. Rosenberg
Date: 4/2/2016
Description: ROT13 ("rotate by 13 places", sometimes hyphenated ROT-13) is a simple letter substitution cipher that replaces a letter with the letter 13 letters after it in the alphabet. ROT13 is a special case of the Caesar cipher, developed in ancient Rome.
*/


#include <iostream>
using namespace std;

void convertStringtoROT13(char * pString);

int main() {
	
	// Pointer to an array of characters
	char strInput[100];
	
	// The input choice asking if the user should break the do-while loop
	char inputChoice;
	
	// do-while loop runs the loop at least once before checking to break!
	do {
		
    cout << "Please input a sentence (letters/spaces only): ";
    
    // Gets a line of characters from console and stores it into an character array of size 100
    cin.getline(strInput, 100);
    
    // void function that manipulates the entered character array (string) and converts to ROT13
    convertStringtoROT13(strInput);
    
    // Displays the ROT13 converted array of characters (C++11)
    cout<<strInput;
    
    cout<<"\nWould you like to try again? Input \'0\' to QUIT";
    cin>>inputChoice;
    
    // Without this, the cin.getline and cin statements will not work correctly!
    cin.ignore();
    
	} while(inputChoice != '0'); // Keep looping unless inputChoice is '0'
    
    return 0;
}

// Uses ASCII Table for Decimal to ASCII Char conversion
// http://www.asciitable.com/ for reference
void convertStringtoROT13(char * pString)
{
	int wrappingIndex; 
	
	// The # for any letter to be shifted
	int letterShift = 13; 
	int letterStartIndex;
	int difference;
	
	// for loop to loop through the array of characters
    for (int i = 0; i < 100; i++)
    {
    	
    	// If the current index of the char array is UpperCase
    	if (pString[i] >= 65 && pString[i] <= 90)
    	{
    		wrappingIndex = 91;
    		letterStartIndex = 65;
    	}
    	
    	// If the current index of the char array is LowerCase
    	else if (pString[i] >= 97 && pString[i] <= 122)
    	{
    		wrappingIndex = 123;
    		letterStartIndex = 97;
    	}
    	
    	// If the current index of the character array is not a letter or space, then exit the function
    	else if (pString[i] != ' ')
    		return;
    		
    	difference = pString[i] + letterShift - wrappingIndex;
		
		// casting is like smart converting objects from one data type to another   
		
		// recircle back to the A/a letter and add the difference
    	if (difference >= 0)
    	{
    		pString[i] = static_cast<char>(letterStartIndex + difference);
    	}
    	
    	else if (pString[i] != ' ')
    		pString[i] = static_cast<char>(pString[i] + letterShift);
    }	
	
}