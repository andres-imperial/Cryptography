#include "RailFence.h"
#include <cstring>

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool RailFence::setKey(const string& key)
{ 
    masterKey = atoi(key.c_str());

    return true;  

} // End of setKey()


/**	
 * Encrypts a plainText string
 * @param plainText - the plainText string
 * @return - the encrypted cipherText string
 */
string RailFence::encrypt(const string& plainText)
{ 
    // Variables
    string rows[masterKey];
    string cipherText;

    for(int i = 0; i < plainText.length();){
        do{
            rows[i % masterKey].push_back(plainText[i]);
            ++i;
        }while(i % masterKey);
    }

    for(int i = 0; i < masterKey; ++i){
        cipherText.append(rows[i]);
    }
	
    return cipherText; 

} // End of encrypt()


/**
 * Decrypts a string of cipherText
 * @param cipherText - the cipherText
 * @return - the plainText
 */
string RailFence::decrypt(const string& cipherText) 
{ 
    string plainText;
    string rows[masterKey];
    int index = 0;

     for(int i = 0; i < cipherText.length(); ++index){
         for(int j = 0; j < cipherText.length()/masterKey; ++j){
            rows[index].push_back(cipherText[i]);
            ++i;
        }
    }

    for(int i = 0, index = 0; i < cipherText.length(); ++index){
        do{
            plainText.push_back(rows[i % masterKey][index]);
            ++i;
        }while(i % masterKey);
    }

    return plainText; 

} // End of decrypt()
