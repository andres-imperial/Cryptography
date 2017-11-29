#include <string>
#include <cstring>
#include <cctype>
#include <ctype.h>
#include <fstream>
#include "CipherInterface.h"
#include "Playfair.h"
#include "RowTransposition.h"
#include "RailFence.h"
#include "Vigenere.h"
#include "Ceasar.h"
#include "Hill.h"

using namespace std;

int main(int argc, char** argv)
{
    // Variables
    CipherInterface* cipher = NULL;
    ifstream inputFile;
    ofstream outputFile;
    string outputText;
    string inputText;
    string key(argv[2]);

    // Check for Proper Amount of arguments
    if(argc != 6){
        // ERROR
        fprintf(stderr, "Error, incorrect number of arguments provided, please follow format.\n"
                "./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUTFILE> <OUTPUTFILE>\n");
            exit(-1);
    }

    // Get input text from input file provided.
    inputFile.open(argv[4]);
    if(!inputFile.is_open()){ // File had an error
        fprintf(stderr, "Error was not able to open input file.");
        exit(-1);
    }
    else{ // File is looking good
        getline(inputFile, inputText);
        //Check to see if there are any characters
        if(inputText.length() < 1){
            fprintf(stderr, "Error there is nothing to ENC/DEC in %s\n"
                    "Please make sure there is no spaces/newlines/punctuation in file\n",
                    argv[4]);
            exit(-1);
        }
    }

    // Open output file and error check
    outputFile.open(argv[5]);
    if(!outputFile.is_open()){
        fprintf(stderr, "Error was not able to open output file.");
        exit(-1);
    }

    // Check for specified cipher to use.
    if(argv[1] == string("PLF")){
        /* Create an instance of the Playfair cipher */	
        cipher = new Playfair();
        // Clean your input text.
        inputText = scrubText(inputText, false);
        /* Set the encryption key */
        key = scrubText(key, true);
    }
    else if(argv[1] == string("RTS")){
        /* Create an instance of the Row Transpostion cipher */	
        cipher = new RowTransposition();
        // Format your input text
        inputText = evenOutText(key.length(), inputText);
    }
    else if(argv[1] == string("RFC")){
        /* Create an instance of the Rail Fence Cipher */	
        cipher = new RailFence();
        // Format your input text
        inputText = evenOutText(atoi(key.c_str()), inputText);
    }
    else if(argv[1] == string("VIG")){
        /* Create an instance of the Row Transpostion cipher */	
        cipher = new Vigenere();
        // Format your input text
        inputText = lowerString(inputText);
        // Format your key
        key = lowerString(key);
    }
    else if(argv[1] == string("CES")){
        /* Create an instance of the Row Transpostion cipher */	
        cipher = new Ceasar();
        // Format your input text
        inputText = lowerString(inputText);
    }
    else if(argv[1] == string("HIL")){
        /* Create an instance of the Row Transpostion cipher */	
        cipher = new Hill();
        // Lowercase the string and even it out according to 3
        inputText = evenOutText(3, lowerString(inputText));
    }
    else{
        // Error invalid input
        fprintf(stderr, "Error No matches for specified cipher --%s--\n"
               "Please choose from the following:\n"
               "PLF = Playfiar\n"
               "RTS = Row Transpostion\n"
               "RFC = Railfence\n"
               "VIG = Vigenere\n"
               "CES = Caesar\n"
               "HIL = Hill\n",
               argv[1]);
        exit(-1);
    } 

    /* Error checks */
    if(!cipher)
        {
            fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
        __FILE__, __FUNCTION__, __LINE__);
        exit(-1);
    }

    // Set cipher key
    if(!cipher->setKey(key)){
        fprintf(stderr,"Error in setting key, exiting. . . \n");
        exit(-1);
    }

    if(argv[3] == string("ENC")){
        /* Perform encryption */
        outputText = cipher->encrypt(inputText).c_str();
        outputFile << outputText << '\n';
    }
    else if(argv[3] == string("DEC")){
        /* Perform decryption */
        outputText = cipher->decrypt(inputText);	
        outputFile << outputText << '\n';
    }
    else{
        // Error did not specify either ENC or DEC
        fprintf(stderr,"Error invalid input for ENC/DEC option.Please use following format.\n"
                "./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUTFILE> <OUTPUTFILE>\n");
        exit(-1);
    }

    // Close file streams
    inputFile.close();
    outputFile.close();

    delete cipher;

    return 0;

} // End of main()
