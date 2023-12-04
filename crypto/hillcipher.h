#pragma once
#include <Eigen/Dense>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;
class hillcipher
{
public:
	int smallerdet(int row, int col, Eigen::Matrix3d M);
	Eigen::Matrix3d modular_inverse(Eigen::Matrix3d K);
	Eigen::Matrix2d modular_inverse2by2(Eigen::Matrix2d K);
	list <int> analyse3by3(list <int> plain, list <int> cipher);
	list <int> analyse(list <int> plain, list <int> cipher);
	list <int> encrypt(list <int> plain, list<int> key);
	list <int> decrypt(list <int> cipher, list <int> key);

};

