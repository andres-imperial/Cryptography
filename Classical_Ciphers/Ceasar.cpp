#include "Ceasar.h"
#include <string>

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Ceasar::setKey(const string& key)
{ 
    masterKey = atoi(key.c_str());

    if(!(masterKey < 26 && masterKey > -1)){
        return false;
    }
    else{
        return true;  
    }

} // End of setKey()


/**	
 * Encrypts a plainText string
 * @param plainText - the plainText string
 * @return - the encrypted cipherText string
 */
string Ceasar::encrypt(const string& plainText)
{ 
    // Variables
    string cipherText;

    for(int i = 0; i < plainText.length(); ++i){
        cipherText.push_back(getCeasarLetter(plainText[i], masterKey));
    }

    return cipherText; 

} // End of encrypt()


/**
 * Decrypts a string of cipherText
 * @param cipherText - the cipherText
 * @return - the plainText
 */
string Ceasar::decrypt(const string& cipherText) 
{ 
    string plainText;
    int index = 0;

    for(int i = 0; i < cipherText.length(); ++i){
        plainText.push_back(getPlainLetter(cipherText[i], masterKey));
    }

    return plainText; 

} // End of decrypt()

char getCeasarLetter(char plainChar, int keyOff)
{
    // Variables
    int plainOff = plainChar - 'a';

    return 'a' + ((plainOff + keyOff) % 26);

} // End of getVigLetter()

char getPlainLetter(char cipherChar, int keyOff)
{
    // Variables
    int offset, cipherOff;

    cipherOff = cipherChar - 'a';
    offset = cipherOff - keyOff;

    if(offset < 0){
        return 'z' + offset + 1;
    }
    else{
        return 'a' + offset;
    }

} // End of getPlainLetter()
