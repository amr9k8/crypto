#include "VigenereRepeating.h"
#include<iostream>
#include <string>
using namespace std;

const string allAlphabet{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

int VigenereRepeating::mod(int k, int n) { //-1,26
	return ((k %= n) < 0) ? k + n : k;
	// k=k%n
	/*
	if (k <0) {
		return k = k + n

	}
	else return k
	*/



}



void VigenereRepeating::textToUpper(string& text) {
	for (int i = 0; i < size(text); i++)
	{
		text[i] = toupper(text[i]);
	}
}

string VigenereRepeating::Encrypt(string plainText, string key) {

	plainText.erase(remove(plainText.begin(), plainText.end(), ' '), plainText.end());
	textToUpper(plainText);
	textToUpper(key);
	string keysteam = VigenereRepeating::Repeatingkeystream(plainText, key);
	string encryptedtext = plainText;
	for (int i = 0; i < size(plainText); i++) // plaintext size equal keysteam
	{

		int index_pt = allAlphabet.find(plainText[i]);
		int index_ks = allAlphabet.find(keysteam[i]);

		encryptedtext[i] = allAlphabet[mod(index_pt + index_ks, 26)];
	}
	return encryptedtext;
}

string VigenereRepeating::Decrypt(string cipherText, string key) {
	cipherText.erase(remove(cipherText.begin(), cipherText.end(), ' '), cipherText.end());
	textToUpper(cipherText);
	textToUpper(key);
	string decryptedtext = cipherText;
	key = VigenereRepeating::Repeatingkeystream(cipherText, key);
	for (int i = 0; i < size(cipherText); i++) // plaintext size equal keysteam
	{

		int index_ct = allAlphabet.find(cipherText[i]);
		int index_ks = allAlphabet.find(key[i]);

		decryptedtext[i] = allAlphabet[mod(index_ct - index_ks, 26)];
	}
	return decryptedtext;
}


string VigenereRepeating::Analyse(string plainText, string cipherText) {
	cipherText.erase(remove(cipherText.begin(), cipherText.end(), ' '), cipherText.end());
	plainText.erase(remove(plainText.begin(), plainText.end(), ' '), plainText.end());

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

string VigenereRepeating::Repeatingkeystream(string PlainTEXT, string Key) {
	int sizeofnewKey = 10;
	int differnce;
	int keycounter = 0;
	string keystream = PlainTEXT;

	if (size(PlainTEXT) > size(Key)) { //key : hello   , pt : computer   , counter = 3
		//append key
		differnce = size(PlainTEXT) - size(Key); // 5
		sizeofnewKey = size(Key) + differnce; // 8 
		for (int i = 0; i < sizeofnewKey; i++)
		{



			keystream[i] = Key[keycounter];
			keycounter++;

			if (keycounter == (size(Key))) {
				keycounter = 0;
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

	return "	111";
}



//
//string VigenereRepeating::Encrypt(string plainText, int key) {
//
//	textToUpper(plainText);
//
//	for (int i = 0; i < size(plainText); i++)
//	{
//		int index = allAlphabet.find(plainText[i]);
//		plainText[i] = allAlphabet[(index + keyValue) % 26];
//	}
//	return plainText;
//}
//
//
//string VigenereRepeating::Decrypt(string cipherText, int key) {
//	textToUpper(EncryptedText);
//	for (int i = 0; i < size(EncryptedText); i++)
//	{
//		int index = allAlphabet.find(EncryptedText[i]);
//		EncryptedText[i] = allAlphabet[mod(index - keyValue, 26)];
//	}
//	return EncryptedText;
//}
//
//
//
//string VigenereRepeating::Analyse(string plainText, string cipherText) {
//
//	string DecryptedText = EncryptedText;
//
//	textToUpper(EncryptedText);
//
//	for (int j = 0; j <= 15; j++) {
//
//		for (int i = 0; i < size(EncryptedText); i++)
//		{
//			int index = allAlphabet.find(EncryptedText[i]);
//			DecryptedText[i] = allAlphabet[mod(index - j, 26)];
//		}
//		cout << " at key  = " << j << "	Result is : " << DecryptedText << endl;
//
//	}
//
//}