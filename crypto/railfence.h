#pragma once
using namespace std;
#include <String>;

class railfence
{

public:

	string Encrypt_RainFence(string plain_txt, int key);
	string Decrypt_RainFence(string cipher_txt, int key);
	int Analyse_RainFence(string plain_txt, string cipher_txt);
};

