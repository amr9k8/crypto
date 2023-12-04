#include "hillcipher.h"
#include <Eigen/Dense>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;

int hillcipher::smallerdet(int row, int col, Eigen::Matrix3d M)
{
	Eigen::MatrixXd temp(2, 2);
	bool err = false;
	bool err2 = false;
	if (col == 1)
		err = true;
	if (row == 1)
		err2 = true;
	row++;
	col++;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int x = i + row;
			int y = j + col;

			if (x > 2)
			{
				x = x % 3;
			}
			if (y > 2)
			{
				y = y % 3;
			}
			temp(i, j) = M(x, y);
		}
	}
	if (err2 == true)
	{
		swap(temp(0, 0), temp(1, 0));
		swap(temp(0, 1), temp(1, 1));
	}
	if (err == true)
	{
		swap(temp(0, 0), temp(0, 1));
		swap(temp(1, 0), temp(1, 1));
	}
	return temp.determinant();
}

Eigen::Matrix3d hillcipher::modular_inverse(Eigen::Matrix3d K)
{
	Eigen::MatrixXd K2(3, 3);
	int det = K.determinant();
	int mod = 0;
	if (det < 0)
	{
		mod = 26 + det % 26;
	}
	else
	{
		mod = det % 26;
	}

	int b = 0;
	int i = 0;
	while (i * mod % 26 != 1 && i < 26)
	{
		i++;
	}
	b = i;
	if (b == 26)
	{
		cout << "matrix has no inverse";
		exit(0);
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int Sdet = smallerdet(i, j, K);
			int k11 = b * pow(-1, i + j) * Sdet;
			if (k11 < 0)
			{
				K2(i, j) = 26 + k11 % 26;
			}
			else
			{
				K2(i, j) = k11 % 26;
			}
		}
	}
	K2 = K2.transpose().eval();
	return K2;
}

Eigen::Matrix2d hillcipher::modular_inverse2by2(Eigen::Matrix2d K)
{
	Eigen::Matrix2d K2;
	int det = K.determinant();
	int i = 0;
	int b = 0;
	while (i < 26 && (i * det) % 26 != 1)
	{
		if (26 + ((i * det) % 26) == 1)
			break;
		i++;
	}
	b = i;
	if (b == 26)
		cout << "matrix has no inverse";
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int sdet = K((i + 1) % 2, (j + 1) % 2);
			int k11 = b * pow(-1, i + j) * sdet;
			if (k11 < 0)
			{
				K2(i, j) = 26 + k11 % 26;
			}
			else
			{
				K2(i, j) = k11 % 26;
			}
		}
	}
	K2 = K2.transpose().eval();
	return K2;
}

list <int> hillcipher::analyse3by3(list <int> plain, list <int> cipher)
{
	Eigen::MatrixXd P(3, 3);
	Eigen::MatrixXd C(3, 3);
	int size1 = plain.size();
	int size2 = cipher.size();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			P(i, j) = plain.front() % 26;
			plain.pop_front();
			C(i, j) = cipher.front() % 26;
			cipher.pop_front();
		}
		for (int j = 3; j < size1 / 3; j++)
			plain.pop_front();
		for (int j = 3; j < size2 / 3; j++)
			cipher.pop_front();
	}
	Eigen::Matrix3d P_inv;
	Eigen::Matrix3d K;
	P_inv = modular_inverse(P);
	cout << P << endl;
	cout << P_inv << endl;
	K = P_inv * C;
	list <int> key;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			K(i, j) = (int)K(i, j) % 26;
			key.push_back(K(i, j));
		}
	}
	cout << K << endl;
	return key;
}

list <int> hillcipher::analyse(list <int> plain, list <int> cipher)
{
	Eigen::MatrixXd p1(2, 2);
	Eigen::MatrixXd c1(2, 2);
	int size1 = plain.size();
	int size2 = cipher.size();
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			p1(i, j) = plain.front() % 26;
			plain.pop_front();
			c1(i, j) = cipher.front() % 26;
			cipher.pop_front();
		}
		for (int j = 2; j < size1 / 2; j++)
			plain.pop_front();
		for (int j = 2; j < size2 / 2; j++)
			cipher.pop_front();
	}

	Eigen::MatrixXd k(2, 2);
	Eigen::Matrix2d pinv;
	pinv = modular_inverse2by2(p1);
	k = pinv * c1;
	list <int> key;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			k(i, j) = (int)k(i, j) % 26;
			key.push_back(k(i, j));
		}
	}
	k = k.transpose().eval();
	cout << "\n";
	cout << "---------------------------------------------------------------------------" << endl;
	cout << k << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	return key;
};

list <int> hillcipher::encrypt(list <int> plain, list<int> key)
{
	if (key.size() == 9)
	{
		Eigen::MatrixXd K(3, 3);
		int size1 = plain.size();
		for (int i = 0; i < plain.size() % 3; i++)
		{
			plain.push_back(0);
		}
		Eigen::MatrixXd P(3, plain.size() / 3);
		Eigen::MatrixXd C(3, plain.size() / 3);
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				K(i, j) = key.front();
				key.pop_front();
			}
			for (int k = 0; k < (size1 / 3); k++)
			{
				P(i, k) = plain.front();
				plain.pop_front();
			}
		}
		list <int> cipher;
		cout << "key" << endl << K << endl;
		cout << "plain" << endl << P.col(0) << endl;
		cout << "--------------------------------------------------" << endl;
		for (int i = 0; i < size1 / 3; i++)
		{
			C.col(i) = K * P.col(i);
		}
		for (int i = 0; i < 3; i++)
		{
			for (int k = 0; k < (size1 / 3); k++)
			{
				C(i, k) = (int)C(i, k) % 26;
				cipher.push_back(C(i, k));
			}
		}
		cout << C << endl;
		return cipher;
	}
	if (key.size() == 4)
	{
		Eigen::MatrixXd K(2, 2);
		int size1 = plain.size();
		for (int i = 0; i < plain.size() % 2; i++)
		{
			plain.push_back(0);
		}
		Eigen::MatrixXd P(2, plain.size() / 2);
		Eigen::MatrixXd C(2, plain.size() / 2);
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				K(i, j) = key.front();
				key.pop_front();
			}
			for (int k = 0; k < (size1 / 2); k++)
			{
				P(i, k) = plain.front();
				plain.pop_front();
			}
		}
		list <int> cipher;
		cout << "key" << endl << K << endl;
		cout << "plain" << endl << P << endl;
		cout << "--------------------------------------------------" << endl;
		for (int i = 0; i < size1 / 2; i++)
		{
			C.col(i) = K * P.col(i);
		}
		for (int i = 0; i < 2; i++)
		{
			for (int k = 0; k < (size1 / 2); k++)
			{
				C(i, k) = (int)C(i, k) % 26;
			}
		}
		cout << C << endl;
		return cipher;
	}
	else
	{
		cout << "invalid key " << endl;
		exit(0);
	}
}

list <int> hillcipher::decrypt(list <int> cipher, list <int> key)
{
	if (key.size() == 9)
	{
		Eigen::MatrixXd K(3, 3);
		int size1 = cipher.size();
		for (int i = 0; i < cipher.size() % 3; i++)
		{
			cipher.push_back(0);
		}
		Eigen::MatrixXd C(3, cipher.size() / 3);
		Eigen::MatrixXd P(3, cipher.size() / 3);
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				K(i, j) = key.front();
				key.pop_front();
			}
			for (int k = 0; k < (size1 / 3); k++)
			{
				C(i, k) = cipher.front();
				cipher.pop_front();
			}
		}
		list <int> plain;
		cout << "key" << endl << K << endl;
		cout << "cipher" << endl << C << endl;
		cout << "--------------------------------------------------" << endl;
		K = modular_inverse(K);
		for (int i = 0; i < size1 / 3; i++)
		{
			P.col(i) = K * C.col(i);
		}
		for (int i = 0; i < 3; i++)
		{
			for (int k = 0; k < (size1 / 3); k++)
			{
				P(i, k) = (int)P(i, k) % 26;
				plain.push_back(P(i, k));
			}
		}
		cout << P << endl;
		return plain;
	}
	if (key.size() == 4)
	{
		Eigen::MatrixXd K(2, 2);
		int size1 = cipher.size();
		for (int i = 0; i < cipher.size() % 2; i++)
		{
			cipher.push_back(0);
		}
		Eigen::MatrixXd C(2, cipher.size() / 2);
		Eigen::MatrixXd P(2, cipher.size() / 2);
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				K(i, j) = key.front();
				key.pop_front();
			}
			for (int k = 0; k < (size1 / 2); k++)
			{
				C(i, k) = cipher.front();
				cipher.pop_front();
			}
		}
		list <int> plain;
		cout << "Key" << endl << K << endl;
		cout << "Cipher" << endl << C << endl;
		cout << "--------------------------------------------------" << endl;
		K = modular_inverse2by2(K);
		cout << K << endl;
		for (int i = 0; i < size1 / 2; i++)
		{
			P.col(i) = K * C.col(i);
		}
		for (int i = 0; i < 2; i++)
		{
			for (int k = 0; k < (size1 / 2); k++)
			{
				P(i, k) = (int)P(i, k) % 26;
				plain.push_back(P(i, k));
			}
		}
		cout << P << endl;
		return plain;
	}
	else
	{
		cout << "invalid key " << endl;
		exit(0);
	}
}
