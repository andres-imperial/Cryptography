#include "AES.h"

/**
 * Sets the key to use
 * @param key - the first byte of this represents whether
 * to encrypt or to decrypt. 00 means encrypt and any other
 * value to decrypt.  Then come the bytes of the 128-bit key
 * (should be 16 of them).
 * @return - True if the key is valid and False otherwise
 */
bool AES::setKey(const unsigned char* keyArray)
{
	
	// TODO: AES implementation of openssl cares about whether
	// you are encrypting or decrypting when setting the key.
	// That is, when encrypting you use function AES_set_encrypt_key(...)
	// and when decrypting AES_set_decrypt_key(...).
	//
	// One way to solve this problem is to pass in a 17 byte key, where
	// the first byte is used to indicate whether we are encrypting or
	// decrypting. E.g., if the first byte is 0, then use AES_set_encrypt_key(...).
	// Otherwise, use AES_set_decrypt_key(...).  The rest of the bytes in the
	// array indicate the 16 bytes of the 128-bit AES key.
	//
	// Both functions return 0 on success and other values on faliure.
	// For documentation, please see https://boringssl.googlesource.com/boringssl/+/2623/include/openssl/aes.h
	// and aes.cpp example provided with the assignment.
        
        // Check the LAST index for enc/dec flag
        const static unsigned char aes_key[]={0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};
        if(keyArray[16] == 0){
            //encrypt
            printf("encrytping");
            if(AES_set_encrypt_key(aes_key, 128, &this->key)!=0)
            {
		fprintf(stderr, "AES_set_encrypt_key() failed!\n");
		exit(-1);
            }
        }
        else{
            //decrypt
            printf("dencrytping");
            if(AES_set_decrypt_key(aes_key, 128, &this->key) != 0)
            {
		fprintf(stderr, "AES_set_decrypt_key() failed!\n");
            }
        }
	
}
 
/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
unsigned char* AES::encrypt(const unsigned char* plainText)
{
	
	//TODO: 1. Dynamically allocate a block to store the ciphertext.
        unsigned char* ciphertext = new unsigned char[8];
	//	2. Use AES_ecb_encrypt(...) to encrypt the text (please see the URL in setKey(...)
	//	and the aes.cpp example provided.
        AES_ecb_encrypt(plainText, ciphertext, &this->key, AES_ENCRYPT);
	// 	3. Return the pointer to the ciphertext
		
	return ciphertext;	
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
unsigned char* AES::decrypt(const unsigned char* cipherText)
{
	
	//TODO: 1. Dynamically allocate a block to store the plaintext.
        unsigned char* plaintext = new unsigned char[8];
	//	2. Use AES_ecb_encrypt(...) to decrypt the text (please see the URL in setKey(...)
	//	and the aes.cpp example provided.
	AES_ecb_encrypt(cipherText, plaintext, &this->key, AES_DECRYPT);
	// 	3. Return the pointer to the plaintext
		
	return plaintext;
}



