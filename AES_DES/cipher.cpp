#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"

using namespace std;

int main(int argc, char** argv)
{
	/**
	 * TODO: Replace the code below	with your code which can SWITCH
	 * between DES and AES and encrypt files. DO NOT FORGET TO PAD
	 * THE LAST BLOCK IF NECESSARY.
	 *
	 * NOTE: due to the incomplete skeleton, the code may crash or
	 * misbehave.
	 */
	/* Create an instance of the DES cipher */	
	CipherInterface* cipher = NULL; 
        FILE* inputFile;
        FILE* outputFile;
        unsigned char* inputText;
        unsigned char* outputText;
        unsigned char key[17] = {};
        int buffersize;

        // copy key
        for(int i = 0 ; i < 16; ++i){
            key[i] = argv[2][i];
        }
		
        // Check for proper amount of arguments
        if(argc != 7){
            fprintf(stderr, "Error that is the wrong number of arguments please follow format:"
            "./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUT FILE> <OUTPUT FILE> <ECB/CBC/CFB>");        
            exit(-1);
        }

        //Open files for I/O
        inputFile = fopen(argv[4], "r+");
        outputFile = fopen(argv[5], "w");
        if(inputFile == NULL){
            fprintf(stderr, "Error input file was not able to be opened.");
            exit(-1);
        }
        else if(outputFile == NULL){
            fprintf(stderr, "Error output file was not able to be opened.");
            exit(-1);
        }

	// See which encryption method is specified
        if(argv[1] == string("DES")){
            buffersize = 8;
            inputText = new unsigned char[buffersize];
            outputText = new unsigned char[buffersize];
            cipher = new DES();
        }
        else if(argv[1] == string("AES")){
            buffersize = 16;
            inputText = new unsigned char[buffersize];
            outputText = new unsigned char[buffersize];
            cipher = new AES();
            if(argv[3] == string("ENC")){
                key[16] = 0;
            }
            else{
                key[16] = 1;
            }
        }
        else{
            fprintf(stderr,"Error please specify cipher type: AES||DES"
            "./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUT FILE> <OUTPUT FILE>");        
            exit(-1);
        }

	/* Error checks */
	if(!cipher)
	{
		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}
	
	/* Set the encryption key
	 * A valid key comprises 16 hexidecimal
	 * characters. Below is one example.
	 * Your program should take input from
	 * command line.
	 */
	cipher->setKey(key);
	
        char mychar;
        int retChars;
        fseek(inputFile, 0, SEEK_END);
        retChars = ftell(inputFile);
        cout << "retchars: " << retChars << endl;
        for(int i = retChars%buffersize; i < buffersize && i != 0; ++i){
            fputc('\0',inputFile);
        }
        rewind(inputFile);
        if(argv[3] == string("ENC")){
            /* Perform encryption */
            if(argv[6] == string("CBC")){
                // CBC MODE
                unsigned char ciphertext[8] = {'C','P','C','S','4','5','2','!'};
                while(true){
                    if(retChars = fread(inputText, 1, buffersize, inputFile) !=buffersize)
                        break;
                    cout << inputText << endl;
                    // XOR plaintext with previous ciphertext
                    for(int i = 0; i < buffersize; ++i){
                        inputText[i] = (unsigned char)(inputText[i] ^ ciphertext[i]);
                    }
                    cout << inputText << endl;
                    outputText = cipher->encrypt(inputText);
                    // copy ciphertext to save it for next round of XOR
                    for(int i = 0; i < buffersize; ++i){
                        ciphertext[i] = outputText[i];
                    }
                    cout << outputText << endl;
                    fwrite(outputText, 1, buffersize, outputFile);
                }
            }
            else if(argv[6] == string("CFB")){
                // CFB MDOE
                printf("Not yet implemented, Exiting.");
                exit(-1);
            }
            else if(argv[6] == string("ECB")){ // Normal MODE
                while(true){
                    if(retChars = fread(inputText, 1, buffersize, inputFile) !=buffersize)
                        break;
                    cout << inputText << endl;
                    outputText = cipher->encrypt(inputText);
                    cout << outputText << endl;
                    fwrite(outputText, 1, buffersize, outputFile);
                }
            }
            else{
                printf("Valid mode not specified, please choose: ECB/CBC/CFB\n");
                exit(-1);
            }
        }
        else if(argv[3] == string("DEC")){
            /* Perform decryption */
            if(argv[6] == string("CBC")){
                // CBC MODE
                unsigned char ciphertext[8] = {'C','P','C','S','4','5','2','!'};
                while(true){
                    if(retChars = fread(inputText, 1, buffersize, inputFile) !=buffersize)
                        break;
                    cout << inputText << endl;
                    outputText = cipher->decrypt(inputText);
                    // XOR plaintext with previous ciphertext
                    for(int i = 0; i < buffersize; ++i){
                        outputText[i] = (unsigned char)(outputText[i] ^ ciphertext[i]);
                    }
                    // copy ciphertext to save it for next round of XOR
                    for(int i = 0; i < buffersize; ++i){
                        ciphertext[i] = inputText[i];
                    }
                    cout << outputText << endl;
                    fwrite(outputText, 1, buffersize, outputFile);
                }
            }
            else if(argv[6] == string("CFB")){
                // CFB MDOE
                printf("Not yet implemented, Exiting.");
                exit(-1);
            }
            else if(argv[6] == string("ECB")){ // Normal MODE
                while(true){
                    if(retChars = fread(inputText, 1, buffersize, inputFile) !=buffersize)
                        break;
                    cout << inputText << endl;
                    outputText = cipher->decrypt(inputText);
                    cout << outputText << endl;
                    fwrite(outputText, 1, buffersize, outputFile);
                }
            }
            else{
                printf("Valid mode not specified, please choose: ECB/CBC/CFB\n");
                exit(-1);
            }
        }
        else{
            fprintf(stderr,"Error please specify encryption or decryption: ENC||DEC"
            "./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUT FILE> <OUTPUT FILE>");        
            exit(-1);
        }

        fclose(inputFile);
        fclose(outputFile);

	return 0;
}
