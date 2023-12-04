#pragma once
#include<iostream>
#include <string>
using namespace std;
class AES
{
public:
	
	string rotation(string L_word);
	string sbox_pick(string L_word);
	string zerox_rem(string sb_word);
	string hex_to_bin(string sb_wrod);
	string xoring(string first, string second, int length);
	string bin_to_hex2(string key);
	void key_expansion(string key, int numOfround);


	string DEC_To_HEX(int dec);
	void shift_rows(int Matrix_sBox[4][4]);
	bool dectobinary(int decimal, int binaryArr[], int mult);
	void XoR_arr(int arr[], int arr2[], int size, int* ret_arr);
	string bin_to_hex(string key);
	string MIX_arr_calc(int temp_arr_mix[4], int S_Box[4][4]);
	string AES_Encrypt(string plaintext, string key);
	string Lastround_AES_Encrypt(string plaintext, string key);
	string Initial_XoR(string plain, string key);
	string first_time(string plain, string initial_key);
	string AES_Final_ENC(string plain, string initial_key);



	string AES_Decrypt(string cipher, string initial_key);
	void shift_rows_right(string Matrix_sBox[4][4]);
	void inv_sbox(string matrix[4][4]);
	void inv_mix_col(string matrix[4][4]);
	string shift2x(string arr);
	unsigned char inv0e(unsigned char b);
	unsigned char inv0d(unsigned char b);
	unsigned char inv09(unsigned char b);
	unsigned char inv0b(unsigned char b);
	unsigned char inv02(unsigned char b);
	
	bool Length_input(string txt, int size);
	bool Check_Hex(string txt);
};

