#include "VigenereAuto.h"
#include<iostream>
#include <string>
using namespace std;

const string allAlphabet{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

int VigenereAuto::mod(int k, int n) { //-1,26
	return ((k %= n) < 0) ? k + n : k;
	// k=k%n
	/*
	if (k <0) {
		return k = k + n

	}
	else return k
	*/



}



void VigenereAuto::textToUpper(string& text) {
	for (int i = 0; i < size(text); i++)
	{
		text[i] = toupper(text[i]);
	}
}

string VigenereAuto::Encrypt(string plainText, string key) {
	plainText.erase(remove(plainText.begin(), plainText.end(), ' '), plainText.end());

	textToUpper(plainText);
	textToUpper(key);
	string keysteam = VigenereAuto::Autokeystream(plainText, key);
	string encryptedtext = plainText;
	for (int i = 0; i < size(plainText); i++) // plaintext size equal keysteam
	{

		int index_pt = allAlphabet.find(plainText[i]);
		int index_ks = allAlphabet.find(keysteam[i]);

		encryptedtext[i] = allAlphabet[mod(index_pt + index_ks, 26)];
	}
	return encryptedtext;
}

string VigenereAuto::Decrypt(string cipherText, string key)
{


	cipherText.erase(remove(cipherText.begin(), cipherText.end(), ' '), cipherText.end());
	textToUpper(cipherText);
	textToUpper(key);

	string decryptedtext = cipherText;
	for (int i = 0; i < size(cipherText); i++) // plaintext size equal keysteam
	{

		int index_ct = allAlphabet.find(cipherText[i]);
		int index_ks = allAlphabet.find(key[i]);

		decryptedtext[i] = allAlphabet[mod(index_ct - index_ks, 26)];
	}
	return decryptedtext;
}


string VigenereAuto::Analyse(string plainText, string cipherText) {
	plainText.erase(remove(plainText.begin(), plainText.end(), ' '), plainText.end());
	cipherText.erase(remove(cipherText.begin(), cipherText.end(), ' '), cipherText.end());
	cipherText.erase(remove(cipherText.begin(), cipherText.end(), ' '), cipherText.end());
	textToUpper(cipherText);
	textToUpper(plainText);
	string keystream = cipherText;
	// plaintext[i] + x = cipherText[i]
	// x = cipherText[i] - plaintext[i]
	for (int i = 0; i < size(cipherText); i++) // plaintext size equal keysteam
	{

		int index_ct = allAlphabet.find(cipherText[i]);
		int index_pt = allAlphabet.find(plainText[i]);
		keystream[i] = allAlphabet[mod(index_ct - index_pt, 26)];
	}
	return keystream;
}


string VigenereAuto::Autokeystream(string PlainTEXT, string Key) {
	int sizeofnewKey = 10;
	int differnce;
	int keycounter = 0; //for key
	int plaintextcounter = 0;// for plaintext
	string keystream = PlainTEXT;

	if (size(PlainTEXT) > size(Key)) { //key : hello   , pt : computer   , counter = 3
		//append key
		differnce = size(PlainTEXT) - size(Key); // 5
		sizeofnewKey = size(Key) + differnce; // 8 
		for (int i = 0; i < sizeofnewKey; i++)
		{
			//counter = 0 , update [h] at index 0
			//counter = 1 , update [e] at index 1
			//counter = 2 , update [l] at index 2
			//counter = 3 , update [l] at index 3
			//counter = 4 , update [o] at index 4
			if (keycounter < size(Key)) {

				keystream[i] = Key[keycounter];

				keycounter++;
			}

			//plaintextcounter = 0 , update [c] at index 5
			//plaintextcounter = 1 , update [o] at index 6
			//plaintextcounter = 2 , update [m] at index 7
			else {
				keystream[i] = PlainTEXT[plaintextcounter];
				plaintextcounter++;

			}


		}

		return keystream;
	}
	else if (size(PlainTEXT) < size(Key)) {

		return "Warning : plaintext must be longer than or equal key ";
	}
	else
	{
		return Key;
	}




	return "please enter valid data";
}

