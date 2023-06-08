#include "enigma.h"
#include <stdio.h>
#include <string.h>
const char *ROTOR_CONSTANTS[] = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ", // Identity Rotor (index 0 - and useful for testing):
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
        "AJDKSIRUXBLHWTMCQGZNPYFVOE",
        "BDFHJLCPRTXVZNYEIWGAKMUSQO",
        "ESOVPZJAYQUIRHXLNFTGKDCMWB",
        "VZBRGITYUPSDNHLXAWMJQOFECK",
        "JPGVOUMFYQBENHZRDKASXLICTW",
        "NZJHGRCXMYSWBOUFAIVLPEKQDT",
        "FKQHTLXOCBJSPDZRAMEWNIUYGV",
};

// This method reads a character string from the keyboard and 
// stores the string in the parameter msg.
// Keyboard input will be entirely uppercase and spaces followed by 
// the enter key.  
// The string msg should contain only uppercase letters spaces and 
// terminated by the '\0' character
// Do not include the \n entered from the keyboard
void Get_Message(char msg[]){
  scanf("%[^\n]", msg);
  getchar();
  return;
}

// This function reads up to 4 characters from the keyboard
// These characters will be only digits 1 through 8. The user
// will press enter when finished entering the digits.
// The rotor string filled in by the function should only contain 
// the digits terminated by the '\0' character. Do not include
// the \n entered by the user. 
// The function returns the number of active rotors.
int Get_Which_Rotors(char which_rotors[]){
 scanf("%[^\n]", which_rotors);
 getchar();
 int i = 0; 
 while(which_rotors[i] != '\0')
	i++;
 return i;
} 

// This function reads an integer from the keyboard and returns it 
// This number represents the number of rotations to apply to the 
// encryption rotors.  The input will be between 0 and 25 inclusive
int Get_Rotations(){ 
    char rotations[2];
    scanf("%[^\n]", rotations);
    getchar();
    return atoi(rotations);
}

// This function copies the rotors indicated in the which_rotors string 
// into the encryption_rotors.  For example if which rotors contains the string 
// {'3', '1', '\0'} Then this function copies the third and first rotors into the 
// encryption rotors array in positions 0 and 1.  
// encryptions_rotors[0] = "BDFHJLCPRTXVZNYEIWGAKMUSQO"
// encryptions_rotors[1] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
void Set_Up_Rotors(char encryption_rotors[4][27], char which_rotors[5]){
	int i = 0;
	while(which_rotors[i] != '\0'){
		char num = which_rotors[i];
 		int rotorNum = num - '0'; //subtract 0 to get the value 0-9
		strcpy(encryption_rotors[i], ROTOR_CONSTANTS[rotorNum]);
//		printf("rotor in position %d: %s\n", i, encryption_rotors[i]);
		i++;
}

    return;
}

// This function rotates the characters in each of the active encryption rotors
// to the right by rotations.  For example if rotations is 3 encryption_rotors[0]
// contains "BDFHJLCPRTXVZNYEIWGAKMUSQO" then after rotation this row will contain
// SQOBDFHJLCPRTXVZNYEIWGAKMU.  Apply the same rotation to all for strings in 
// encryption_rotors
void Apply_Rotation(int rotations, char encryption_rotors[4][27]) {
for(int i = 0; i < rotations; i++){
	char last1 = encryption_rotors[0][25];
	char last2 = encryption_rotors[1][25];
	char last3 = encryption_rotors[2][25];
	char last4 = encryption_rotors[3][25];
	for(int j = 25; j > 0; j--){ //loop to shift array to the right by 1{
		encryption_rotors[0][j] = encryption_rotors[0][j-1];	
		encryption_rotors[1][j] = encryption_rotors[1][j-1];	
		encryption_rotors[2][j] = encryption_rotors[2][j-1];	
		encryption_rotors[3][j] = encryption_rotors[3][j-1];	
}
	encryption_rotors[0][0] = last1;
	encryption_rotors[1][0] = last2;
	encryption_rotors[2][0] = last3;
	encryption_rotors[3][0] = last4;
}

 return;
}

// This function takes a string msg and applys the enigma machine to encrypt the message
// The encrypted message is stored in the string encryped_msg 
// Do not change spaces, make sure your encryped_msg is a \0 terminated string
void Encrypt(char encryption_rotors[4][27], int num_active_rotors, char msg[], char encrypted_msg[]){
for(int i = 0; msg[i] != '\0'; i++){ //iterating through every letter in the message
	char currentCharacter = msg[i];
	if(currentCharacter == ' ')
		;
	else{
		for(int j = 0; j < num_active_rotors; j++){ //need to repeat the same proess for each encryption rotor
			int indexOfCharacter = currentCharacter - 'A'; //represents the index of the character in the identity rotor
			currentCharacter = encryption_rotors[j][indexOfCharacter];
		}
	}	
	encrypted_msg[i] = currentCharacter;
//	printf("encrypted_msg after %d iterations: %s\n", i, encrypted_msg);
}
//printf("Encrypted_msg: %s\n", encrypted_msg);   
return;
}


// This function takes a string msg and applys the enigma machine to decrypt the message
// The encrypted message is stored in the string encryped_msg and the decrypted_message 
// is returned as a call by reference variable
// remember the encryption rotors must be used in the reverse order to decrypt a message
// Do not change spaces, make sure your decrytped_msg is a \0 terminated string
void Decrypt(char encryption_rotors[4][27], int num_active_rotors, char encrypted_msg[], char decrypted_msg[]) {
int i = 0;
while(encrypted_msg[i] != '\0'){
	char currentCharacter = encrypted_msg[i];
	if(currentCharacter == ' ')
		;
	else{ //identical to encrypt, but we go backwards through the rotors, AND we go from rotor -> identity rotor instead of the other way around
		for(int j = num_active_rotors-1; j >= 0; j--){
		int indexOfCharacter = 0;
			while(encryption_rotors[j][indexOfCharacter] != currentCharacter)
				indexOfCharacter++;
			currentCharacter = 'A' + indexOfCharacter;
		}
	}
	decrypted_msg[i] = currentCharacter;
	i++;
}   
decrypted_msg[i] = '\0';
return;
}

