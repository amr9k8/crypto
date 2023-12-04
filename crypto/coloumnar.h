#pragma once
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <cmath> 
using namespace std;
class coloumnar
{
public:
	int key_numOf_Eelemnts;

	string Encrypt(string plaintext, int key[]);
	string Decrypt(string ciphertext, int key[]);
	list<int> analyse(string plaintext, string ciphertext);

};

