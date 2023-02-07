//
// Created by Max Link on 2/25/22.
//

#ifndef PROGRAM2_CRYPTOGRAPHY_H
#define PROGRAM2_CRYPTOGRAPHY_H
#include <string>

using namespace std;

class cryptography {
private:

public:
};

string encrypt(string plainText, string key);

string findKey(string& cypherText);

string decrypt(string cypherText, string key);

void interface();

#endif //PROGRAM2_CRYPTOGRAPHY_H
