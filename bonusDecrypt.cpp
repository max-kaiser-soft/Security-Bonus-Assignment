//MAX KAISER

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <bitset>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>

using namespace std;


char* readFile(const char* file){ //read file to get letter
    
    ifstream inputFile(file);

    if (!inputFile.is_open()) {
        cerr << "Error opening the file!" << endl;}

    stringstream buffer; //read file into stringstream buffer

    buffer << inputFile.rdbuf();

    string fileContent = buffer.str(); //convert buffer into a single string

    //cout << fileContent << endl; //print file content

    inputFile.close();

    
    char* output = new char[fileContent.length() + 1]; //allocate memory for c-string
    output[fileContent.length()] = '\0'; //null terminator

    for (int c = 0; c < fileContent.length(); c++){
        output[c] = fileContent[c];}

    return output;
}


int keyDecimalMaker(char* key){ //converts key binary to decimal
        int output = 0;
    
    for (int c = 7; c >= 0; c--){
        int keyVal = 0; 

        if(key[c] == '1'){
            keyVal = 1;}

        //cout<<keyVal<<"*"<<pow(2, (7 - c))<<" ";
        //cout<<keyVal * pow(2, (7 - c))<< "   ";

        output += keyVal * pow(2, (7 - c));}

    return output;
}


char* messageGetter(char* input, int keyDecimal) { //method to get the message
   
    int length = strlen(input);
    char* output = new char[length]; //allocate memory for c-string
    output[length] = '\0'; //null terminator


    for (int c = 0; c < length; c++){ //loop to go through full message
        
        char inputChar = input[c]; //grab character
        int inputCharASCII = int(inputChar); //convert character to ASCII

        int outputCharACSII = inputCharASCII ^ keyDecimal; //XOR with key
        
        char outputChar = static_cast<char>(outputCharACSII); //convert result to character

        output[c] = outputChar; //add to output

    }
        //char toAdd[2] = "0";
        //strncat(output, toAdd, 1); //add num to output    
    
    return output;
}


int printer(char* content, const char* file){ //prints to file

    ofstream outfile(file); //create and open text file

    if (!outfile.is_open()) {// check if file is open
        cerr << "Failed to open file for writing.\n";
        return 1;
    }

    outfile << content; // write to  file

    outfile.close(); //close file

    return 0;
}


int main(){ //main
    char* input = readFile("secret.txt"); //read file to get letter
    char* key = readFile("key.txt"); //read file to get key


    int keyDecimal = keyDecimalMaker(key); //key as decimal number

//char* messageGetter(char* input, int keyDecimal) { //method to get the message

    char* message = messageGetter(input, keyDecimal);

    printer(message, "message.txt"); //printers

    //cout<<input<<endl;
    //cout<<key<<endl;
    //cout<<output<<endl;
}