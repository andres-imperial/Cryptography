#include "Playfair.h"
#include <string>

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Playfair::setKey(const string& key)
{ 
    char alpha[26] = {'a','b','c','d','e','f','g','h','i',0,'k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int index = 0;
    int alphaIndex = 0;

    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j){
            if(index < key.length()){
                // Check if letter has already been used and continue until we
                // find an unused letter.
                while(alpha[key[index] - 'a'] == 0){
                    ++index;
                }
                // If not then go ahead and assign it to the key and remove
                // it from the bank of letters alpha
                keyMatrix[i][j] = key[index];
                alpha[key[index] - 'a'] = 0;
                ++index;
            }
            else{
                while(alpha[alphaIndex] == 0){
                    ++alphaIndex;
                }
                keyMatrix[i][j] = alpha[alphaIndex];
                ++alphaIndex;
            }
            
        }
    }
	
    return true;  

} // End of setKey()


/**	
 * Encrypts a plainText string
 * @param plainText - the plainText string
 * @return - the encrypted cipherText string
 */
string Playfair::encrypt(const string& plainText)
{ 
    int first[2], second[2];
    string cipherText;
    int index = 0;

    while(index < plainText.length()){
        for(int i = 0; i < 5; ++i){
            for(int j = 0; j < 5; ++j){
                if(plainText[index] == keyMatrix[i][j]){
                    first[0] = i;
                    first[1] = j;
                }
                else if(plainText[index + 1] == keyMatrix[i][j]){
                    second[0] = i;
                    second[1] = j;
                }
            }
        }

        if(first[0] == second[0]){
            cipherText.push_back(keyMatrix[first[0]][++first[1] % 5]);
            cipherText.push_back(keyMatrix[second[0]][++second[1] % 5]);
            index += 2;
        }
        else if(first[1] == second[1]){
            cipherText.push_back(keyMatrix[++first[0] % 5][first[1]]);
            cipherText.push_back(keyMatrix[++second[0] % 5][second[1]]);
            index += 2;
        }
        else{
            cipherText.push_back(keyMatrix[first[0]][second[1]]);
            cipherText.push_back(keyMatrix[second[0]][first[1]]);
            index += 2;
        }
    }
	
	return cipherText; 

} // End of encrypt()


/**
 * Decrypts a string of cipherText
 * @param cipherText - the cipherText
 * @return - the plainText
 */
string Playfair::decrypt(const string& cipherText) 
{ 
    int first[2], second[2];
    string plainText;
    int index = 0;

    while(index < cipherText.length()){
        for(int i = 0; i < 5; ++i){
            for(int j = 0; j < 5; ++j){
                if(cipherText[index] == keyMatrix[i][j]){
                    first[0] = i;
                    first[1] = j;
                }
                else if(cipherText[index + 1] == keyMatrix[i][j]){
                    second[0] = i;
                    second[1] = j;
                }
            }
        }

        if(first[0] == second[0]){
            plainText.push_back(keyMatrix[first[0]][(--first[1] + 5) % 5]);
            plainText.push_back(keyMatrix[second[0]][(--second[1] + 5) % 5]);
            index += 2;
        }
        else if(first[1] == second[1]){
            plainText.push_back(keyMatrix[(--first[0] + 5) % 5][first[1]]);
            plainText.push_back(keyMatrix[(--second[0] + 5) % 5][second[1]]);
            index += 2;
        }
        else{
            plainText.push_back(keyMatrix[first[0]][second[1]]);
            plainText.push_back(keyMatrix[second[0]][first[1]]);
            index += 2;
        }
    }
	
	return plainText; 

} // End of decrypt()

/**
 * Scrubs the text and formats it for encryption/decryption
 * @param dirtyText - the unformatted text
 * @return - the formatted text
 */
string scrubText(string dirtyText, bool isKey)
{
    string cleanText;
 
    // Delete all 'j' characters and replace with 'i'.
    // Also make all characters lower case.
    for(string::iterator it = dirtyText.begin(); it != dirtyText.end(); ++it){
        if(*it == 'j'){
            cleanText.push_back('i');
        }
        cleanText.push_back(tolower(*it));
    }

    if(!isKey){
        // Check for any repeated letters and replace the second with an 'x'
        for(int i = 0; i < cleanText.length(); i += 2){
            if(cleanText[i] == cleanText[i + 1]){
                cleanText[i + 1] = 'x';
            }
        }

        // Check for even input, else append a filler 'x' character
        if(cleanText.length() % 2){
            cleanText.push_back('x');
        }
    }

    return cleanText;
 
} // End of scrubText()
