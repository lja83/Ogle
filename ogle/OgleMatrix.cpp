#include <iostream>
#include "OgleMatrix.h"
#include "OgleMath.h"
#include <cstdio>
#include <cassert>
using namespace std;


OgleMatrix::OgleMatrix(const OgleMatrix &copyMe)
{
	copy(copyMe);
}

OgleMatrix & OgleMatrix::operator=(const OgleMatrix & other)
{
	copy(other);
	return *this;
}

OgleMatrix::OgleMatrix(void)
{
	rows = 4;
	columns = 4;
	matrix = new float[rows * columns];
}

OgleMatrix::OgleMatrix(int x, int y)
{
	rows = x;
	columns = y;

	matrix = new float[rows * columns];
}


OgleMatrix::~OgleMatrix(void)
{
	rows = 0;
	columns = 0;
	delete[] matrix;
	matrix = NULL;
}

void OgleMatrix::copy(const OgleMatrix &copyMe)
{
	if (&copyMe == this) {
		return;
	}

	rows = copyMe.rows;
	columns = copyMe.columns;
	matrix = new float[rows * columns];
	memcpy(matrix, copyMe.matrix, (sizeof(float) * (rows * columns)));
}

void OgleMatrix::SetMatrix(const float *newValues)
{
	for(int r = 0; r < rows; r++) {
		for(int c = 0; c < columns; c++) {
			matrix[(r * columns) + c] = newValues[(r * columns) + c];
		}
	}
}

void OgleMatrix::SetIdentity(void)
{
	int oneLocation = 0;
	for(int r = 0; r < rows; r++) {
		for(int c = 0; c < columns; c++) {
			if(c == oneLocation) {
				matrix[(r*columns) + c] = 1.0f;
			} else {
				matrix[(r*columns) + c] = 0.0f;
			}
		}
		oneLocation ++;
	}

	//for(int r = 0; r < rows; r++) {
	//	for(int c = 0; c < rows; c++) {
	//		cout << matrix[(r*columns) + c] << ' ';
	//	}
	//	cout << endl;
	//}
}

OgleMatrix OgleMatrix::MultMatrix(const OgleMatrix &rightTerm)
{
	assert(rows == rightTerm.columns);
	OgleMatrix ret(rows, rows);
	float *tempCol = new float[rows];
	float *tempRow = new float[rows];
	float value;
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < rightTerm.columns; col++) {
			for(int i = 0; i < rows; i++) {
				tempRow[i] = matrix[(row*columns) + i];
				tempCol[i] = rightTerm.matrix[(i*rightTerm.columns) + col];
			}
			value = dotf(tempRow, tempCol, rows);
			ret.matrix[(row * columns) + col] = value;
		}
	}
	delete[] tempCol;
	delete[] tempRow;
	return ret;
}