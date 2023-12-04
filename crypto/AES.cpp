#include "AES.h"
#include <iostream>
#include <iterator>
#include <list>
#include<array> 
#include <sstream>
#include <bitset>
#include <algorithm> 
#include <string> 
#include <bitset>
using namespace std;

string sbox[16][16] =
{
	"0x63","0x7c","0x77","0x7b","0xf2","0x6b","0x6f","0xc5","0x30","0x01","0x67","0x2b","0xfe","0xd7","0xab","0x76",
	"0xca","0x82","0xc9","0x7d","0xfa","0x59","0x47","0xf0","0xad","0xd4","0xa2","0xaf","0x9c","0xa4","0x72","0xc0",
	"0xb7","0xfd","0x93","0x26","0x36","0x3f","0xf7","0xcc","0x34","0xa5","0xe5","0xf1","0x71","0xd8","0x31","0x15",
	"0x04","0xc7","0x23","0xc3","0x18","0x96","0x05","0x9a","0x07","0x12","0x80","0xe2","0xeb","0x27","0xb2","0x75",
	"0x09","0x83","0x2c","0x1a","0x1b","0x6e","0x5a","0xa0","0x52","0x3b","0xd6","0xb3","0x29","0xe3","0x2f","0x84",
	"0x53","0xd1","0x00","0xed","0x20","0xfc","0xb1","0x5b","0x6a","0xcb","0xbe","0x39","0x4a","0x4c","0x58","0xcf",
	"0xd0","0xef","0xaa","0xfb","0x43","0x4d","0x33","0x85","0x45","0xf9","0x02","0x7f","0x50","0x3c","0x9f","0xa8",
	"0x51","0xa3","0x40","0x8f","0x92","0x9d","0x38","0xf5","0xbc","0xb6","0xda","0x21","0x10","0xff","0xf3","0xd2",
	"0xcd","0x0c","0x13","0xec","0x5f","0x97","0x44","0x17","0xc4","0xa7","0x7e","0x3d","0x64","0x5d","0x19","0x73",
	"0x60","0x81","0x4f","0xdc","0x22","0x2a","0x90","0x88","0x46","0xee","0xb8","0x14","0xde","0x5e","0x0b","0xdb",
	"0xe0","0x32","0x3a","0x0a","0x49","0x06","0x24","0x5c","0xc2","0xd3","0xac","0x62","0x91","0x95","0xe4","0x79",
	"0xe7","0xc8","0x37","0x6d","0x8d","0xd5","0x4e","0xa9","0x6c","0x56","0xf4","0xea","0x65","0x7a","0xae","0x08",
	"0xba","0x78","0x25","0x2e","0x1c","0xa6","0xb4","0xc6","0xe8","0xdd","0x74","0x1f","0x4b","0xbd","0x8b","0x8a",
	"0x70","0x3e","0xb5","0x66","0x48","0x03","0xf6","0x0e","0x61","0x35","0x57","0xb9","0x86","0xc1","0x1d","0x9e",
	"0xe1","0xf8","0x98","0x11","0x69","0xd9","0x8e","0x94","0x9b","0x1e","0x87","0xe9","0xce","0x55","0x28","0xdf",
	"0x8c","0xa1","0x89","0x0d","0xbf","0xe6","0x42","0x68","0x41","0x99","0x2d","0x0f","0xb0","0x54","0xbb","0x16"
};
string RC[10] = { "01" ,"02","04","08","10","20","40","80","1b","36" };
static string key_Rounds[10];


int Sub_Byte[16][16] =
{
	{0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76},
	{0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0 },
	{0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15 },
	{0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75},
	{0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84},
	{0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF},
	{0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8},
	{0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2},
	{0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73},
	{0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB},
	{0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79},
	{0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08},
	{0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A},
	{0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E},
	{0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF},
	{0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16}
};


string inv_Sbox[16][16] =
{
	{"0x52","0x09","0x6a","0xd5","0x30","0x36","0xa5","0x38","0xbf","0x40","0xa3","0x9e","0x81","0xf3","0xd7","0xfb"},
	{"0x7c","0xe3","0x39","0x82","0x9b","0x2f","0xff","0x87","0x34","0x8e","0x43","0x44","0xc4","0xde","0xe9","0xcb"},
	{"0x54","0x7b","0x94","0x32","0xa6","0xc2","0x23","0x3d","0xee","0x4c","0x95","0x0b","0x42","0xfa","0xc3","0x4e"},
	{"0x08","0x2e","0xa1","0x66","0x28","0xd9","0x24","0xb2","0x76","0x5b","0xa2","0x49","0x6d","0x8b","0xd1","0x25"},
	{"0x72","0xf8","0xf6","0x64","0x86","0x68","0x98","0x16","0xd4","0xa4","0x5c","0xcc","0x5d","0x65","0xb6","0x92"},
	{"0x6c","0x70","0x48","0x50","0xfd","0xed","0xb9","0xda","0x5e","0x15","0x46","0x57","0xa7","0x8d","0x9d","0x84"},
	{"0x90","0xd8","0xab","0x00","0x8c","0xbc","0xd3","0x0a","0xf7","0xe4","0x58","0x05","0xb8","0xb3","0x45","0x06"},
	{"0xd0","0x2c","0x1e","0x8f","0xca","0x3f","0x0f","0x02","0xc1","0xaf","0xbd","0x03","0x01","0x13","0x8a","0x6b"},
	{"0x3a","0x91","0x11","0x41","0x4f","0x67","0xdc","0xea","0x97","0xf2","0xcf","0xce","0xf0","0xb4","0xe6","0x73"},
	{"0x96","0xac","0x74","0x22","0xe7","0xad","0x35","0x85","0xe2","0xf9","0x37","0xe8","0x1c","0x75","0xdf","0x6e"},
	{"0x47","0xf1","0x1a","0x71","0x1d","0x29","0xc5","0x89","0x6f","0xb7","0x62","0x0e","0xaa","0x18","0xbe","0x1b"},
	{"0xfc","0x56","0x3e","0x4b","0xc6","0xd2","0x79","0x20","0x9a","0xdb","0xc0","0xfe","0x78","0xcd","0x5a","0xf4"},
	{"0x1f","0xdd","0xa8","0x33","0x88","0x07","0xc7","0x31","0xb1","0x12","0x10","0x59","0x27","0x80","0xec","0x5f"},
	{"0x60","0x51","0x7f","0xa9","0x19","0xb5","0x4a","0x0d","0x2d","0xe5","0x7a","0x9f","0x93","0xc9","0x9c","0xef"},
	{"0xa0","0xe0","0x3b","0x4d","0xae","0x2a","0xf5","0xb0","0xc8","0xeb","0xbb","0x3c","0x83","0x53","0x99","0x61"},
	{"0x17","0x2b","0x04","0x7e","0xba","0x77","0xd6","0x26","0xe1","0x69","0x14","0x63","0x55","0x21","0x0c","0x7d"},
};
string inv_mix[4][4] =
{
	{"0e","0b","0d","09"},
	{"09","0e","0b","0d"},
	{"0d","09","0e","0b"},
	{"0b","0d","09","0e"},
};



string AES::first_time(string plain, string initial_key)
{
	string initial_XOR;
	initial_XOR = Initial_XoR(plain, initial_key);
	return initial_XOR;
}
string AES::Initial_XoR(string plain, string initial_key)
{
	string bin_plain;
	string bin_key;

	string temp_plain;
	temp_plain = plain[0];
	temp_plain += plain[1];

	string temp_KEY;
	temp_KEY = initial_key[0];
	temp_KEY += initial_key[1];
	string keyXORplain;

	string HEx = "0x";

	for (int i = 2; i < 34; i += 2)
	{
		temp_plain += plain[i];
		temp_plain += plain[i + 1];

		temp_KEY += initial_key[i];
		temp_KEY += initial_key[i + 1];

		bin_plain = hex_to_bin(temp_plain);
		bin_key = hex_to_bin(temp_KEY);

		temp_plain.clear();
		temp_KEY.clear();

		temp_plain = plain[0];
		temp_plain += plain[1];

		temp_KEY = initial_key[0];
		temp_KEY += initial_key[1];

		//cout << bin_plain << endl;
		keyXORplain = xoring(bin_plain, bin_key, 8);
		HEx += bin_to_hex(keyXORplain);

		keyXORplain.clear();
		bin_key.clear();
		bin_plain.clear();
	}

	//cout << HEx;
	string matrix_11[4][4];
	int counter_11 = 2;
	string New_sorted_HEX = "0x";
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			matrix_11[i][j] += HEx[counter_11];
			matrix_11[i][j] += HEx[counter_11 + 1];
			counter_11 += 2;
		}
	}


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			New_sorted_HEX += matrix_11[i][j];
		}

	}
	return New_sorted_HEX;
}
string AES::AES_Encrypt(string plain, string key)
{
	//cout << "---------------------------------------" << endl;
	/*if (plain.length() % 2 != 0)
	{
		plain += 'Z';
	}*/
	transform(plain.begin(), plain.end(), plain.begin(), ::toupper);

	//cout << plain << endl;

	string matrix[4][4];
	int counter = 2;
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			matrix[i][j] += plain[counter];
			matrix[i][j] += plain[counter + 1];
			counter += 2;
		}
	}
	string temp;
	string temp1;
	string temp2;
	int row; //= stoi(ah);
	int col;
	int Matrix_sBox[4][4];

	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		cout << matrix[i][j] << " ";
	//	}

	//	// Newline for new row
	//	cout << endl;
	//}


	//know index and then S-Box
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp = matrix[j][i];
			if (temp[0] == 'A')
			{
				temp1 = "10";
				row = stoi(temp1);
			}
			else if (temp[0] == 'B')
			{
				temp1 = "11";
				row = stoi(temp1);
			}
			else if (temp[0] == 'C')
			{
				temp1 = "12";
				row = stoi(temp1);
			}
			else if (temp[0] == 'D')
			{
				temp1 = "13";
				row = stoi(temp1);
			}
			else if (temp[0] == 'E')
			{
				temp1 = "14";
				row = stoi(temp1);
			}
			else if (temp[0] == 'F')
			{
				temp1 = "15";
				row = stoi(temp1);
			}

			else
				row = (int)temp[0] - 48;

			if (temp[1] == 'A')
			{
				temp2 = "10";
				col = stoi(temp2);
			}
			else if (temp[1] == 'B')
			{
				temp2 = "11";
				col = stoi(temp2);
			}
			else if (temp[1] == 'C')
			{
				temp2 = "12";
				col = stoi(temp2);
			}
			else if (temp[1] == 'D')
			{
				temp2 = "13";
				col = stoi(temp2);
			}
			else if (temp[1] == 'E')
			{
				temp2 = "14";
				col = stoi(temp2);
			}
			else if (temp[1] == 'F')
			{
				temp2 = "15";
				col = stoi(temp2);
			}

			else
				col = (int)temp[1] - 48;

			/*cout << "row index is: " << row << " ";
			cout << "col index is: " << col <<" ";
			cout << endl;*/
			Matrix_sBox[i][j] = Sub_Byte[row][col];

		}

	}
	//cout << endl << "after Sub-Box:" << endl << endl;
	//string cipher500 = "";
	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		cipher500=DEC_To_HEX(Matrix_sBox[i][j]) ;
	//		cout << cipher500 << " ";
	//		cipher500.clear();
	//	}

	//	// Newline for new row
	//	cout << endl;
	//}
	//



	//Shift rows
	shift_rows(Matrix_sBox);
	//string cipher501;
	//cout << endl << "after SHIFT:" << endl << endl;
	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		cipher501=DEC_To_HEX(Matrix_sBox[i][j]) ;
	//		cout << cipher501 << " ";
	//		cipher501.clear();
	//	}

	//	// Newline for new row
	//	cout << endl;
	//}

	//cout << endl;
	//Mix Columns
	int Mix_matrix[4][4] = { 2,3,1,1,
								1,2,3,1,
								1,1,2,3,
								3,1,1,2 };

	int after_Mix[4][4];
	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		cout << Mix_matrix[i][j] << " ";
	//	}

	//	// Newline for new row
	//	cout << endl;
	//}
	//cout << endl;
	int temp_col[4];
	int  temp_arr_mix[4];

	int counterr_4 = 0;
	int counterr_16 = 0;
	string cipher = "0x";
	for (int row = 0; row < 16; row++)
	{
		temp_arr_mix[counterr_16] = Mix_matrix[counterr_4][counterr_16];
		counterr_16++;
		//cout <<"ssssssss" <<temp_arr_mix[counterr_16] << " ";
		if (counterr_16 == 4)
		{

			cipher += MIX_arr_calc(temp_arr_mix, Matrix_sBox);

			counterr_4++;
			counterr_16 = 0;


		}
	}
	//cout<<"in function: " << cipher << endl;

	/// //////////////////////////////////////////////////////////
	string bin_cipher;
	string bin_round_Key;

	string temp_cipher;
	temp_cipher = cipher[0];
	temp_cipher += cipher[1];

	string temp_round_Key;
	string Key_Round = key;

	string matrix_13[4][4];
	int counter_13 = 2;
	string NEW_Sorted_HEX = "0x";

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			matrix_13[i][j] += Key_Round[counter_13];
			matrix_13[i][j] += Key_Round[counter_13 + 1];
			counter_13 += 2;
		}
	}


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			NEW_Sorted_HEX += matrix_13[i][j];
		}

	}

	//cout << endl << "round KEy one is: " << vv << endl;
	temp_round_Key = NEW_Sorted_HEX[0];
	temp_round_Key += NEW_Sorted_HEX[1];
	string RoundKey_XOR_Cipher;

	string HEx2 = "0x";

	for (int i = 2; i < 34; i += 2)
	{
		temp_cipher += cipher[i];
		temp_cipher += cipher[i + 1];

		temp_round_Key += NEW_Sorted_HEX[i];
		temp_round_Key += NEW_Sorted_HEX[i + 1];

		bin_cipher = hex_to_bin(temp_cipher);
		bin_round_Key = hex_to_bin(temp_round_Key);

		temp_cipher.clear();
		temp_round_Key.clear();

		temp_cipher = cipher[0];
		temp_cipher += cipher[1];

		temp_round_Key = NEW_Sorted_HEX[0];
		temp_round_Key += NEW_Sorted_HEX[1];

		//cout << bin_plain << endl;
		RoundKey_XOR_Cipher = xoring(bin_cipher, bin_round_Key, 8);
		HEx2 += bin_to_hex(RoundKey_XOR_Cipher);

		RoundKey_XOR_Cipher.clear();
		bin_round_Key.clear();
		bin_cipher.clear();
	}


	//cout << endl << "cipher is in aes: " << HEx2 << endl;
	return HEx2;
}
string AES::DEC_To_HEX(int decimalNum)
{
	int rem, i = 0;
	char hexaDecimalNum[50];
	//cout << "Enter the Decimal Number: ";
	string hex_num;
	while (decimalNum != 0)
	{
		rem = decimalNum % 16;
		if (rem < 10)
			rem = rem + 48;
		else
			rem = rem + 55;
		hexaDecimalNum[i] = rem;
		i++;
		decimalNum = decimalNum / 16;
	}
	//cout << "\nEquivalent Hexadecimal Value: ";
	//cout << endl << "i is:" << i << endl;
	if (i == 1)
	{
		hex_num = "0";
	}
	for (i = i - 1; i >= 0; i--)
		hex_num += hexaDecimalNum[i];

	return hex_num;
}
string AES::Lastround_AES_Encrypt(string plain, string key)
{
	//cout << "---------------------------------------" << endl;
	/*if (plain.length() % 2 != 0)
	{
		plain += 'Z';
	}*/
	transform(plain.begin(), plain.end(), plain.begin(), ::toupper);
	//cout << plain << endl;

	string matrix[4][4];
	int counter = 2;
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			matrix[i][j] += plain[counter];
			matrix[i][j] += plain[counter + 1];
			counter += 2;
		}
	}
	string temp;
	string temp1;
	string temp2;
	int row; //= stoi(ah);
	int col;
	int Matrix_sBox[4][4];

	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		cout << matrix[i][j] << " ";
	//	}

	//	// Newline for new row
	//	cout << endl;
	//}


	//know index and then S-Box
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp = matrix[j][i];
			if (temp[0] == 'A')
			{
				temp1 = "10";
				row = stoi(temp1);
			}
			else if (temp[0] == 'B')
			{
				temp1 = "11";
				row = stoi(temp1);
			}
			else if (temp[0] == 'C')
			{
				temp1 = "12";
				row = stoi(temp1);
			}
			else if (temp[0] == 'D')
			{
				temp1 = "13";
				row = stoi(temp1);
			}
			else if (temp[0] == 'E')
			{
				temp1 = "14";
				row = stoi(temp1);
			}
			else if (temp[0] == 'F')
			{
				temp1 = "15";
				row = stoi(temp1);
			}

			else
				row = (int)temp[0] - 48;

			if (temp[1] == 'A')
			{
				temp2 = "10";
				col = stoi(temp2);
			}
			else if (temp[1] == 'B')
			{
				temp2 = "11";
				col = stoi(temp2);
			}
			else if (temp[1] == 'C')
			{
				temp2 = "12";
				col = stoi(temp2);
			}
			else if (temp[1] == 'D')
			{
				temp2 = "13";
				col = stoi(temp2);
			}
			else if (temp[1] == 'E')
			{
				temp2 = "14";
				col = stoi(temp2);
			}
			else if (temp[1] == 'F')
			{
				temp2 = "15";
				col = stoi(temp2);
			}

			else
				col = (int)temp[1] - 48;

			/*cout << "row index is: " << row << " ";
			cout << "col index is: " << col <<" ";
			cout << endl;*/
			Matrix_sBox[i][j] = Sub_Byte[row][col];

		}

	}
	//cout << endl << "after Sub-Box:" << endl << endl;
	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		cout << Matrix_sBox[i][j] << " ";
	//	}

	//	// Newline for new row
	//	cout << endl;
	//}


	//Shift rows
	shift_rows(Matrix_sBox);
	//cout << endl << "after swap:" << endl << endl;
	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		cout << Matrix_sBox[i][j] << " ";
	//		
	//	}

	//	// Newline for new row
	//	cout << endl;
	//}

	//cout << endl;
	string cipher = "0x";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cipher += DEC_To_HEX(Matrix_sBox[i][j]);
		}
	}
	//cout << "cipher is: "<<cipher<< endl;
	 //////////////////////////////////////////////////////////
	string bin_cipher;
	string bin_round_Key;

	string temp_cipher;

	for (int k = 0; k < 4; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			cipher += Matrix_sBox[k][i];
		}
	}
	temp_cipher = cipher[0];
	temp_cipher += cipher[1];

	string temp_round_Key;
	string Key_Round = key;

	string matrix_13[4][4];
	int counter_13 = 2;
	string NEW_Sorted_HEX = "0x";

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			matrix_13[i][j] += Key_Round[counter_13];
			matrix_13[i][j] += Key_Round[counter_13 + 1];
			counter_13 += 2;
		}
	}

	cout << "" << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			NEW_Sorted_HEX += matrix_13[i][j];
			cout << NEW_Sorted_HEX << " ";
		}
		cout << endl;
	}

	temp_round_Key = NEW_Sorted_HEX[0];
	temp_round_Key += NEW_Sorted_HEX[1];
	string RoundKey_XOR_Cipher;

	string HEx2 = "0x";


	for (int i = 2; i < 34; i += 2)
	{
		temp_cipher += cipher[i];
		temp_cipher += cipher[i + 1];

		temp_round_Key += NEW_Sorted_HEX[i];
		temp_round_Key += NEW_Sorted_HEX[i + 1];

		bin_cipher = hex_to_bin(temp_cipher);
		bin_round_Key = hex_to_bin(temp_round_Key);

		temp_cipher.clear();
		temp_round_Key.clear();

		temp_cipher = cipher[0];
		temp_cipher += cipher[1];

		temp_round_Key = NEW_Sorted_HEX[0];
		temp_round_Key += NEW_Sorted_HEX[1];

		//cout << bin_plain << endl;
		RoundKey_XOR_Cipher = xoring(bin_cipher, bin_round_Key, 8);
		HEx2 += bin_to_hex(RoundKey_XOR_Cipher);

		RoundKey_XOR_Cipher.clear();
		bin_round_Key.clear();
		bin_cipher.clear();
	}
	string matrix_12[4][4];
	int counter_12 = 2;
	string Final_HEX = "";
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			matrix_12[i][j] += HEx2[counter_12];
			matrix_12[i][j] += HEx2[counter_12 + 1];
			counter_12 += 2;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Final_HEX += matrix_12[i][j];
		}

	}
	//cout <<"Final_HEX in last aes: " <<Final_HEX;
	return Final_HEX;
}
void AES::XoR_arr(int arr[], int arr2[], int size, int* ret_arr)
{
	//end(arr) - begin(arr);
	//cout << endl<< "real XOR:" << endl;
	for (int i = 0; i < size; i++)
	{
		ret_arr[i] = arr[i] ^ arr2[i];
		//cout << ret_arr[i];
	}
	//cout << endl;
}
string AES::MIX_arr_calc(int temp_arr_mix[4], int Matrix_sBox[4][4])
{
	int binaryArr2[8] = { 0 };
	int arr1b[8] = { 0,0,0,1,1,0,1,1 };
	int  temp_arr_SBOX[4];
	int temp_bit[8] = { 0 };
	string final_matrix = "";
	for (int o = 0; o < 4; o++)
	{
		//cout << endl;
		for (int col = 0; col < 4; col++)
		{
			temp_arr_SBOX[col] = Matrix_sBox[col][o];
			//cout << temp_arr_SBOX[col] << endl;
		}
		bool _1b = false;
		int result[8] = { 0 };
		int result_16[8] = { 0 };

		for (int i = 0; i < 4; i++)
		{
			if (temp_arr_mix[i] == 2)
			{
				_1b = dectobinary(temp_arr_SBOX[i], binaryArr2, 2);
				if (_1b == true)
				{
					XoR_arr(binaryArr2, arr1b, 8, result);
				}
				else
				{
					for (int i = 0; i < 8; i++)
					{
						result[i] = binaryArr2[i];
					}
				}
			}
			else if (temp_arr_mix[i] == 1)
			{
				_1b = dectobinary(temp_arr_SBOX[i], binaryArr2, 1);
				for (int i = 0; i < 8; i++)
				{
					result[i] = binaryArr2[i];
				}


			}
			else//3
			{
				_1b = dectobinary(temp_arr_SBOX[i], binaryArr2, 2);
				if (_1b == true)
				{
					XoR_arr(binaryArr2, arr1b, 8, result);
				}
				else
				{
					for (int i = 0; i < 8; i++)
					{
						result[i] = binaryArr2[i];
					}
				}
				//*1
				_1b = dectobinary(temp_arr_SBOX[i], binaryArr2, 1);
				XoR_arr(result, binaryArr2, 8, result);
				/*for (int i = 0; i < 8; i++)
				{
					result[i] = binaryArr2[i];
				}*/

			}
			XoR_arr(result, temp_bit, 8, temp_bit);
			/*cout << endl;
			for (int i = 0; i < 8; i++)
			{
				cout <<temp_bit[i];
			}
			cout << endl;*/

		}
		string HEX_after = "";
		for (int i = 0; i < 8; i++)
		{
			HEX_after += to_string(temp_bit[i]);
			temp_bit[i] = 0;
		}
		string final_hex;
		final_hex = bin_to_hex(HEX_after);
		//cout << final_hex << endl;
		final_matrix += final_hex;

	}
	return final_matrix;
}
bool AES::dectobinary(int decimal, int binaryArr[], int mult)
{

	int count = 0;
	bitset<8> bin_x(decimal);
	bool _1b = false;
	if (mult == 2)
	{

		if (bin_x[7] == 1)
		{

			_1b = true;
		}


		for (int i = 6; i >= 0; i--)
		{
			binaryArr[count] = bin_x[i];
			count++;
			//cout << binaryArr[i];
		}
		binaryArr[7] = 0;

		//cout << endl;
	}
	else if (mult == 1)
	{
		for (int i = 7; i >= 0; i--)
		{
			binaryArr[count] = bin_x[i];
			count++;
		}
	}
	return _1b;
}
void AES::shift_rows(int Matrix_sBox[4][4])
{
	int temp_shift[4];

	for (int i = 1; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp_shift[j] = Matrix_sBox[i][j];
		}
		for (int k = 0; k < 4; k++)
		{
			if (i == 1)
			{
				if (k != 3)
				{
					Matrix_sBox[i][k] = Matrix_sBox[i][k + 1];
				}
				else
					Matrix_sBox[i][k] = temp_shift[0];

			}
			if (i == 2)
			{
				if (k < i)
					Matrix_sBox[i][k] = temp_shift[k + i];
				else
					Matrix_sBox[i][k] = temp_shift[k - i];


			}
			if (i == 3)
			{
				if (k > 0)
					Matrix_sBox[i][k] = temp_shift[k - 1];
				else
					Matrix_sBox[i][k] = temp_shift[3];

			}

		}
	}


}
string AES::bin_to_hex(string key)
{
	string key_hex = "";
	string sub_Str = "";
	for (int i = 0; i < key.length(); i += 4)
	{
		sub_Str = key.substr(i, 4);

		if (sub_Str == "1010")
			key_hex += "A";

		else if (sub_Str == "1011")
			key_hex += "B";

		else if (sub_Str == "1100")
			key_hex += "C";

		else if (sub_Str == "1101")
			key_hex += "D";

		else if (sub_Str == "1110")
			key_hex += "E";

		else if (sub_Str == "1111")
			key_hex += "F";

		else
		{
			int size = sub_Str.length();
			int bit = 0, decimal = 0;
			int power_index = 0;
			for (int i = size - 1; i >= 0; i--)
			{
				bit = sub_Str[i] - '0';
				if (bit != 0)
					decimal += bit * pow(2, power_index);
				power_index++;
			}
			power_index = 0;
			key_hex += to_string(decimal);
		}

		sub_Str.clear();
	}
	return key_hex;
}

//KEY
string AES::rotation(string L_word)
{
	string temp_Word = "";
	temp_Word += L_word[0];
	temp_Word += L_word[1];
	int len = L_word.length();
	for (int i = 1; i < L_word.length(); i++)
	{
		L_word[i - 1] = L_word[i + 1];
	}
	L_word[len - 2] = temp_Word[0];
	L_word[len - 1] = temp_Word[1];
	return L_word;
}
string AES::sbox_pick(string L_word)
{
	int counter2 = 0;
	int x_axis, y_axis;
	string sub_Word = "";
	for (int i = 0; i < 4; i++)
	{
		x_axis = L_word[counter2];
		y_axis = L_word[counter2 + 1];
		if (x_axis > 47 && x_axis < 58)
		{
			x_axis -= 48;
		}
		else if (x_axis > 96 && x_axis < 103)
		{
			x_axis -= 87;
		}
		if (y_axis > 47 && y_axis < 58)
		{
			y_axis -= 48;
		}
		else if (y_axis > 96 && y_axis < 103)
		{
			y_axis -= 87;
		}
		sub_Word += sbox[x_axis][y_axis];
		counter2 += 2;
	}
	return sub_Word;
}
string AES::zerox_rem(string sb_word)
{
	int counter3 = 4;
	for (int i = 0; i < sb_word.length() - 1; i++)
	{
		if (sb_word[i] == '0' && sb_word[i + 1] == 'x')
		{
			sb_word.erase(counter3, 2);
			counter3 += 2;
		}
	}
	return sb_word;
}
string AES::hex_to_bin(string sb_wrod)
{
	transform(sb_wrod.begin(), sb_wrod.end(), sb_wrod.begin(), ::toupper);
	string binary = "";
	int counter = 0;
	for (int i = 2; i < sb_wrod.length(); i++)
	{
		switch (sb_wrod[i])
		{
		case 'A':
			binary += "1010";
			break;

		case 'B':
			binary += "1011";
			break;

		case 'C':
			binary += "1100";
			break;

		case 'D':
			binary += "1101";
			break;

		case 'E':
			binary += "1110";
			break;

		case 'F':
			binary += "1111";
			break;

		default:
			/*int num=plain[i], bin;
			cout << plain[i] << endl;
			while (num > 0)
			{
				bin = num % 2;
				binary += to_string(bin);
				num /= 2;
			}
			binary += '|';*/
			char d = sb_wrod[i] - '0';
			string output = "0000";

			for (int i = 0; d > 0; i++)
			{
				output[3 - i] = d % 2 + '0';
				d = d / 2;
			}
			binary += output;
			break;
		}
	}
	return binary;
}
string AES::xoring(string first, string second, int length)
{
	string xoring = "";
	int sbit = 0, rcbit = 0;
	for (int i = 0; i < length; i++)
	{
		sbit = first[i] - '0';
		rcbit = second[i] - '0';
		xoring += to_string(sbit ^ rcbit);
	}
	return xoring;
}
string AES::bin_to_hex2(string key)
{
	string key_hex = "0x";
	string sub_Str = "";
	for (int i = 0; i < key.length(); i += 4)
	{
		sub_Str = key.substr(i, 4);

		if (sub_Str == "1010")
			key_hex += "A";

		else if (sub_Str == "1011")
			key_hex += "B";

		else if (sub_Str == "1100")
			key_hex += "C";

		else if (sub_Str == "1101")
			key_hex += "D";

		else if (sub_Str == "1110")
			key_hex += "E";

		else if (sub_Str == "1111")
			key_hex += "F";

		else
		{
			int size = sub_Str.length();
			int bit = 0, decimal = 0;
			int power_index = 0;
			for (int i = size - 1; i >= 0; i--)
			{
				bit = sub_Str[i] - '0';
				if (bit != 0)
					decimal += bit * pow(2, power_index);
				power_index++;
			}
			power_index = 0;
			key_hex += to_string(decimal);
		}

		sub_Str.clear();
	}
	return key_hex;
}
void AES::key_expansion(string key, int numOfround)
{
	transform(key.begin(), key.end(), key.begin(), ::tolower);
	string k_matrix[4][4];
	string words[4];
	int counter = 2;
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			k_matrix[i][j] += key[counter];
			k_matrix[i][j] += key[counter + 1];
			words[j] += k_matrix[i][j];
			counter += 2;
		}
	}

	//left circular rotation of last word
	string last_word = words[3];
	string temp_lastword = "0x" + words[3];
	string rotated = "";
	rotated = rotation(last_word);


	//sbox of last word
	string subs_Word = "";
	subs_Word = sbox_pick(rotated);

	string lllll = subs_Word;
	//remove 0x from word
	subs_Word = zerox_rem(lllll);


	//XORing with RC
	string subs_binary = hex_to_bin(subs_Word);
	string rc = "0x" + RC[numOfround] + "000000";
	string rc_binary = hex_to_bin(rc);
	string XOR = "";
	XOR = xoring(subs_binary, rc_binary, subs_binary.length());
	words[3] = XOR;
	/*cout << words[3];*/

	//xoring between words
	string bin_word;
	for (int i = 0; i < 3; i++)
	{
		words[i] = "0x" + words[i];
		words[i] = hex_to_bin(words[i]);
	}

	string temp_LW_hex = hex_to_bin(temp_lastword);
	XOR.clear();
	words[0] = xoring(words[0], words[3], words[0].length());
	XOR.clear();
	for (int i = 1; i < 4; i++)
	{
		if (i < 3)
		{
			words[i] = xoring(words[i], words[i - 1], words[i].length());
		}
		else if (i == 3)
		{
			words[i] = xoring(temp_LW_hex, words[i - 1], words[i].length());
		}
	}

	string key_hex = "";
	for (int i = 0; i < 4; i++)
	{
		key_hex += words[i];
	}
	key_Rounds[numOfround] += bin_to_hex2(key_hex);
}

//decrypt
string AES::AES_Decrypt(string cipher, string initial_key)
{
	bool Invalid_input1 = false;
	bool Invalid_input2 = false;
	bool Invalid_input3 = false;
	Invalid_input1 = Check_Hex(cipher);
	Invalid_input2 = Length_input(initial_key, 34);
	Invalid_input3 = Check_Hex(initial_key);
	//Invalid_input = Check_Hex();
	if (Invalid_input1 == false || Invalid_input2 == false || Invalid_input3 == false)
	{
		cout << "Wrong Input" << endl;;
		return "";
	}
	string str_hex[100];
	int counter_hex = 0;
	int len = (cipher.length() - 2) % 32;
	if (len != 0)
	{
		int append = 32 - len;
		for (int i = 0; i < append; i++)
		{
			cipher += '0';
		}
	}

	//padding of key
	int key_len = (initial_key.length() - 2) % 32;
	if (key_len != 0)
	{
		int append_for_key = 32 - key_len;
		for (int i = 0; i < append_for_key; i++)
		{
			initial_key += '0';
		}
	}

	int counter_32 = 2; //skip "0x"
	int num_32 = (cipher.length() - 2) / 32; //number of blocks (16)
	for (int i = 0; i < num_32; i++)
	{
		str_hex[counter_hex] += "0x";
		for (int j = 0; j < 32; j++)
		{
			str_hex[counter_hex] += cipher[counter_32];
			counter_32++;
		}
		counter_hex++;
	}

	string final_plain = "0x";
	for (int O = 0; O < num_32; O++)
	{
		for (int i = 0; i < 10; i++)
		{

			key_Rounds[i].clear();

			if (i == 0)
			{
				key_expansion(initial_key, i);
			}

			else if (i > 0)
			{
				key_expansion(key_Rounds[i - 1], i);
			}
		}
		string key = key_Rounds[9];
		string C = hex_to_bin(str_hex[O]);
		string K = hex_to_bin(key);
		string X = xoring(K, C, C.size());
		string res = bin_to_hex(X);
		res.insert(0, "0x");
		//out << res << endl;
		//cout << res<<endl;
		if (str_hex[O].length() % 2 != 0)
		{
			str_hex[O] += 'Z';
		}
		transform(res.begin(), res.end(), res.begin(), ::toupper);
		string cipher2[4][4];
		int counter = 2;
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				cipher2[i][j] += res[counter];
				cipher2[i][j] += res[counter + 1];
				counter += 2;
			}
		}
		cipher = "";
		shift_rows_right(cipher2);
		/*for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				cout << cipher2[i][j] << " ";
			}
			cout << endl;
		}*/
		inv_sbox(cipher2);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				//cout << cipher2[i][j] << " ";
				cipher.append(cipher2[j][i]);
			}
			//cout << endl;
		}
		cipher = zerox_rem(cipher);
		//cout << endl << cipher << endl;

		for (int i = 0; i < 9; i++)
		{
			cipher = hex_to_bin(cipher);
			string K = hex_to_bin(key_Rounds[8 - i]);
			cipher = xoring(cipher, K, K.length());
			cipher = bin_to_hex(cipher);
			cipher.insert(0, "0x");
			//cout << cipher;
			counter = 2;
			transform(cipher.begin(), cipher.end(), cipher.begin(), ::toupper);
			for (int j = 0; j < 4; j++)
			{
				for (int i = 0; i < 4; i++)
				{
					cipher2[i][j] = "";
					cipher2[i][j] += cipher[counter];
					cipher2[i][j] += cipher[counter + 1];
					counter += 2;
				}
			}
			/*for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					cout << cipher2[i][j] << " ";
				}
				cout << endl;
			}*/
			inv_mix_col(cipher2);
			/*for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					cout << cipher2[j][i] << " ";
				}
				cout << endl;
			}*/
			shift_rows_right(cipher2);
			inv_sbox(cipher2);
			cipher = "";
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					cipher.append(cipher2[j][i]);
				}
			}
			cipher = zerox_rem(cipher);
			//cout << endl << cipher << endl;
		}
		cipher = hex_to_bin(cipher);
		string kk = hex_to_bin(initial_key);
		cipher = xoring(cipher, kk, kk.length());
		cipher = bin_to_hex(cipher);
		final_plain += cipher;
		//cout << cipher;
	}
	return final_plain;
}
void AES::shift_rows_right(string Matrix_sBox[4][4])
{
	string temp_shift[4];
	for (int i = 1; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp_shift[j] = Matrix_sBox[i][j];//first row ,second , ....
		}
		for (int j = 0; j < 4; j++)
		{
			if (i == 1)
			{
				if (j == 0)
				{
					Matrix_sBox[i][j] = temp_shift[3];
				}
				else
				{
					Matrix_sBox[i][j] = temp_shift[j - 1];
				}
			}
			else if (i == 2)
			{
				if (j == 0)
				{
					Matrix_sBox[i][j] = temp_shift[2];
				}
				else if (j == 1)
				{
					Matrix_sBox[i][j] = temp_shift[3];
				}
				else
				{
					Matrix_sBox[i][j] = temp_shift[j - 2];
				}
			}
			else if (i == 3)
			{
				if (j == 3)
				{
					Matrix_sBox[i][j] = temp_shift[0];
				}
				else
				{
					Matrix_sBox[i][j] = temp_shift[j + 1];
				}
			}
		}
	}


}
void AES::inv_sbox(string matrix[4][4])
{
	string temp;
	string temp1;
	string temp2;
	int row;
	int col;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp = matrix[i][j];
			if (temp[0] == 'A')
			{
				temp1 = "10";
				row = stoi(temp1);
			}
			else if (temp[0] == 'B')
			{
				temp1 = "11";
				row = stoi(temp1);
			}
			else if (temp[0] == 'C')
			{
				temp1 = "12";
				row = stoi(temp1);
			}
			else if (temp[0] == 'D')
			{
				temp1 = "13";
				row = stoi(temp1);
			}
			else if (temp[0] == 'E')
			{
				temp1 = "14";
				row = stoi(temp1);
			}
			else if (temp[0] == 'F')
			{
				temp1 = "15";
				row = stoi(temp1);
			}

			else
				row = (int)temp[0] - 48;

			if (temp[1] == 'A')
			{
				temp2 = "10";
				col = stoi(temp2);
			}
			else if (temp[1] == 'B')
			{
				temp2 = "11";
				col = stoi(temp2);
			}
			else if (temp[1] == 'C')
			{
				temp2 = "12";
				col = stoi(temp2);
			}
			else if (temp[1] == 'D')
			{
				temp2 = "13";
				col = stoi(temp2);
			}
			else if (temp[1] == 'E')
			{
				temp2 = "14";
				col = stoi(temp2);
			}
			else if (temp[1] == 'F')
			{
				temp2 = "15";
				col = stoi(temp2);
			}

			else
				col = (int)temp[1] - 48;

			/*cout << "row index is: " << row << " ";
			cout << "col index is: " << col <<" ";
			cout << endl;*/
			matrix[i][j] = inv_Sbox[row][col];
		}
	}
}
void AES::inv_mix_col(string matrix[4][4])
{
	string res[4][4];
	string temp[4];
	unsigned char temp2[4];
	for (int k = 0; k < 4; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			temp[i] = matrix[i][k];
			//cout << temp[i] << endl;
		}
		///cout << endl;
		for (int l = 0; l < 4; l++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (inv_mix[l][i] == "0e")
				{
					//13
					unsigned char v = stoi(temp[i], 0, 16);
					unsigned char x = inv0e(v);
					temp2[i] = x;
					/*string final = mul2(mul2(mul2(v)));
					string final2 = mul2(mul2(v));
					final = hex_to_bin(final);
					final2 = hex_to_bin(final2);
					string finalx = xoring(final, final2, final.length());
					string final3 =mul2(v);
					final3 = hex_to_bin(final3);
					finalx= xoring(finalx, final3, finalx.length());*/
				}
				if (inv_mix[l][i] == "0b")
				{
					unsigned char v = stoi(temp[i], 0, 16);
					unsigned char x = inv0b(v);
					temp2[i] = x;
				}
				if (inv_mix[l][i] == "0d")
				{
					/*string T = hex_to_bin("0x94");
					int T_len = T.length();
					T = shift2x(T);
					string F = xoring(T, hex_to_bin("0x94") , T.length());
					int F_len = F.length();
					F = shift2x(F);
					F = shift2x(F);
					string F2 = xoring(F, hex_to_bin("0x94") , T.length());
					temp2[i] = F2;*/
					unsigned char v = stoi(temp[i], 0, 16);
					unsigned char x = inv0d(v);
					temp2[i] = x;
				}
				if (inv_mix[l][i] == "09")
				{
					/*string T = hex_to_bin("0xED");
					int T_len = T.length();
					T = shift2x(T);
					T = shift2x(T);
					T = shift2x(T);
					string F = xoring(T, hex_to_bin("0xED"), T.length());
					temp2[i] = F;*/
					unsigned char v = stoi(temp[i], 0, 16);
					unsigned char x = inv09(v);
					temp2[i] = x;
				}
			}
			unsigned char final = unsigned char((int)temp2[0] ^ (int)temp2[1] ^ (int)temp2[2] ^ (int)temp2[3]);
			int x = (int)final;
			string xx = DEC_To_HEX(x);
			res[k][l] = xx;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix[i][j] = res[j][i];
		}
	}


}
string AES::shift2x(string arr)
{

	for (int i = 0; i < arr.length(); i++)
	{
		arr[i] = arr[i + 1];
		if (i == arr.length() - 1)
		{
			arr[i] = '0';
		}
	}
	return arr;
}
unsigned char AES::inv02(unsigned char b)
{
	if (b < 0x80)
		return (unsigned char)(int)(b << 1);
	else
		return (unsigned char)((int)(b << 1) ^ (int)(0x1b));
}
unsigned char AES::inv0e(unsigned char b)
{
	unsigned char x8 = inv02(inv02(inv02(b)));
	unsigned char x4 = inv02(inv02(b));
	unsigned char x2 = inv02(b);
	unsigned char T = (unsigned char)(int)x8 ^ (int)x4 ^ (int)x2;
	return T;
}
unsigned char AES::inv0b(unsigned char b)
{
	unsigned char x8 = inv02(inv02(inv02(b)));
	unsigned char x2 = inv02(b);
	unsigned char T = (unsigned char)(int)x8 ^ (int)x2 ^ (int)b;
	return T;
}
unsigned char AES::inv0d(unsigned char b)
{
	unsigned char x8 = inv02(inv02(inv02(b)));
	unsigned char x4 = inv02(inv02(b));
	unsigned char T = (unsigned char)(int)x8 ^ (int)x4 ^ (int)b;
	return T;
}
unsigned char AES::inv09(unsigned char b)
{
	return (unsigned char)((int)inv02(inv02(inv02(b))) ^ (int)b);
}

string AES::AES_Final_ENC(string plain, string initial_key)
{
	bool Invalid_input1 = false;
	bool Invalid_input2 = false;
	bool Invalid_input3 = false;
	Invalid_input1 = Check_Hex(plain);
	Invalid_input2 = Length_input(initial_key, 34);
	Invalid_input3 = Check_Hex(initial_key);
	//Invalid_input = Check_Hex();
	if (Invalid_input1 == false || Invalid_input2 == false || Invalid_input3 == false)
	{
		cout << "Wrong Input" << endl;;
		return "";
	}
	string str_hex[100];
	int counter_hex = 0;
	int len = (plain.length() - 2) % 32;
	if (len != 0)
	{
		int append = 32 - len;
		for (int i = 0; i < append; i++)
		{
			plain += '0';
		}
	}

	//padding of key
	int key_len = (initial_key.length() - 2) % 32;
	if (key_len != 0)
	{
		int append_for_key = 32 - key_len;
		for (int i = 0; i < append_for_key; i++)
		{
			initial_key += '0';
		}
	}

	int counter_32 = 2; //skip "0x"
	int num_32 = (plain.length() - 2) / 32; //number of blocks (16)
	for (int i = 0; i < num_32; i++)
	{
		str_hex[counter_hex] += "0x";
		for (int j = 0; j < 32; j++)
		{
			str_hex[counter_hex] += plain[counter_32];
			counter_32++;
		}
		counter_hex++;
	}

	string cipher;
	string temp_cipher;
	string final_Cipher = "0x";
	for (int O = 0; O < num_32; O++)
	{
		for (int i = 0; i < 10; i++)
		{
			key_Rounds[i].clear();

			if (i == 0)
			{
				string initial_XOR = first_time(str_hex[O], initial_key);
				key_expansion(initial_key, i);
				cipher = AES_Encrypt(initial_XOR, key_Rounds[i]);

			}

			else if (i > 0)
			{
				key_expansion(key_Rounds[i - 1], i);
				if (i != 9)
				{
					temp_cipher.clear();
					temp_cipher = cipher;
					cipher.clear();
					cipher = AES_Encrypt(temp_cipher, key_Rounds[i]);
					temp_cipher = cipher;
				}
				else
				{
					cipher.clear();
					cout << AES_Encrypt(temp_cipher, key_Rounds[i]);
					cipher = Lastround_AES_Encrypt(temp_cipher, key_Rounds[i]);

				}
			}

		}
		final_Cipher += cipher;
	}
	return final_Cipher;
}
bool AES::Length_input(string txt, int size)
{
	if (txt.length() <= size)
	{

		return 1;
	}
	return 0;
}
bool AES::Check_Hex(string hex_string)
{
	int Len = hex_string.length();
	transform(hex_string.begin(), hex_string.end(), hex_string.begin(), ::toupper);
	if (hex_string[0] != '0' || hex_string[1] != 'X')
	{
		return 0;
	}

	// Iterate over string
	for (int i = 2; i < Len; i++)
	{
		char ch = hex_string[i];

		// Check if the character
		// is invalid
		if ((ch < '0' || ch > '9') &&
			(ch < 'A' || ch > 'F'))
		{

			return 0;
		}
	}


	return 1;

}
