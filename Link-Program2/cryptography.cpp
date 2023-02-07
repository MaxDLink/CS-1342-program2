//
// Created by Max Link on 2/25/22.
//
#include <iostream>
#include "cryptography.h"
#include <string>

using namespace std;

//returns value & takes argument by value
string encrypt(string plainText, string key) {

    int shiftbyCounter = 0;
    int shiftAmount;
    int keyLetter;
    int encryptedLetter;
    char upperCase;
    string encrypted;
    //for loop that cycles through the word
    for (int i = 0; i < plainText.size(); i++) {
        //working with uppercase
        upperCase = toupper(plainText[i]);


        if (upperCase < 65 || upperCase > 90) {
            //appending punctuations/spaces unchanged (not A-Z)
            encrypted += upperCase;
        } else {
            //taking the next letter in the key
            keyLetter = (int) key[shiftbyCounter % key.size()];
            //keyletter - A. Gives how far from A moving
            shiftAmount = keyLetter - 65;

            //shifting original letter
            encryptedLetter = upperCase + shiftAmount;
            //checks for Z pass
            if (encryptedLetter > 90) {
                //Difference between everything after Z and original letter. Taking distance & adding it to A to get capital wrap letter
                encryptedLetter = encryptedLetter - 91 + 65;
            }
            //appending capital encrypted letter to encrypted string
            encrypted += encryptedLetter;
//            cout << "Input: " << upperCase << " " << "keyLetter: " << (char) keyLetter << " " << "ShiftAmount: "
//                 << shiftAmount << " " << "Encrypted: " << encrypted << endl;
            shiftbyCounter++;
        }
    }
    cout << "Encrypted phrase: " << encrypted << endl;
    return encrypted;
}

//Function returns value & takes argument by reference
string findKey(string& cypherText) {
    string plainText = "ATTENT"; //ATTENTION - up to 6 characters
    string key;
    for (int i = 0; i < plainText.size(); i++) {
        int keyLetter = cypherText[i] - plainText[i] + 65;
        if (cypherText[i] < plainText[i]) {
            keyLetter = (cypherText[i] - 65) + (91 - plainText[i]) + 65;
        }
//        cout << "plainText letter: " << plainText[i] << " key letter: " << keyLetter << endl;
        if (key.find(keyLetter) == 0) {
            break;
        }
        key += (char) keyLetter;
    }
    cout << "Key: " << key << endl;
    return key;
}

//function returns value & takes argument by value
string decrypt(string cypherText, string key) {

    int shiftbyCounter = 0;
    int shiftAmount;
    int keyLetter;
    int plainLetter;
    char upperCase;
    string plainText;
    //for loop that cycles through the word
    for (int i = 0; i < cypherText.size(); i++) {
        //working with uppercase
        upperCase = toupper(cypherText[i]);


        if (upperCase < 65 || upperCase > 90) {
            //appending punctuations/spaces unchanged (not A-Z)
            plainText += upperCase;
        } else {
            //taking the next letter in the key
            keyLetter = (int) key[shiftbyCounter % key.size()];
            //keyletter - A. Gives how far from A moving
            shiftAmount = keyLetter - 65;

            //shifting original letter
            plainLetter = upperCase - shiftAmount;
            //checks for Z pass
            if (plainLetter < 65) {
                int distanceCypherTextToA = upperCase - 65;
                int remainingKeyDistance = keyLetter - 65 - distanceCypherTextToA;
                plainLetter = 91 - remainingKeyDistance; //z = 91
            }
            //appending capital encrypted letter to encrypted string
            plainText += plainLetter;
//            cout << "Input: " << upperCase << " " << "keyLetter: " << (char) keyLetter << " " << "ShiftAmount: "
//                 << shiftAmount << " " << "plainText: " << plainText << endl;
            shiftbyCounter++;
        }
    }
    cout << "plainText: " << plainText << endl;
    return plainText;
}

//does not return value or take argument by value
void interface() {

    int userChoice = -1;

    while (userChoice != 0) {

        cout << "1. Intercept Incoming Message" << endl;
        cout << "2. Encrypt Message" << endl;
        cout << "0. Quit" << endl;

        cin >> userChoice;
        cin.ignore();


        if (userChoice == 2) {
            string plainText;
            cout << "Enter plainText:" << endl;
            getline(cin, plainText);
            string key;
            bool keyInvalid = true;
            while (keyInvalid) {
                cout << "Enter key:" << endl;
                getline(cin, key);
                for (int i = 0; i < key.size(); i++) {
                    if (key[i] > 90 || key[i] < 65) {
                        cout << "Key incorrect. Must be uppercase letters" << endl;
                        break;
                    } else {
                        keyInvalid = false;
                    }
                }

            }
            string encryptedString;
            encryptedString = encrypt(plainText, key);


        } else if (userChoice == 1) {
            string cypherText;
            cout << "Enter cypherText:" << endl;
            getline(cin, cypherText);
            cout << "Encrypted String: " << cypherText << endl;
            //decrypt
            string interceptKey;
            interceptKey = findKey(cypherText);
            decrypt(cypherText, interceptKey);
        } else if (userChoice > 2) {
            cout << "Invalid value. try again" << endl;
        }
        //comparing strings
//        if (encryptedString.compare(cypherText) == 0) {
//            cout << "They are equal" << endl;
//        } else {
//            cout << "They do not match" << endl;
//        }
//        cout << "encrypted: " << encryptedString << endl;
//        cout << "cypherText: " << cypherText << endl;
    }
    cout << "User Quit" << endl;
}
