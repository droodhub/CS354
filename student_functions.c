/* Andrew McAvoy
 * apmcavoy
*/

/* This function takes a string as input and removes 
 * leading and trailing whitespace including spaces
 * tabs and newlines. It also removes multiple internal
 * spaces in a row. Arrays are passed by reference.
 */

#include <stdio.h>
#include <stdlib.h>
#include "student_functions.h"
#include <math.h>

int lengthOfArray(char data[]);

int lengthOfArray(char data[]){
int size = 0;
while(data[size] != '\0')
	size++;
return size;
}


void Clean_Whitespace(char str[]) {
   int replacementIndex = 0;
   int spaceNeeded = 0;
   char temp[1024];
   int i = 0;
   while(str[i] != '\0'){
	if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n'){
		if(spaceNeeded){
			temp[replacementIndex] = ' '; //insert a space
			++replacementIndex;
			temp[replacementIndex] = str[i]; //then insert char
			++replacementIndex;
			spaceNeeded = 0;
		}
		else{
			temp[replacementIndex] = str[i];
			++replacementIndex;
		}
		if(str[i+1] == ' ' || str[i+1] == '\t' || str[i+1] == '\n')
			spaceNeeded = 1; //the only time spaceNeeded can be set to 1 is if we 
			//just inserted a character, so this should eliminate unnecessary spaces entirely
	}
	i++;
   }
   temp[replacementIndex] = '\0';
   for(int i = 0; i < lengthOfArray(temp); i++)
	   str[i] = temp[i];
   str[lengthOfArray(temp)] = '\0';
    return;
}

/* This function takes a string and makes the first
 * letter of every word upper case and the rest of the
 * letters lower case
 */ 
void Fix_Case(char str[]) {
   int firstCharFound = 0;
   int i = 0;
   while(str[i] != '\0'){
	if(str[i] >= 'A' && str[i] <= 'Z'){ //found an uppercase letter
		if(!firstCharFound){ //this is the first letter in the string
			//already uppercase so do nothing
			firstCharFound = 1;
			i++;
			continue;
		}
		if(str[i-1] != ' ' || str[i-1] != '\t' || str[i-1] != '\n'){
		//previous character was not whitespace, letter should be lowercase
			str[i] = str[i] + 32;}
	
	}
	if(str[i] >= 'a' && str[i] <= 'z'){
		if(!firstCharFound){
			firstCharFound = 1;
			str[i] = str[i] - 32;
			i++;
			continue;
		}
		if(str[i-1] == ' ' || str[i-1] == '\t' || str[i-1] == '\n'){
			str[i] = str[i] - 32;
		}
	}
	i++;
   }
    return;
}
/* this function takes a string and returns the 
 * integer equivalent
 */
int String_To_Year(char str[]) {
    int year = (str[0]-48) * 1000 + (str[1]-48) * 100 + (str[2]-48) * 10 + (str[3]-48);
    return year;
}


/* this function takes the name of a 
 * director as a string and removes all but
 * the last name.  Example:
 * "Bucky Badger" -> "Badger"
 */
void Director_Last_Name(char str[]) {

int size = lengthOfArray(str);
int lengthOfName = 0;

for(int i = size-1; i >= 0; i--){
	if(str[i] == ' ') //iterate backwards until either a space is found
		break; //or we reach the start of the string
	lengthOfName++;
}

char temp[lengthOfName];
int charIndex = 0;
for(int index = (size - lengthOfName); index < size; index++, charIndex++)
	temp[charIndex] = str[index]; //copy last name over to temp string

for(int i = 0; i < lengthOfName; i++)
	str[i] = temp[i]; //rewrite original string with just the last name

str[lengthOfName] = '\0'; //place null terminator after the last name is copied over

return;
}

/* this function takes the a string and returns
 * the floating point equivalent
 */
float String_To_Rating(char str[]) {
int length = lengthOfArray(str);
float rating = 0;
if(length == 1){
	rating = (float)(str[0]-48);
}
else if(length == 3){
	rating = (float)(str[0]-48) + (float)(str[2]-48) * .1;
}
else if(length == 4){
	rating = (float)(str[0]-48)*10 + (float)(str[1]-48) + (float)(str[3]-48) * .1;
}
    return rating;
}


/* this function takes a string representing
 * the revenue of a movie and returns the decimal
 * equivlaent. The suffix M or m represents millions,
 * K or k represents thousands.
* example: "123M" -> 123000000 
*/
long long String_To_Dollars(char str[])  {
    int size = lengthOfArray(str);
    long long dollars = 0;
    char newVal[1000]; 
    
    if(str[size-1] == 'k' || str[size-1] == 'K'){//check for suffix
	for(int i = 0; i < size-1; i++) //copy numbers over to new data structure
		newVal[i] = str[i];
	newVal[size-1] = '\0';
	dollars = atoll(newVal);//get value of numbers

        dollars = dollars * 1000;//multiply by suffix
    }
    else if(str[size-1] == 'm' || str[size-1] == 'M'){	
	for(int i = 0; i < size-1; i++)
		newVal[i] = str[i];
	newVal[size-1] = '\0';

	dollars = atoll(newVal);
	 
     	dollars = dollars * 1000000;
    }
    else
	    dollars = atoll(str);

    return dollars;
}


/* This function takes the array of strings representing 
 * the csv movie data and divides it into the individual
 * components for each movie.
 * Use the above helper functions.
 */
void Split(char csv[10][1024], int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
    	for(int csvRow = 0; csvRow < num_movies; csvRow++){ //looping through each line of the csv array
		int bufferRow = 0;
		int bufferIndex = 0;
		char buffer[6][1024];
		for(int j = 0; csv[csvRow][j] != '\0'; j++){ //looping through each index at the given line
			if(csv[csvRow][j] == ','){
				buffer[bufferRow][bufferIndex] = '\0'; //add null terminator, move to next row
				bufferIndex = 0;
				bufferRow++;
			}
			else{
				buffer[bufferRow][bufferIndex] = csv[csvRow][j];//add char to buffer + increment
				bufferIndex++;
			}
		}
		buffer[bufferRow][bufferIndex] = '\0';

		for(int k = 0; k <= bufferRow; k++){
			Clean_Whitespace(buffer[k]); //clean up all elements
			Fix_Case(buffer[k]); 
		}
		
		int f = 0;
		while(buffer[0][f] != '\0'){ //copy the title over
			titles[csvRow][f] = buffer[0][f];
			f++;
		}
		titles[csvRow][f] = '\0';
		f = 0;

		int year = String_To_Year(buffer[1]);
		years[csvRow] = year;

		Director_Last_Name(buffer[3]);
		while(buffer[3][f] != '\0'){ //copy director's last name over
			directors[csvRow][f] = buffer[3][f];
			f++;
		}
		directors[csvRow][f] = '\0';
		f = 0;

		float rating = String_To_Rating(buffer[4]);
		ratings[csvRow] = rating;

		long long profits = String_To_Dollars(buffer[5]);
		dollars[csvRow] = profits;
	}
	return;
}



/* This function prints a well formatted table of
 * the movie data 
 * Row 1: Header - use name and field width as below
 * Column 1: Id, field width = 3, left justified
 * Column 2: Title, field width = lenth of longest movie + 2 or 7 which ever is larger, left justified, first letter of each word upper case, remaining letters lower case, one space between words
 * Column 3: Year, field with = 6, left justified
 * Column 4: Director, field width = length of longest director last name + 2 or 10 (which ever is longer), left justified, only last name, first letter upper case, remaining letters lower case
 * column 5: Rating, field width = 6, precision 1 decimal place (e.g. 8.9, or 10.0), right justified
 * column 6: Revenue, field width = 11, right justified
 */
void Print_Table(int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
    // do your work here
    int nameLength = 10;
    int titleLength = 7;
    for(int i = 0; i < num_movies; i++){ //determine the width of the director and title fields
	int movieLength = lengthOfArray(titles[i]) + 2;
	int directorLength = lengthOfArray(directors[i]) + 2;
	if(movieLength > titleLength)
		titleLength = movieLength;
	if(directorLength > nameLength)
		nameLength = directorLength;
    }

    printf("%-3s","Id");
    printf( "%-*s", titleLength, "Title");
    printf( "%-6s", "Year");
    printf( "%-*s", nameLength, "Director");
    printf( "%6s", "Rating");
    printf("%11s\n", "Revenue");
    for(int j = 0; j < num_movies; j++){
	printf("%-3d", j+1);
   	printf("%-*s", titleLength, titles[j]);
        printf("%-6d", years[j]);
        printf("%-*s", nameLength, directors[j]);
        printf("%6.1f", ratings[j]);
        printf("%11lld\n", dollars[j]);}

    return;
}


