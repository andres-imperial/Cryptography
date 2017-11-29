#include "Hill.h"
#include <string>

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Hill::setKey(const string& key)
{ 
    int index = 0;
    int alphaIndex = 0;

    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(index < key.length()){
                // assign key word to 3x3 matrix
                keyMatrix[i][j] = (int)key[index] - 'a';
                ++index;
            }
            else{
                keyMatrix[i][j] = alphaIndex;
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
string Hill::encrypt(const string& plainText)
{ 
    int triGraphs[plainText.length()/3][3];
    int encGraphs[plainText.length()/3][3];
    string cipherText;

    for(int index = 0; index < plainText.length();){
        for(int i = 0; i < 3; ++i, ++index){
            triGraphs[index/3][i] = (int)plainText[index] - 'a'; 
        }
    }

    for(int i = 0; i < plainText.length()/3; ++i){
        for(int j = 0; j < 3; ++j){
            encGraphs[i][j] = (keyMatrix[j][0] * triGraphs[i][0]) +
                              (keyMatrix[j][1] * triGraphs[i][1]) + 
                              (keyMatrix[j][2] * triGraphs[i][2]);
            encGraphs[i][j] %= 26;
            cipherText.push_back('a' + encGraphs[i][j]);
        }
    }
    
    return cipherText; 

} // End of encrypt()


/**
 * Decrypts a string of cipherText
 * @param cipherText - the cipherText
 * @return - the plainText
 */
string Hill::decrypt(const string& cipherText) 
{ 
//    string plainText;
//    int det = getThreeDet(keyMatrix) % 26;
//    int index = 0;
//    int multiplier;
//    int adjMat[3][3];
//
//    while((det * multiplier) % 26 != 1){
//        ++multiplier;
//    }
//
//    getAdjMat(keyMatrix, adjMat);
//
//    while(index < cipherText.length()){
//        for(int i = 0; i < 5; ++i){
//            for(int j = 0; j < 5; ++j){
//                if(cipherText[index] == keyMatrix[i][j]){
//                    first[0] = i;
//                    first[1] = j;
//                }
//                else if(cipherText[index + 1] == keyMatrix[i][j]){
//                    second[0] = i;
//                    second[1] = j;
//                }
//            }
//        }
//
//        if(first[0] == second[0]){
//            plainText.push_back(keyMatrix[first[0]][(--first[1] + 5) % 5]);
//            plainText.push_back(keyMatrix[second[0]][(--second[1] + 5) % 5]);
//            index += 2;
//        }
//        else if(first[1] == second[1]){
//            plainText.push_back(keyMatrix[(--first[0] + 5) % 5][first[1]]);
//            plainText.push_back(keyMatrix[(--second[0] + 5) % 5][second[1]]);
//            index += 2;
//        }
//        else{
//            plainText.push_back(keyMatrix[first[0]][second[1]]);
//            plainText.push_back(keyMatrix[second[0]][first[1]]);
//            index += 2;
//        }
//    }
//
//	return plainText; 

} // End of decrypt()

int getThreeDet(int m[3][3])
{
    int determinant;

    determinant = (m[0][0] * ((m[1][1] * m[2][2]) - (m[1][2] * m[2][1]))) -
                  (m[0][1] * ((m[1][0] * m[2][2]) - (m[1][2] * m[2][0]))) +
                  (m[0][2] * ((m[1][0] * m[2][1]) - (m[1][1] * m[2][0]))); 

    return determinant;

} // End of getThreeDet()

int* getAdjMat(int m[9], int newMat[9])
{
//    newMat[0] = ((m[4] * m[8]) - (m[5] * m[7]));
//    newMat[1] = -((m[1] * m[8]) - (m[2] * m[7]));
//    newMat[2] = ((m[1] * m[5]) - (m[4] * m[2]));
//    newMat[3] = -((m[3] * m[8]) - (m[6] * m[5]));
//    newMat[4] = ((m[0] * m[8]) - (m[6] * m[5]));
//    newMat[5] = -((m[0] * m[5]) - (m[3] * m[2]));
//    newMat[6] = ((m[3] * m[7]) - (m[4] * m[6]));
//    newMat[7] = -((m[0] * m[7]) - (m[6] * m[1]));
//    newMat[8] = ((m[0] * m[4]) - (m[3] * m[1])); 
//    
//    newMat[0] %= 26;
//    newMat[1] %= 26;
//    newMat[2] %= 26;
//    newMat[3] %= 26;
//    newMat[4] %= 26;
//    newMat[5] %= 26;
//    newMat[6] %= 26;
//    newMat[7] %= 26;
//    newMat[8] %= 26;
//
//    return newMat;
} // End of getAdjMat()
