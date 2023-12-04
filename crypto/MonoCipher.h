#pragma once
using namespace std;
#include <iostream>

class MonoCipher
{
public:
	string encrypt(string plaintext, string key);
	string decrypt(string ciphertext, string key);
	void AnalyseUsingCharFrequency(string ciphertext);
};

