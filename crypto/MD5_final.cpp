#include "MD5_final.h"
#include <iostream>
#include <bitset>
#include <string>
#include <algorithm>
#include <iterator>
#include <list>
#include<array> 
#include <sstream>
#include <stdio.h>

using namespace std;


//constants
uint32_t IV[4] = { 0x67452301 , 0xEFCDAB89 ,0x98BADCFE,0x10325476 };
//Little Endian { 0x67452301 , 0xEFCDAB89 ,0x98BADCFE,0x10325476};
//Big Endian { 0x01234567 , 0x89ABCDEF ,0xFEDCBA98,0x76543210};

uint32_t IV_old[4] = { 0x67452301 , 0xEFCDAB89 ,0x98BADCFE,0x10325476 };

int index_x_r2[16] = { 1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12 };
int index_x_r3[16] = { 5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2 };
int index_x_r4[16] = { 0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9 };

uint32_t T[64] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
					0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
					0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
					0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
					0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
					0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
					0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
					0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
					0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
					0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
					0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
					0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
					0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
					0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
					0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
					0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };


//msg into blocks
string MD5_final:: str_to_bin(string input)
{
	string bin;
	bitset<8> temp;
	for (int i = 0; i < input.length(); i++)
	{
		temp = input[i];
		/*cout << temp << " ";*/
		bin.append(temp.to_string());
	}
	return bin;
}
string MD5_final:: str_padded_to_448(string input, int& size)
{
	int counter = 0;
	for (int i = 0; i < input.length(); i++)
	{
		counter++;
	}
	size = counter;
	if ((counter + 64) % 512 != 0)
	{
		input.append("1");
		counter++;
	}
	while ((counter + 64) % 512 != 0)
	{
		input.append("0");
		counter++;
	}
	return input;
}
string MD5_final:: add_length(string input, int size)
{
	string binary = bitset<64>(size).to_string();
	//cout << endl << binary << endl;
	while (binary.length() != 64)
	{
		binary.insert(0, "0");
	}
	input.append(binary);
	return input;
}

//start of hashing round
string MD5_final:: decToHexa(uint32_t n)
{
	// ans string to store hexadecimal number
	string ans = "";

	while (n != 0) {
		// remainder variable to store remainder
		int rem = 0;

		// ch variable to store each character
		char ch;
		// storing remainder in rem variable.
		rem = n % 16;

		// check if temp < 10
		if (rem < 10) {
			ch = rem + 48;
		}
		else {
			ch = rem + 55;
		}

		// updating the ans string with the character variable
		ans += ch;
		n = n / 16;
	}

	// reversing the ans string to get the final result
	int i = 0, j = ans.size() - 1;
	while (i <= j)
	{
		swap(ans[i], ans[j]);
		i++;
		j--;
	}
	return ans;
}
uint32_t MD5_final:: G_function(uint32_t b, uint32_t c, uint32_t d, int r)
{
	int part1, part2, result;
	switch (r)
	{
	case 1:
		//F
		part1 = IV[1] & IV[2];
		part2 = (~IV[1]) & IV[3];
		result = part1 | part2;
		break;

	case 2:
		//G
		part1 = IV[1] & IV[3];
		part2 = IV[2] & (~IV[3]);
		result = part1 | part2;
		break;

	case 3:
		//H
		part1 = IV[1] ^ IV[2];
		result = part1 ^ IV[3];
		break;

	case 4:
		//I
		part2 = IV[1] | (~IV[3]);
		result = IV[2] ^ part2;
		break;
	}

	return result;
}
void MD5_final:: block_to_32bits(string block_512, string block_32bits[16], int round, bool last_block)
{
	int counter = 0;
	bool length_32 = false;
	for (int i = 0; i < 512; i++)
	{
		if (i % 32 == 0 && i != 0)
		{
			counter++;
			length_32 = true;

		}
		else
		{
			if (length_32 == true)
			{
				i = i - 1;
				length_32 = false;
			}
			block_32bits[counter] += block_512[i];
			//cout << simple[0];
		}

	}
	if (last_block == true)
	{
		string temp_X;
		temp_X = block_32bits[15];
		block_32bits[15].clear();
		block_32bits[15] = block_32bits[14];
		block_32bits[14].clear();
		block_32bits[14] = littleEndian32Bits(temp_X);
		temp_X.clear();
	}



	string temp_blocks[16];
	if (round > 1)
	{

		for (int i = 0; i < 16; i++)
		{
			temp_blocks[i] = block_32bits[i];
			block_32bits[i].clear();
		}
	}
	//M1, M6, M11, M0, M5, M10, M15, M4, M9, M14, M3, M8, M13, M2, M7, M12
	if (round == 2)
	{
		for (int i = 0; i < 16; i++)
		{
			block_32bits[i] = temp_blocks[index_x_r2[i]];
			//cout << "Round_2 K(X): " << index_x_r2[i] << endl;
		}

		for (int i = 0; i < 16; i++)
		{
			temp_blocks[0].clear();
		}
	}

	//M5, M8, M11, M14, M1, M4, M7, M10, M13, M0, M3, M6, M9, M12, M15, M2
	else if (round == 3)
	{
		for (int i = 0; i < 16; i++)
		{
			block_32bits[i] = temp_blocks[index_x_r3[i]];
			//cout << "Round_3 K(X): " << index_x_r3[i] << endl;
		}

		for (int i = 0; i < 16; i++)
		{
			temp_blocks[0].clear();
		}
	}

	//M0, M7, M14, M5, M12, M3, M10, M1, M8, M15, M6, M13, M4, M11, M2, M9
	else if (round == 4)
	{
		for (int i = 0; i < 16; i++)
		{
			block_32bits[i] = temp_blocks[index_x_r4[i]];
			//cout << "Round_4 K(X): " << index_x_r4[i] << endl;
		}

		for (int i = 0; i < 16; i++)
		{
			temp_blocks[0].clear();
		}
	}


	/*for (int i = 0; i < 16; i++)
	{
		cout << "block " << i << " is: " << block_32bits[i] << endl;
	}*/


}
void MD5_final:: shifting(int bits[], int num_shifts)
{
	//cout << "Number of Shifts:" << num_shifts << endl;
	int temp;
	int i = 0;
	for (int j = 0; j < num_shifts; j++)
	{
		temp = bits[0];
		i = 0;
		for (; i < 32; i++)
		{
			bits[i] = bits[i + 1];
		}
		bits[i - 1] = temp;
	}

}
void MD5_final:: CLS(int s_round, int bits[])
{
	if (s_round == 1 || s_round == 5 || s_round == 9 || s_round == 13)
	{
		shifting(bits, 7);
	}
	else if (s_round == 2 || s_round == 6 || s_round == 10 || s_round == 14)
	{
		shifting(bits, 12);
	}
	else if (s_round == 3 || s_round == 7 || s_round == 11 || s_round == 15)
	{
		shifting(bits, 17);
	}
	else if (s_round == 4 || s_round == 8 || s_round == 12 || s_round == 16)
	{
		shifting(bits, 22);
	}
	else if (s_round == 17 || s_round == 21 || s_round == 25 || s_round == 29)
	{
		shifting(bits, 5);
	}
	else if (s_round == 18 || s_round == 22 || s_round == 26 || s_round == 30)
	{
		shifting(bits, 9);
	}
	else if (s_round == 19 || s_round == 23 || s_round == 27 || s_round == 31)
	{
		shifting(bits, 14);
	}
	else if (s_round == 20 || s_round == 24 || s_round == 28 || s_round == 32)
	{
		shifting(bits, 20);
	}
	else if (s_round == 33 || s_round == 37 || s_round == 41 || s_round == 45)
	{
		shifting(bits, 4);
	}
	else if (s_round == 34 || s_round == 38 || s_round == 42 || s_round == 46)
	{
		shifting(bits, 11);
	}
	else if (s_round == 35 || s_round == 39 || s_round == 43 || s_round == 47)
	{
		shifting(bits, 16);
	}
	else if (s_round == 36 || s_round == 40 || s_round == 44 || s_round == 48)
	{
		shifting(bits, 23);
	}
	else if (s_round == 49 || s_round == 53 || s_round == 57 || s_round == 61)
	{
		shifting(bits, 6);
	}
	else if (s_round == 50 || s_round == 54 || s_round == 58 || s_round == 62)
	{
		shifting(bits, 10);
	}
	else if (s_round == 51 || s_round == 55 || s_round == 59 || s_round == 63)
	{
		shifting(bits, 15);
	}
	else if (s_round == 52 || s_round == 56 || s_round == 60 || s_round == 64)
	{
		shifting(bits, 21);
	}
}
uint32_t MD5_final:: binary_dec(int arr_bin[], int size)
{
	string decimal = "";
	for (int i = 0; i < size; i++)
	{
		//cout << bits[counter];
		if (arr_bin[i] == 1)
		{
			decimal += '1';
		}
		else
		{
			decimal += '0';
		}
	}
	bitset<32> bits_1(decimal);
	uint32_t dec = bits_1.to_ulong();
	return dec;
}
void MD5_final:: binary_str_to_binary_int_arr(string binary, int ret_bin_arr[], int size)
{

	for (int i = 0; i < size; i++)
	{
		if (binary[i] == '0')
		{
			ret_bin_arr[i] = 0;
		}
		else
		{
			ret_bin_arr[i] = 1;
		}
	}
}


//16 Times
string MD5_final:: repeated_16(string block_512, int round, bool last_block)
{
	string hash_val = "";
	string X_single_block_32bits[16];
	block_to_32bits(block_512, X_single_block_32bits, round, last_block);



	string X_temp[16];
	for (int i = 0; i < 16; i++)
	{
		X_temp[i] = littleEndian32Bits(X_single_block_32bits[i]);
		X_single_block_32bits[i].clear();
		X_single_block_32bits[i] = X_temp[i];
		X_temp[i].clear();
		//cout << "block after little " << i << " is: " << X_single_block_32bits[i] << endl;
	}


	int counter_temp = 0;
	//T[Counter_temp]
	if (round == 2)
	{
		counter_temp = 16;
	}
	else if (round == 3)
	{
		counter_temp = 32;
	}
	else if (round == 4)
	{
		counter_temp = 48;
	}

	for (int i = 0; i < 16; i++)
	{
		//cout << "i is:" << i << endl << " A : " << IV[0] << endl << "B :" << IV[1] << endl << "C :" << IV[2] << endl << "D : " << IV[3] << endl;
		//cout << endl << "num of repeated: " << i << endl;
		uint32_t g = G_function(IV[1], IV[2], IV[3], round);
		//cout << "g func is: " << g << endl;

		uint32_t Sum_AG = (IV[0] + g) % 4294967296;//mod 2^32
		//cout << "A + G= " << Sum_AG << endl;

		//x(k):from string(binary)-->decimal
		int X_bin[32];
		binary_str_to_binary_int_arr(X_single_block_32bits[i], X_bin, 32);
		//cout << "X from string to arr: ";
		/*for (int i = 0; i < 32; i++)
		{
			cout << X_bin[i];
		}*/
		//cout << endl;
		uint32_t X_decimal = binary_dec(X_bin, 32);
		//cout << "X in decimal: " << X_decimal << endl;

		//sum x+AG
		uint32_t Sum_XAG = (Sum_AG + X_decimal) % 4294967296;
		//cout << "X+AG: " << Sum_XAG << endl;

		//sum T+XAG
		uint32_t Sum_TXAG = (T[counter_temp] + Sum_XAG) % 4294967296;
		//cout << "T " << counter_temp << ":" << T[counter_temp] << endl;
		//cout << "T+XAG: " << Sum_TXAG << endl;


		// circular left shift
		int s_round = counter_temp + 1;
		//cout << "S_Round: " << s_round << endl;
		//to store g in arr
		bitset<32> reversed = Sum_TXAG;
		int bits_Sum_TXAG[32];
		int counter = 0;
		for (int i = 31; i >= 0; i--)
		{
			bits_Sum_TXAG[counter] = reversed[i];
			counter++;
		}
		//cout << endl << "before shifting: ";
		/*for (int i = 0; i < 32; i++)
		{
			cout << bits_Sum_TXAG[i];
		}*/
		//cout << endl;
		//CLS
		CLS(s_round, bits_Sum_TXAG);

		/*cout << "after shifting: ";
		for (int i = 0; i < 32; i++)
		{
			cout << bits_Sum_TXAG[i];
		}*/
		//cout << endl;
		uint32_t dec_after_CLS;
		dec_after_CLS = binary_dec(bits_Sum_TXAG, 32);
		//cout << "decimal after shifting: " << dec_after_CLS << endl;

		uint32_t Sum_B_TXAG = (IV[1] + dec_after_CLS) % 4294967296;
		//cout << "B+TXAG: " << Sum_B_TXAG << endl;

		IV[0] = IV[3];
		IV[3] = IV[2];
		IV[2] = IV[1];
		IV[1] = Sum_B_TXAG;
		counter_temp++;
		/*char ll = 'A';
		for (int i = 0; i < 4; i++)
		{
			cout << ll << ":" << IV[i] << endl;
			ll++;

		}*/

		string hex_IV;
		//ll = 'A';
		string temp = "";
		for (int i = 0; i < 4; i++)
		{
			hex_IV = decToHexa(IV[i]);
			int calc = 8 - hex_IV.length();
			//cout << "calc: " << calc << endl;
			for (int i = 0; i < calc; i++)
			{
				temp += "0";
			}
			temp += hex_IV;
			//cout << ll << " is: " << temp << endl;
			//ll++;
			temp.clear();
		}
		//cout << "-------------------------------------------" << endl;
	}

	//sum at the end
	if (round == 4)
	{
		for (int i = 0; i < 4; i++)
		{
			IV[i] = (IV_old[i] + IV[i]) % 4294967296;
		}

		if (last_block == true)
		{
			char letter = 'A';
			string hex_IV;
			for (int i = 0; i < 4; i++)
			{
				hex_IV = decToHexa(IV[i]);
				int calc = 8 - hex_IV.length();
				string temp = "";
				//cout << "calc: " << calc << endl;
				for (int i = 0; i < calc; i++)
				{
					hex_IV += "0";
				}
				letter++;
				hash_val += littleEndian_hex(hex_IV);
				temp = littleEndian_hex(hex_IV);

				////////////////////////////////////////////////////////////

				uint32_t IV_Hex;
				IV_Hex = HexToDec(temp);
				IV[i] = IV_Hex;
				/*cout <<"hex:"<< IV_Hex << endl;
				cout <<"IV:"<< IV[i] << endl;*/


				/////////////////////////////////////////////////////////////////////
				//letter++;

			}
		}


		//cout << "-------------------------------------------" << endl;
	}
	return hash_val;
}

//take each 32 bit
string MD5_final:: littleEndian32Bits(string str)
{
	string b1, b2, b3, b4;

	for (int i = 0; i < 32; i++) {
		if ((i >= 0) & (i < 8))
			b1 += str[i];
		if ((i >= 8) & (i < 16))
			b2 += str[i];
		if ((i >= 16) & (i < 24))
			b3 += str[i];
		if ((i >= 24) & (i < 32))
			b4 += str[i];
	}

	return b4 + b3 + b2 + b1;
}
string MD5_final:: littleEndian_hex(string str)
{
	string a1, a2, a3, a4;

	for (int i = 0; i < 8; i++)
	{
		if ((i >= 0) & (i < 2))
			a1 += str[i];
		if ((i >= 2) & (i < 4))
			a2 += str[i];
		if ((i >= 4) & (i < 6))
			a3 += str[i];
		if ((i >= 6) & (i < 8))
			a4 += str[i];
	}


	//b = HexToDec(all);
	//cout << "ABCD: " << all << endl;
	//cout << IV_Hex << endl;
	return a4 + a3 + a2 + a1;
}
uint32_t MD5_final:: HexToDec(string n)
{
	uint32_t ret_dec;
	istringstream iss(n);
	iss >> hex >> ret_dec;
	return ret_dec;
}

string MD5_final:: MD5_Hash(string plaintext)
{

	string str = str_to_bin(plaintext);
	int size = 0;
	string padded = str_padded_to_448(str, size);
	string final = add_length(padded, size);

	//separate into blocks
	int num_of_blocks = final.length() / 512;
	string* blocks = new string[num_of_blocks];
	for (int i = 0; i < num_of_blocks; i++)
	{
		for (int j = i * 512; j < 512 * (i + 1); j++)
		{
			blocks[i].push_back(final[j]);
		}
	}
	//string block_512 = blocks[0];
	//cout << block_512 << endl;
	//cout << "------------------------------------------------------------------" << endl;
	/*
		how to use dynamic array
		blocks are separated as follow => blocks[no.of.blocks]==>each element of array is string of size 512
		so when you want first block
		simply => string block1 = blocks[0]
	*/


	/*for (int i = 0; i < 16; i++)
	{
		cout << "X " << i << " is: " << X_single_block_32bits[i] << endl;
	}
	cout << "-------------------------------------------" << endl;*/
	//----------------G--------------------------
	//int round = 1;
	//cin >> round;
	bool last_block = false;
	string hash_val = "";
	for (int i = 0; i < num_of_blocks; i++)
	{
		if (i == (num_of_blocks - 1))
		{
			last_block = true;
		}
		string block_512 = blocks[i];
		for (int round_num = 1; round_num < 5; round_num++)
		{
			//cout << "ROUND: " << round_num << endl;
			hash_val = repeated_16(block_512, round_num, last_block);
		}

		for (int i = 0; i < 4; i++)
		{
			IV_old[i] = IV[i];
			//cout << "IV:" << decToHexa(IV[i]) << endl;
		}
	}



	/*int last_block = 0xFFF;
	cout << decToHexa(IV[0] + aa);*/
	delete[] blocks; // NEVER MOVE
	return hash_val;
}