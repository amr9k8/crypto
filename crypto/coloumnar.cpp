#include "coloumnar.h"
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <cmath> 
using namespace std;

int key_numOf_Eelemnts;




string coloumnar::Encrypt(string plaintext, int key[])
{
	string ciphertext;
	plaintext.erase(std::remove_if(plaintext.begin(), plaintext.end(), ::isspace), plaintext.end());
	transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::toupper);

	int num_rows = ceil((float)plaintext.length() / (float)key_numOf_Eelemnts);
	if (plaintext.length() < (num_rows * key_numOf_Eelemnts))
	{
		int difference = (num_rows * key_numOf_Eelemnts) - plaintext.length();
		for (int i = 0; i < difference; i++)
		{
			plaintext += 'X';
		}
	}

	char matrix[100][100] = { '0' };
	int index = 0;
	for (int i = 0; i < num_rows; i++)
	{
		for (int j = 0; j < key_numOf_Eelemnts; j++)
		{
			if (index < plaintext.length())
			{
				matrix[i][j] = plaintext[index];
				index++;
			}
		}

	}

	for (int k = 1; k <= key_numOf_Eelemnts; k++)
	{
		for (int col = 0; col < key_numOf_Eelemnts; col++)
		{
			if (k == key[col])
			{
				for (int rows = 0; rows < num_rows; rows++)
				{
					ciphertext += matrix[rows][col];
				}
			}
		}
	}
	return ciphertext;
}

string coloumnar::Decrypt(string ciphertext, int key[])
{
	string plaintext;
	ciphertext.erase(std::remove_if(ciphertext.begin(), ciphertext.end(), ::isspace), ciphertext.end());
	transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), ::toupper);

	int num_rows = ceil((float)ciphertext.length() / (float)key_numOf_Eelemnts);
	char matrix[100][100] = { '0' };
	int index = 0;
	for (int k = 1; k <= key_numOf_Eelemnts; k++)
	{
		for (int col = 0; col < key_numOf_Eelemnts; col++)
		{
			if (k == key[col])
			{
				for (int rows = 0; rows < num_rows; rows++)
				{
					if (ciphertext.length() % key_numOf_Eelemnts == 0)
					{
						if (index < ciphertext.length())
						{
							matrix[rows][col] = ciphertext[index];
							index++;
						}
					}
					else if (ciphertext.length() % key_numOf_Eelemnts != 0)
					{
						if (rows != num_rows - 1 || col != key_numOf_Eelemnts - 1)
						{
							if (index < ciphertext.length())
							{
								matrix[rows][col] = ciphertext[index];
								index++;
							}
						}
					}

				}
			}
		}
	}

	for (int i = 0; i < num_rows; i++)
	{
		for (int j = 0; j < key_numOf_Eelemnts; j++)
		{
			if (matrix[i][j] != '0')
			{
				plaintext += matrix[i][j];
			}
		}
	}
	return plaintext;
}

list<int> coloumnar::analyse(string plaintext, string ciphertext)
{
	int key[100] = { 0 };
	plaintext.erase(std::remove_if(plaintext.begin(), plaintext.end(), ::isspace), plaintext.end());
	transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::toupper);
	ciphertext.erase(std::remove_if(ciphertext.begin(), ciphertext.end(), ::isspace), ciphertext.end());
	transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), ::toupper);
	list<int>keys;
	if (plaintext == ciphertext)
	{

		keys.push_back(1);
		return keys;
	}
	else
	{
		if (plaintext.length() < ciphertext.length())
		{
			int difference = ciphertext.length() - plaintext.length();
			for (int i = 0; i < difference; i++)
			{
				plaintext += 'X';
			}
		}

		int divisor1 = 0, divisor2 = 0;
		int counter = 0;
		bool exit1 = false;
		for (int divisor1 = 2; divisor1 < plaintext.length(); divisor1++)
		{
			if (exit1 == true)
				break;
			if (plaintext.length() % divisor1 == 0)
			{
				int divisor2 = plaintext.length() / divisor1;
				char matrix[100][100];
				int indx_pt = 0;

				for (int i = 0; i < divisor1; i++)
				{
					for (int j = 0; j < divisor2; j++)
					{
						matrix[i][j] = plaintext[indx_pt];
						indx_pt++;
					}
				}

				int priority = 1;
				bool check = false;
				int indx_ciph = 0;
				int rows = 0;
				int col = 0;
				bool check2 = false;
				for (col = 0; col < divisor2; col++)
				{
					if (exit1 == true)
						break;
					if (check2 == true)
					{
						check2 = false;
						col = 0;
					}
					for (rows = 0; rows < divisor1; rows++)
					{
						if (matrix[rows][col] == ciphertext[indx_ciph])
						{
							check = true;
							indx_ciph++;
						}
						else
						{
							check = false;
							indx_ciph -= rows;
							break;
						}
					}
					if (check == true)
					{
						key[col] = priority;
						priority++;
						counter++;
						check2 = true;
						rows = 0;
						col = 0;
						if (indx_ciph == ciphertext.length())
						{
							exit1 = true;
						}
					}
				}
			}
		}

		for (int i = 0; i < counter; i++)
		{
			keys.push_back(key[i]);
		}
		return keys;
	}
}
