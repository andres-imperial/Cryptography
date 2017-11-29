#ifndef HILL_H
#define HILL_H

#include <vector>   /* For vectors */
#include <string>   /* For C++ strings */
#include <stdio.h>  /* For standard I/O */
#include <stdlib.h> /* For miscellenous C functions */
#include "CipherInterface.h"

using namespace std;

/**
 * This class implements the playfair cipher.
 * The class extends the abstract class
 * CipherInterface.
 */
int getThreeDet(int matrix[3][3]);
int getAdjMat(int *m[3][3], int *newMat[3][3]);

class Hill: public CipherInterface
{
	/** The public members **/
	public:

		/**
		 * Sets the key to use
		 * @param key - the key to use
		 * @return - True if the key is valid and False otherwise
		 */
		virtual bool setKey(const string& key);

		/**
		 * Encrypts a plaintext string
		 * @param plaintext - the plaintext string
		 * @return - the encrypted ciphertext string
		 */
		virtual string encrypt(const string& plaintext);

		/**
		 * Decrypts a string of ciphertext
		 * @param ciphertext - the ciphertext
		 * @return - the plaintext
		 */
		virtual string decrypt(const string& ciphertext);

		/**
		 * Prints the Playfair matrix
		 * @param fp - the file pointer
		 */
		void printMatrix(FILE* fp);

        /**
         * Scrubs the text and formats it for encryption/decryption
         * @param dirtyText - the unformatted text
         * @return - the formatted text
         */

		/* The protected members */
	protected:
        int keyMatrix[3][3];

};

#endif
