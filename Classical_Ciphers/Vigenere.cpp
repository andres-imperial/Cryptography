#include "Vigenere.h"
#include <string>

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Vigenere::setKey(const string& key)
{ 
    masterKey = key;

    return true;  

} // End of setKey()


/**	
 * Encrypts a plainText string
 * @param plainText - the plainText string
 * @return - the encrypted cipherText string
 */
string Vigenere::encrypt(const string& plainText)
{ 
    // Variables
    string cipherText;

    for(int i = 0; i < plainText.length();){
        for(int j = 0; j < masterKey.length() && i < plainText.length(); ++j){ 
            cipherText.push_back(getVigLetter(plainText[i], masterKey[j]));
            ++i;
        }
    }

    return cipherText; 

} // End of encrypt()


/**
 * Decrypts a string of cipherText
 * @param cipherText - the cipherText
 * @return - the plainText
 */
string Vigenere::decrypt(const string& cipherText) 
{ 
    string plainText;
    int index = 0;

    for(int i = 0; i < cipherText.length();){
        for(int j = 0; j < masterKey.length() && i < cipherText.length(); ++j){ 
            plainText.push_back(getPlainLetter(cipherText[i], masterKey[j]));
            ++i;
        }
    }

    return plainText; 

} // End of decrypt()

char getVigLetter(char plainChar, char keyChar)
{
    // Variables
    int plainOff, keyOff;

    plainOff = plainChar - 'a';
    keyOff = keyChar - 'a';

    return 'a' + ((plainOff + keyOff) % 26);

} // End of getVigLetter()

char getPlainLetter(char cipherChar, char keyChar)
{
    // Variables
    int offset, cipherOff, keyOff;

    cipherOff = cipherChar - 'a';
    keyOff = keyChar - 'a';
    offset = cipherOff - keyOff;

    if(offset < 0){
        return 'z' + offset + 1;
    }
    else{
        return 'a' + offset;
    }

} // End of getPlainLetter()

string lowerString(string inputString)
{
    string cleanText;

    for(string::iterator it = inputString.begin(); it != inputString.end(); ++it){
        cleanText.push_back(tolower(*it));
    }

    return cleanText;

} // End of lowerString()
