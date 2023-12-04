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

class MD5_final
{


public:
	string str_to_bin(string input);
	string str_padded_to_448(string input, int& size);
	string add_length(string input, int size);

	// start of our work
	uint32_t G_function(uint32_t b, uint32_t c, uint32_t d, int r);
	string decToHexa(uint32_t n);

	void block_to_32bits(string block_512, string block_32bits[16], int round, bool last_block);
	


	void shifting(int bits[], int num_shifts);
	void CLS(int s_round, int bits[]);

	uint32_t binary_dec(int arr_bin[], int size);
	void binary_str_to_binary_int_arr(string binary, int ret_bin_arr[], int size);

	string repeated_16(string block_512, int round_num, bool last_block);

	string littleEndian32Bits(string str);
	string littleEndian_hex(string str);

	uint32_t HexToDec(string n);

	string MD5_Hash(string plaintext);
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
};
