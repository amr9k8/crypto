// crypto.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "CaeserCipher.h"
#include "MonoCipher.h"
#include "PlayFair.h"
#include "coloumnar.h"
#include "railfence.h"
#include "VigenereAuto.h"
#include "VigenereRepeating.h"
#include "hillcipher.h"
#include "DesDecryption.h"
#include "AES.h";
#include "RSA.h";
#include "MD5_Final.h";

using namespace std;

void coloumnarr() {
	coloumnar coloumnarobject;
	string pt;
	int key_fn[100];

	list<int> key_elements;
	list<int>::iterator ite;
	string cipher;
	int choice;
	cout << "\t\t\t\t\t\tCOLUMNAR \n\n";

	cout << "[1]Encryption\n[2]Decryption\n[3]Analysis\n";
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << "Plain Text : ";
		getline(cin >> ws, pt);
		cout << "num of key elements : ";
		cin >> coloumnarobject.key_numOf_Eelemnts;
		cout << "elements :";
		for (int i = 0; i < coloumnarobject.key_numOf_Eelemnts; i++)
		{
			cin >> key_fn[i];
			cin.ignore();
		}
		cipher = coloumnarobject.Encrypt(pt, key_fn);
		cout << cipher << "\n\n";
		pt.clear();
		cipher.clear();
		break;

	case 2:
		cout << "Cipher Text : ";
		getline(cin >> ws, cipher);
		cout << "num of key elements : ";
		cin >> coloumnarobject.key_numOf_Eelemnts;
		cout << "elements :";
		for (int i = 0; i < coloumnarobject.key_numOf_Eelemnts; i++)
		{
			cin >> key_fn[i];
		}
		pt = coloumnarobject.Decrypt(cipher, key_fn);
		cout << pt << "\n\n";
		pt.clear();
		cipher.clear();
		break;

	case 3:
		cout << "Plain Text : ";
		getline(cin >> ws, pt);
		cout << "Cipher Text : ";
		getline(cin >> ws, cipher);
		key_elements = coloumnarobject.analyse(pt, cipher);
		cout << "Key : ";
		for (ite = key_elements.begin(); ite != key_elements.end(); ite++)
		{
			cout << *ite << " ";
		}
		cout << "\n";
		pt.clear();
		cipher.clear();
		break;

	default:
		cout << "Invalid Choice";
	}

}
void caeser() {
	CaeserCipher caeserObject;
	string name;
	string cipher;
	int key_val = 0;
	int c = 1;
	cout << " \t\t \t ____________________________________________________________" << endl;
	cout << endl << " \t\t \t\t  # Caeser Cipher " << endl;
	cout << " \t\t \t ____________________________________________________________" << endl;
	while (c < 5) {
		cout << endl << endl << endl;
		cout << " 1) Encrypt Text " << endl;
		cout << " 2) Decrypt Text with known key " << endl;
		cout << " 3) Decrypt Text without key " << endl;
		cout << " 4) Cryptanalysis " << endl;
		cout << " 5) Exit " << endl;
		cin >> c;
		switch (c)
		{

		case 1:
			cout << "enter text to encrypt" << endl;
			cin.ignore();
			getline(cin, name);
			cout << endl << "enter key value" << endl;
			cin >> key_val;
			cout << caeserObject.EncryptCaeser(name, key_val);
			break;
		case 2:
			cout << "enter text to decrypt" << endl;
			cin.ignore();
			getline(cin, name);
			cout << endl << "enter key value" << endl;
			cin >> key_val;
			cout << caeserObject.DecryptCaeser(name, key_val);
			break;
		case 3:
			cout << "enter text to decrypt using bruteforce method" << endl;
			cin.ignore();
			getline(cin, name);
			caeserObject.bruteforceCaeser(name);
			break;
		case 4:
			cout << "enter plain text" << endl;
			getline(cin >> ws, name);
			cout << "ciphertext" << endl;
			getline(cin >> ws, cipher);
			key_val = caeserObject.cryptanalysis(cipher, name);
			cout << "Key is:" << key_val;
			break;
		}

	}

	//name = "Computer";
	//key_val = 8;
	//string encryptedtext = EncryptCaeser(name, key_val);

	//cout << "Encrypted Value of Computer : " << encryptedtext << endl;
	//cout << "Decrypted  Value of kwuxcbmz : " << DecryptCaeser(encryptedtext, key_val) << endl;
	//cout << "bruteforcing test : " << endl << endl;
	//bruteforceCaeser(encryptedtext);

	////cout << DecryptCaeser(name, key_val);
}
void monocipher() {

	MonoCipher monoObject;
	string alphabet;
	string plaintext;
	int c = 1;
	cout << " \t\t \t ____________________________________________________________" << endl;
	cout << endl << " \t\t \t\t  # Monoalphabetic Cipher " << endl;
	cout << " \t\t \t ____________________________________________________________" << endl;
	while (c < 4) {
		cout << endl << endl << endl;
		cout << " 1) Encrypt Text " << endl;
		cout << " 2) Decrypt Text with known key " << endl;
		cout << " 3) AnalyseUsingCharFrequency " << endl;
		cout << " 4) Exit " << endl;
		cin >> c;
		switch (c)
		{

		case 1:
			cout << "enter text to encrypt" << endl;
			cin.ignore();
			getline(cin, plaintext);
			cout << endl << "enter alphabitcs" << endl;
			cin >> alphabet;
			cout << monoObject.encrypt(plaintext, alphabet);
			break;
		case 2:
			cout << "enter text to decrypttt" << endl;
			cin.ignore();
			getline(cin, plaintext);
			cout << endl << "enter alphabitcs" << endl;
			cin >> alphabet;
			cout << plaintext << endl << alphabet << endl;
			cout << monoObject.decrypt(plaintext, alphabet);
			break;
		case 3:
			cout << "enter ciphertext to AnalyseUsingCharFrequency " << endl;
			cin >> plaintext;
			monoObject.AnalyseUsingCharFrequency(plaintext);
			break;
		}

	}

}
void playFair() {

	string plain_text;
	string cipher_text;
	PlayFair playfairObject;
	int choice = 0;
	string key_f;
	cout << "\t\t\t\t\t\tPLAYFAIR Algorithm\n";
	cout << "[1]Encryption \n" << "[2]Decryption \n";
	cout << "Enter the choice : ";
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << "enter the key : ";
		cin >> key_f;
		playfairObject.create_matrix(key_f);
		cout << "enter the plaintext : ";
		cin >> plain_text;
		playfairObject.encrypt(plain_text);
		break;

	case 2:
		cout << "enter the key : ";
		cin >> key_f;
		playfairObject.create_matrix(key_f);
		cout << "enter the ciphertext : ";
		cin >> cipher_text;
		playfairObject.decrypt(cipher_text);
		break;

	default:
		cout << "invalid num \n";
	}
}
void railfnc() {
	railfence railfenceobject;
	string plain_txt;
	string cipher_txt;
	int key;//rows
	cout << "\t\t\t\t\t\tRAIL FENCE ENCRYPTION\n\n";
	int choice;
	cout << "[1]Encryption\n[2]Decryption\n[3]Analysis\n";
	cin >> choice;
	switch (choice)
	{

	case 1:
		cout << "\nENCODER\n" << "Enter Plain Text: ";
		getline(cin >> ws, plain_txt);
		cout << "Enter Key: ";
		cin >> key;
		cipher_txt = railfenceobject.Encrypt_RainFence(plain_txt, key);
		cout << "Cipher Text: " << cipher_txt << endl;
		cipher_txt.clear();
		break;

	case 2:
		cout << "\nDECODER\n";
		cout << "Enter Cipher Text: ";
		getline(cin >> ws, cipher_txt);
		cout << "Enter Key: ";
		cin >> key;
		plain_txt = railfenceobject.Decrypt_RainFence(cipher_txt, key);
		cout << "Plain Text: " << plain_txt << endl;
		plain_txt.clear();
		break;

	case 3:

		cout << "\nANALYSIS\n";
		cout << "Enter Plain Text: ";
		getline(cin >> ws, plain_txt);
		cout << "Enter Cipher Text: ";
		getline(cin >> ws, cipher_txt);
		key = railfenceobject.Analyse_RainFence(plain_txt, cipher_txt);
		cout << "Key is: " << key << endl;
		plain_txt.clear();
		cipher_txt.clear();
		break;

	default:
		cout << "Invalid Choice";
	}
}
void vnigeneauto() {
	VigenereAuto VigenereAutoObject;
	string name;
	string key;
	int c = 1;
	//cout << VigenereAutoObject.Encrypt("computer", "hello") << endl;
	//cout << VigenereAutoObject.Decrypt("JSXAIVSD", "hellocom") << endl;
	//cout << VigenereAutoObject.Analyse("computer", "JSXAIVSD") << endl;


	//cout << VigenereRepeatingobj.Decrypt("JSXAIVSD", "hellohel") << endl;
	//cout << VigenereRepeatingobj.Analyse("computer", "JSXAIAIC") << endl;

	cout << " \t\t \t ____________________________________________________________" << endl;
	cout << endl << " \t\t \t\t  # Vigenere Auto Key Cipher " << endl;
	cout << " \t\t \t ____________________________________________________________" << endl;
	while (c < 4) {
		cout << endl << endl << endl;
		cout << " 1) Encrypt" << endl;
		cout << " 2) Decrypt" << endl;
		cout << " 3) Analysis " << endl;
		cout << " 4) Exit " << endl;
		cin >> c;
		switch (c)
		{

		case 1:
			cout << "enter text to encrypt" << endl;
			cin.ignore();
			getline(cin, name);
			cout << endl << "enter key " << endl;
			cin >> key;
			cout << VigenereAutoObject.Encrypt(name, key) << endl;
			break;
		case 2:
			cout << "enter text to decrypt" << endl;
			cin.ignore();
			getline(cin, name);
			cout << endl << "enter key value" << endl;
			cin >> key;
			cout << VigenereAutoObject.Decrypt(name, key) << endl;
			break;
		case 3:
			cout << "enter text" << endl;
			cin.ignore();
			getline(cin, name);
			cout << endl << "enter cipher text" << endl;
			cin >> key;
			cout << VigenereAutoObject.Analyse(name, key) << endl;
			break;
		}

	}

	//name = "Computer";
	//key_val = 8;
	//string encryptedtext = EncryptCaeser(name, key_val);

	//cout << "Encrypted Value of Computer : " << encryptedtext << endl;
	//cout << "Decrypted  Value of kwuxcbmz : " << DecryptCaeser(encryptedtext, key_val) << endl;
	//cout << "bruteforcing test : " << endl << endl;
	//bruteforceCaeser(encryptedtext);

	////cout << DecryptCaeser(name, key_val);
}
void vnigenererepeat() {
	VigenereRepeating VigenereRepeatingobj;
	string name;
	string key;
	int key_val = 0;
	int c = 1;
	//cout << VigenereAutoObject.Encrypt("computer", "hello") << endl;
	//cout << VigenereAutoObject.Decrypt("JSXAIVSD", "hellocom") << endl;
	//cout << VigenereAutoObject.Analyse("computer", "JSXAIVSD") << endl;


	//cout << VigenereRepeatingobj.Decrypt("JSXAIVSD", "hellohel") << endl;
	//cout << VigenereRepeatingobj.Analyse("computer", "JSXAIAIC") << endl;

	cout << " \t\t \t ____________________________________________________________" << endl;
	cout << endl << " \t\t \t\t  # Vigenere Repeating Key Cipher " << endl;
	cout << " \t\t \t ____________________________________________________________" << endl;
	while (c < 4) {
		cout << endl << endl << endl;
		cout << " 1) Encrypt" << endl;
		cout << " 2) Decrypt" << endl;
		cout << " 3) Analysis " << endl;
		cout << " 4) Exit " << endl;
		cin >> c;
		switch (c)
		{

		case 1:
			cout << "enter text to encrypt" << endl;
			cin.ignore();
			getline(cin, name);
			cout << endl << "enter key " << endl;
			cin >> key;
			cout << VigenereRepeatingobj.Encrypt(name, key) << endl;
			break;
		case 2:
			cout << "enter text to decrypt" << endl;
			cin.ignore();
			getline(cin, name);
			cout << endl << "enter key value" << endl;
			cin >> key;
			cout << VigenereRepeatingobj.Decrypt(name, key) << endl;
			break;
		case 3:
			cout << "enter text" << endl;
			cin.ignore();
			getline(cin, name);
			cout << endl << "enter cipher text" << endl;
			cin >> key;
			cout << VigenereRepeatingobj.Analyse(name, key) << endl;
			break;
		}

	}

	//name = "Computer";
	//key_val = 8;
	//string encryptedtext = EncryptCaeser(name, key_val);

	//cout << "Encrypted Value of Computer : " << encryptedtext << endl;
	//cout << "Decrypted  Value of kwuxcbmz : " << DecryptCaeser(encryptedtext, key_val) << endl;
	//cout << "bruteforcing test : " << endl << endl;
	//bruteforceCaeser(encryptedtext);

	////cout << DecryptCaeser(name, key_val);
}
void hillcipherd() {
	hillcipher hillcipherobj;
	int task = 0;
	cout << " \t\t \t ____________________________________________________________" << endl;
	cout << endl << " \t\t \t\t  # Hill Cipher  " << endl;
	cout << " \t\t \t ____________________________________________________________" << endl;
	cout << "1- Analysis of 2*2 key sized cipher" << endl << "2- Analysis of 3*3 key sized cipher" << endl << "3- Encrypt using hill cipher" << endl << "4- Decrypt hill cipher" << endl;
	cout << "choose a task: ";
	cin >> task;
	cout << endl;
	if (task == 1)
	{
		list <int> plain;
		list <int> cipher;
		cout << "enter -1 to end input \n";
		cout << "enter plain text";
		int num;
		while ((cin >> num) && num != -1) {
			plain.push_back(num);
		}
		cout << "enter cipher text";
		while ((cin >> num) && num != -1) {
			cipher.push_back(num);
		}
		if (plain.size() < 4 || cipher.size() < 4)
		{
			cout << "size of both cipher and plain text has to be at least 4 to break encryption";
			exit(0);
		}
		list <int> key;
		key = hillcipherobj.analyse(plain, cipher);
	}
	else if (task == 2)
	{
		list <int> plain;
		list <int> cipher;
		cout << "enter -1 to end input \n";
		cout << "enter plain text";
		int num;
		while ((cin >> num) && num != -1) {
			plain.push_back(num);
		}
		cout << "enter cipher text";
		while ((cin >> num) && num != -1) {
			cipher.push_back(num);
		}
		if (plain.size() < 9 || cipher.size() < 9)
		{
			cout << "size of both cipher and plain text has to be at least 9 to break encryption";
			exit(0);
		}
		hillcipherobj.analyse3by3(plain, cipher);
	}
	else if (task == 3)
	{
		/*
		list <int> plain;
		list <int> key;
		int k[] = { 17,17,5 ,21,18,21,2,2,19 };
		int p[] = {15,12,4,13,0,14,12,4,24,17,14,24};
		int i = 0;
		while (i < 9)
		{
			key.push_back(k[i]);
			i++;
		}
		i = 0;
		while (i < 12)
		{
			plain.push_back(p[i]);
			i++;
		}
		encrypt(plain, key);
		*/
		list <int> plain;
		list <int> key;
		cout << "enter -1 to end input \n";
		cout << "enter plain text: ";
		int num;
		while ((cin >> num) && num != -1) {
			plain.push_back(num);
		}
		cout << "enter key text: ";
		while ((cin >> num) && num != -1) {
			key.push_back(num);
		}
		hillcipherobj.encrypt(plain, key);
	}
	else if (task == 4)
	{
		/*
		list <int> cipher;
		list <int> key;
		int k[] = { 7,8,19,3};
		int c[] = {15,2,16,5};
		int i = 0;
		while (i < 4)
		{
			key.push_back(k[i]);
			i++;
		}
		i = 0;
		while (i < 4)
		{
			cipher.push_back(c[i]);
			i++;
		}
		decrypt(cipher, key);
		*/
		list <int> cipher;
		list <int> key;
		cout << "Enter -1 to end input \n";
		cout << "Enter cipher text: ";
		int num;
		while ((cin >> num) && num != -1) {
			cipher.push_back(num);
		}
		cout << "Enter key : ";
		while ((cin >> num) && num != -1) {
			key.push_back(num);
		}
		list <int> plain;
		plain = hillcipherobj.decrypt(cipher, key);
	}
}
string checktext(string input) {

	if (input.size() < 8) {
		for (int i = 0; i < 8 - input.size(); i++)
		{
			input += "0";
		}
		return input;
	}


	else if (input.size() > 8) {
		cout << " please enter 8 characters only";
		abort();
		return "0";
	}

}
void desDecryption() {
	
	int c = 1;
	cout << " \t\t \t ____________________________________________________________" << endl;
	cout << endl << " \t\t \t\t  # Des  Cipher " << endl;
	cout << " \t\t \t ____________________________________________________________" << endl;
	while (c < 4) 
	{
		DesDecryption  DesDecryptionobject;
		string string_input = "";
		string string_key = "";
		string res = "";
		cout << endl << endl << endl;
		cout << " 1) Encrypt" << endl;
		cout << " 2) Decrypt" << endl;
		cout << " 4) Exit " << endl;
		cin >> c;
		switch (c)
		{

		case 1:
			cout << "Enter the plain text (beginning with \"0x\") :" << endl;
			getline(cin >> ws, string_input);
			cout << endl << "Enter key (beginning with \"0x\") :" << endl;
			getline(cin >> ws, string_key);
			cout << endl;
			res = DesDecryptionobject.Encrypt(string_input, string_key);
			if (res != "")
			{
				cout << "\nENCRYPTED TEXT :   \n";
				cout << endl << res << endl;
			}
			break;
		case 2:

			cout << "Enter the cipher text (beginning with \"0x\") : " << endl;
			cin.ignore();
			getline(cin, string_input);
			cout << endl << "Enter key (beginning with \"0x\") : " << endl;
			getline(cin >> ws, string_key);
			cout << endl;
			res = DesDecryptionobject.Decrypt(string_input, string_key);
			if (res != "")
			{
				cout << "\nDECRYPTED TEXT : \n";
				cout << res << endl;
			}
			break;
		}

	}
}
void AES_func()
{
	AES obj;
	string initial_key;
	string plain;
	string cipher;


	int c = 1;

	while (c < 3)
	{
		cout << " \t\t \t ____________________________________________________________" << endl;
		cout << endl << " \t\t \t\t            # AES " << endl;
		cout << " \t\t \t ____________________________________________________________" << endl;
		cout << endl << endl;
		cout << " 1) Encrypt" << endl;
		cout << " 2) Decrypt" << endl;
		cout << " 3) Exit " << endl;
		cin >> c;
		switch (c)
		{
		case 1:
			cout << endl << "Enter the plain text (beginning with \"0x\") :" << endl;
			getline(cin >> ws, plain);
			cout << "Enter the initial key (beginning with \"0x\") :" << endl;
			getline(cin >> ws, initial_key);
			cipher = obj.AES_Final_ENC(plain, initial_key);
			if (cipher != "")
			{
				cout << endl << "Cipher text : " << cipher << endl;
			}
			break;
		case 2:
			cout << endl << "Enter the cipher text (beginning with \"0x\") : " << endl;
			getline(cin >> ws, cipher);
			cout << "Enter the initial key (beginning with \"0x\") : " << endl;
			getline(cin >> ws, initial_key);
			string plainx = obj.AES_Decrypt(cipher, initial_key);
			if (plainx != "")
			{
				cout << endl << "Plain text : " << plainx << endl;
			}

		}

	}
}


// need cin and cout  //cin , cout	//cin , cout
void RSAfunc()
{

	int c = 1;

	while (c < 3)
	{
		RSA RSAObject;
		int p, q, M, e, C;
		cout <<endl<< " \t\t \t ____________________________________________________________" << endl;
		cout << endl << " \t\t \t\t  # RSA " << endl;
		cout << " \t\t \t ____________________________________________________________" << endl;
		cout << endl << endl;
		cout << " 1) Encrypt  " << endl;
		cout << " 2) Decrypt " << endl;
		cout << " 3) Exit " << endl;
		cin >> c;
		switch (c)
		{

		case 1:
			cout << "Please enter the value of p " << endl;
			cin >> p;
			cout << "Please enter the value of q " << endl;
			cin >> q;
			cout << "Please enter the value of M " << endl;
			cin >> M;
			cout << "Please enter the value of e" << endl;
			cin >> e;
			C = RSAObject.Encrypt(p, q, M, e);
			if (C != 0)
			{
				cout << "The Cipher is : " << C << endl;
			}
			break;
		case 2:
			cout << "Please enter the value of p " << endl;
			cin >> p;
			cout << "Please enter the value of q " << endl;
			cin >> q;
			cout << "Please enter the value of C " << endl;
			cin >> C;
			cout << "Please enter the value of e" << endl;
			cin >> e;
			int M = RSAObject.Decrypt(p, q, C, e);
			if (M != 0)
			{
				cout << "The Plain text is : " << M << endl;
			}
			
			break;
		}
	}
}

/*	RSA RSAObject;
	int C = RSAObject.Encrypt(3, 11, 2, 7);
	int M = RSAObject.Decrypt(3, 11, C, 7);
	cout << C << endl << M;
	*/
	//cin , cout		//cin , cout

void MD5func()
{
	MD5_final MD5_object;
	int c = 0;
	string plain;
	string hash;

	while (c < 2) {
		cout << " \t\t \t ____________________________________________________________" << endl;
		cout << endl << " \t\t \t\t  # MD5 " << endl;
		cout << " \t\t \t ____________________________________________________________" << endl;
		cout << endl << endl;
		cout << " 1) Hash  " << endl;
		cout << " 2) Exit " << endl;
		plain.clear();
		hash.clear();
		cin >> c;
		switch (c)
		{
		case 1:
			cout << "Please enter plaintext " << endl;
			MD5_final MD5_object;
			getline(cin >> ws, plain);
			hash = MD5_object.MD5_Hash(plain);
			cout << "MD5 Hash :" << hash << endl;
			break;
		}
	}
}

void menu()
{
	cout << endl;
	cout << "Cryptographic algorithms: " << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "1-Ceaser cipher \n2-Monoalphabetic cipher \n3-Playfair \n4-Vigener auto key \n5-Vigener repeating key \n6-Railfence \n7-Columnar \n8-Hill cipher \n9-DES \n10-AES \n11-RSA \n12-MD5 \n13-Exit " << endl;
}
int main()
{
	int choice;

	do {

		menu();
		cout << "Enter the number of the choice that you want : \n";
		cin >> choice;

		switch (choice) {
		case 1:
			caeser();
			break;
		case 2:
			monocipher();
			break;
		case 3:
			playFair();
			break;
		case 4:
			vnigeneauto();

			break;
		case 5:
			vnigenererepeat();
			break;
		case 6:
			railfnc();
			break;
		case 7:
			coloumnarr();
			break;
		case 8:
			hillcipherd();
			break;
		case 9:
			desDecryption();
			break;
		case 10:
			AES_func();
			break;
		case 11:
			RSAfunc();
			break;
		case 12:
			MD5func();
			break;
		case 13:
			exit(0);
		default:
			cout << "Invalid choice please choose number from 1 to 13" << endl;
		}

	} while (choice != 13);

	return 0;
}
