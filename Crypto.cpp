/*
Jenny Bloom
10.29.2015
HW 7 - Cryptography
Description: This program takes a file and encrypts it using a Caesae Cipher.
It also can decrypt the encrypted file.
Credits: http://www.cplusplus.com/reference/cctype/isalpha/ , help from friend
Collin Duncan, brainstorming input with classmates Darwin and Jeff.
*/

#include <iostream>
#include <fstream> //reads in files
#include <string> //fun with strings
#include <string.h> //fun with Linux and OSX compatability!
#include <stdio.h> //fun with Linux and OSX compatability! Hooray!
using namespace std;

//Protofunctions.
string readFile(char* file); //Protofxn: will have to convert char to string.
string encryptMessage(string message, int offset);
string decryptMessage(string message, int offset);
char encryptChar(char messageChar, int offset);
char decryptChar(char messageChar, int offset);
void writeToFile(char* bull, string shit); //this shit is void because it doesn't return shit.

int main(int argc, char* argv[]) //accepting CLA
{
  int offvar; /*offset variable set, unassigned, have to find a place to store
  the user input of the offset variable.*/
  sscanf(argv[2], "%d", &offvar); /*first parameter: %d = double, assigning
  value of char[2] using pointer to access direct memory address where offset
  is stored*/
  string input = readFile(argv[3]); /*declare string input, send to readfile,
  and call from CLA*/
  string output; //declare future output
  if (strcmp(argv[1], "-e") == 0) //if 1st arg = -e that returns true 0
  {
    output = encryptMessage(input, offvar); /*call encryptMessage fxn and
    storing into string output.*/
  }
  else /*else run shit if arg is not true, possibly include -d with else if,
  else is error handling.*/
  {
    output = decryptMessage(input, offvar);
  }

  cout << "INPUT: " << input << "\n";
  cout << "OUTPUT: " << output << "\n";

  writeToFile(argv[1], output);

  return 0;
}

/*this opens the file and uses the string within the file to work with.*/
string readFile(char* file) //fxn takes file assigned as char
{
 string var; /*getline taking info from fooFile, putting into new variable var.*/
 string str;
 ifstream fooFile;
 fooFile.open(file); //opens char file for reading
 while (getline(fooFile, var)) /* use string var to store text within file that
 I'm going to encrypt*/
 {
   str = var; /* reassign var line to str string, to avoid segmentation fault;
   assigning temp memory*/
 }
 fooFile.close(); //closes file after converted to str
 return str; //returning string back to main.
}

//Setting up encrypting message, applying the encryptChar
string encryptMessage(string message, int offset)
{
  string messageEncrypt = "";
  for(int i = 0; i < message.length(); i++) /*counting through the unencrypted
  message*/
  {
    messageEncrypt += encryptChar(message[i], offset); /*applying offset
    incrementally to message string*/
  }
  return messageEncrypt;
}

//Setting up decrypting message, applying decryptChar
string decryptMessage(string message, int offset)
{
  string messageDecrypt = "";
  for(int j = 0; j < message.length(); j++) /*counting through decrypted
  message*/
  {
    messageDecrypt += decryptChar(message[j], offset); /*applying offset
    incrementally to message strings*/
  }
  return messageDecrypt;
}

/* create algorithm chars after this. (4 steps, ASCII table  used, rewrite
algorithm 4 different times, modified slightly each time, mod algebra also.
MODULUO)*/
char encryptChar(char messageChar, int offset)
{
/*if some stuff is in the alphabet, do this thing, else if not in alphabet,
do this other thing. Use nifty isalpha() found in C++ standard library :D*/
  if(isalpha(messageChar))
  {
    if(isupper(messageChar))
    {
      messageChar = (((messageChar - 65)+offset) % 26) + 65; /*Tricksy. Begin at A,
      subtract A ASCII value of 65, then add offset, then take that value
      applied to modulo 26 because this is the size of the alphabet and you
      don't want to re-wrap. Then re-add 65 to bring you back to proper origin
      value location. */
    }
    else
    {
      messageChar = (((messageChar - 97)+offset) % 26) + 97;
    }
  }
  return messageChar;
}

/*Decrypt this shit.*/
char decryptChar(char messageChar, int offset)
{
/*if some stuff is in the alphabet, do this thing, else if not in alphabet,
do this other thing */
  if(isalpha(messageChar))
  {
    if(isupper(messageChar))
    {
      messageChar = (((messageChar - 65)-offset) % 26) + 65; /*Tricksy. Begin at A,
      subtract A ASCII value of 65, then subtract offset, then take that value
      applied to modulo 26 because this is the size of the alphabet and you
      don't want to re-wrap. Then re-add 65 to bring you back to proper origin
      value location. */
    }
    else
    {
      messageChar = (((messageChar - 97)-offset) % 26) + 97;
    }
  }
  return messageChar;
}

/*writeToFile output to file.*/
void writeToFile(char* bull, string shit)
{
  if (strcmp(bull, "-e") == 0) //bull is a char, compare using Booleans...
  {
    ofstream outputFile;
    outputFile.open("queerandin.enc");
    outputFile << shit;
    outputFile.close();
  }
  else
  {
    ofstream outputFile;
    outputFile.open("queerandout.dec");
    outputFile << shit;
    outputFile.close();
  }
}
