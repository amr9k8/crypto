#include "CaeserCipher.h"
#include<iostream>
#include <string>
using namespace std;

const string allAlphabet{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

int CaeserCipher::mod(int k, int n) {
	return ((k %= n) < 0) ? k + n : k;
}

void CaeserCipher::textToUpper(string& text) {
	for (int i = 0; i < size(text); i++)
	{
		text[i] = toupper(text[i]);
	}
}

string CaeserCipher::EncryptCaeser(string plainText, int keyValue) 
{
	textToUpper(plainText);

	string temp_plainText = "";
	for (int i = 0; i < plainText.length(); i++)
	{
		if (plainText[i] != ' ')
		{
			temp_plainText += plainText[i];
		}
	}

	plainText.clear();
	plainText = temp_plainText;


	for (int i = 0; i < size(plainText); i++)
	{
		int index = allAlphabet.find(plainText[i]);
		plainText[i] = allAlphabet[(index + keyValue) % 26];
	}
	return plainText;
}


string CaeserCipher::DecryptCaeser(string EncryptedText, int keyValue) {

	textToUpper(EncryptedText);

	string temp_EncryptedText = "";
	for (int i = 0; i < EncryptedText.length(); i++)
	{
		if (EncryptedText[i] != ' ')
		{
			temp_EncryptedText += EncryptedText[i];
		}
	}

	EncryptedText.clear();
	EncryptedText = temp_EncryptedText;

	for (int i = 0; i < size(EncryptedText); i++)
	{
		int index = allAlphabet.find(EncryptedText[i]);
		EncryptedText[i] = allAlphabet[mod(index - keyValue, 26)];
	}	
	return EncryptedText;
}



void CaeserCipher::bruteforceCaeser(string EncryptedText) {
	
	string DecryptedText = "";

	textToUpper(EncryptedText);
	for (int i = 0; i < EncryptedText.length(); i++)
	{
		if (EncryptedText[i] != ' ')
		{
			DecryptedText += EncryptedText[i];
		}
	}

	for (int j = 0; j <= 15; j++) 
	{
		for (int i = 0; i < size(EncryptedText); i++)
		{
			int index = allAlphabet.find(EncryptedText[i]);
			DecryptedText[i] = allAlphabet[mod(index - j, 26)];
		}
		cout << " at key  = " << j << "	Result is : " << DecryptedText << endl;
	}
}

int CaeserCipher::cryptanalysis(string EncryptedText, string plain_txt)
{
	string temp_plain_txt ="";
	for (int i = 0; i < plain_txt.length(); i++)
	{
		if (plain_txt[i] != ' ')
		{
			temp_plain_txt += plain_txt[i];
		}
	}
	textToUpper(EncryptedText);
	textToUpper(temp_plain_txt);
	string DecryptedText = EncryptedText;

	
	for (int j = 0; j <= 15; j++)
	{
		for (int i = 0; i < size(EncryptedText); i++)
		{
			int index = allAlphabet.find(EncryptedText[i]);
			DecryptedText[i] = allAlphabet[mod(index - j, 26)];
		}
		if (temp_plain_txt == DecryptedText)
		{
			
			return j;
		}
		
	}
}