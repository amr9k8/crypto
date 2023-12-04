#pragma once
#include <String>
#include <algorithm> 
#include <iostream>
using namespace std;

class PlayFair
{
public:
	void create_matrix(string key);
	void encrypt(string plain_txt);
	void decrypt(string cipher_txt);
};


