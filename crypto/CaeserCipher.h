#pragma once
#include<iostream>
#include <string>
using namespace std;
class CaeserCipher
{
public:
	int mod(int k, int n);
	void textToUpper(string& text);
	string EncryptCaeser(string plainText, int keyValue);
	string DecryptCaeser(string EncryptedText, int keyValue);
	void bruteforceCaeser(string EncryptedText);
	int cryptanalysis(string EncryptedText, string plain_txt);

};

