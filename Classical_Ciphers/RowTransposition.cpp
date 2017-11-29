#include "RowTransposition.h"
#include <iostream>
#include <string>

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool RowTransposition::setKey(const string& key)
{ 
    masterKey = key;

    return true;  

} // End of setKey()


/**	
 * Encrypts a plainText string
 * @param plainText - the plainText string
 * @return - the encrypted cipherText string
 */
string RowTransposition::encrypt(const string& plainText)
{ 
    // Variables
    int keyLen = masterKey.length();
    string columns[keyLen];
    string cipherText;

    for(int i = 0; i < plainText.length();){
        do{
            columns[i % keyLen].push_back(plainText[i]);
            ++i;
        }while(i % keyLen);
    }

    for(int i = 0; i < keyLen; ++i){
        cipherText.append(columns[(int)masterKey[i] - '0' - 1]);
    }

    for(int i = 0; i < plainText.length()/keyLen; ++i){
        cout << columns[0][i] << columns[1][i] << columns[2][i] << columns[3][i] << endl;
    }
	
    return cipherText; 

} // End of encrypt()


/**
 * Decrypts a string of cipherText
 * @param cipherText - the cipherText
 * @return - the plainText
 */
string RowTransposition::decrypt(const string& cipherText) 
{ 
    int keyLen = masterKey.length();
    int index = 0;
    string plainText;
    string columns[keyLen];
    string orderedColumns[keyLen];

     for(int i = 0; i < cipherText.length(); ++index){
         for(int j = 0; j < cipherText.length()/keyLen; ++j){
            columns[index].push_back(cipherText[i]);
            ++i;
        }
    }

    for(int i = 0; i < keyLen; ++i){
        orderedColumns[i] = columns[(int)masterKey[i] - '0' - 1];
    }

    for(int i = 0, index = 0; i < cipherText.length(); ++index){
        do{
            plainText.push_back(orderedColumns[i % keyLen][index]);
            ++i;
        }while(i % keyLen);
    }

    for(int i = 0; i < plainText.length()/keyLen; ++i){
        cout << columns[0][i] << columns[1][i] << columns[2][i] << columns[3][i] << endl;
    }
    cout << endl;
    for(int i = 0; i < plainText.length()/keyLen; ++i){
        cout << orderedColumns[0][i] << orderedColumns[1][i] << orderedColumns[2][i] << orderedColumns[3][i] << endl;
    }


    return plainText; 

} // End of decrypt()

/**
 * Scrubs the text and formats it for encryption/decryption
 * @param dirtyText - the unformatted text
 * @return - the formatted text
 */
string evenOutText(int key, string text)
{
    if(!text.length() % key){
        return text;
    }
    else{
        while(text.length() % key){
            text.push_back('x');
        }
    }

    return text;

} // End of evenOutText()
