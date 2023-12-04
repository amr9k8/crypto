using namespace std;
#include <String>;
#include <algorithm> 
#include "railfence.h"

string railfence::Encrypt_RainFence(string plain_txt, int key)
{


	//char new_plain_txt[100];
	plain_txt.erase(remove(plain_txt.begin(), plain_txt.end(), ' '), plain_txt.end());
	transform(plain_txt.begin(), plain_txt.end(), plain_txt.begin(), toupper);
	float col;
	float temp_len = float(plain_txt.length());
	float temp_key = float(key);
	col = temp_len / temp_key;
	col = ceil(col);
	//cout << col;
	char matrix[26][26];
	int start = 0;
	/*cout << "key is: " << key << endl;
	cout << "col is: " << col << endl;*/
	for (int columns = 0; columns < col; columns++)
	{
		for (int rows = 0; rows < key; rows++)
		{
			if (start >= plain_txt.length())
			{
				matrix[rows][columns] = 'X';

			}
			else
			{
				matrix[rows][columns] = plain_txt[start];
				start++;
			}

		}

	}
	//print matrix
	/*for (int i = 0; i < key; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}*/
	//print matrix
	//char cipher[100] = {'0'};
	string cipher2 = "";
	int start_cipher = 0;
	for (int columns = 0; columns < key; columns++)
	{
		for (int rows = 0; rows < col; rows++)
		{
			cipher2 = cipher2 + matrix[columns][rows];
		}

	}
	//cout << cipher2 << endl;
	//string cipher2 = string(cipher);//change arr of char to string
	//cipher2.erase(remove(cipher2.begin(), cipher2.end(), '0'), cipher2.end());
	//cipher2.erase(find(cipher2.begin(), cipher2.end(), '0'));
	return cipher2;
}


/////////////////////////////////////////////////////Decryption/////////////////////////////////////////////
string railfence::Decrypt_RainFence(string cipher_txt, int key)
{
	string plain_txt2 = "";

	float col;
	float temp_len = float(cipher_txt.length());
	float temp_key = float(key);
	col = temp_len / temp_key;
	col = ceil(col);
	//cout << col<<endl;
	char matrix[26][26];
	int st = 0;
	cipher_txt.erase(remove(cipher_txt.begin(), cipher_txt.end(), ' '), cipher_txt.end());
	transform(cipher_txt.begin(), cipher_txt.end(), cipher_txt.begin(), toupper);
	for (int rows = 0; rows < key; rows++)
	{
		for (int columns = 0; columns < col; columns++)
		{
			if (st >= cipher_txt.length())
			{
				matrix[rows][columns] = 'X';

			}
			else
			{
				matrix[rows][columns] = cipher_txt[st];
				st++;
			}

		}

	}


	//read from matrix
	for (int columns = 0; columns < col; columns++)
	{
		for (int rows = 0; rows < key; rows++)
		{
			plain_txt2 = plain_txt2 + matrix[rows][columns];
		}
	}
	//cout << endl;
	//print matrix
	//for (int i = 0; i < key; i++)
	//{
	//	for (int j = 0; j < col; j++)
	//	{
	//		cout << matrix[i][j] << " ";
	//	}

	//	// Newline for new row
	//	cout << endl;
	//}
	//plain_txt2.erase(find(plain_txt2.begin(), plain_txt2.end(), '0'));
	plain_txt2.erase(remove(plain_txt2.begin(), plain_txt2.end(), 'X'), plain_txt2.end());
	return plain_txt2;
}

int railfence::Analyse_RainFence(string plain_txt, string cipher_txt)
{

	//if same --> return 1

	transform(plain_txt.begin(), plain_txt.end(), plain_txt.begin(), toupper);
	plain_txt.erase(remove(plain_txt.begin(), plain_txt.end(), ' '), plain_txt.end());
	if (plain_txt == cipher_txt)
	{
		return 1;
	}
	int key = 2;
	string plain_txt2 = "";
	//cout << col<<endl;
	char matrix[26][26];


	while (plain_txt != plain_txt2)
	{
		float col;
		float temp_len = float(cipher_txt.length());
		float temp_key = float(key);
		col = temp_len / temp_key;
		col = ceil(col);
		int st = 0;
		plain_txt2 = "";
		for (int rows = 0; rows < key; rows++)
		{
			for (int columns = 0; columns < col; columns++)
			{
				if (st >= cipher_txt.length())
				{
					matrix[rows][columns] = 'X';

				}
				else
				{
					matrix[rows][columns] = cipher_txt[st];
					st++;
				}

			}

		}
		//read from matrix
		for (int columns = 0; columns < col; columns++)
		{
			for (int rows = 0; rows < key; rows++)
			{
				plain_txt2 = plain_txt2 + matrix[rows][columns];
			}
		}

		//print matrix
		//for (int i = 0; i < key; i++)
		//{
		//	for (int j = 0; j < col; j++)
		//	{
		//		cout << matrix[i][j] << " ";
		//	}

		//	// Newline for new row
		//	cout << endl;
		//}

		plain_txt2.erase(remove(plain_txt2.begin(), plain_txt2.end(), 'X'), plain_txt2.end());
		/*cout <<"test plain txt is: " <<plain_txt2 << endl;
		cout <<"real plain txt is: " <<plain_txt<<endl;*/
		key++;
	}
	return key - 1;
}
