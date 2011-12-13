#include <iostream>
#include "OgleMatrix.h"
#include "OgleMath.h"
#include <cstdio>
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

OgleMatrix OgleMatrix::MultMatrix(const OgleMatrix &rightTerm)
{
	OgleMatrix ret(rows, columns);
	float tempCol[4];
	float tempRow[4];
	float value;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			for(int i = 0; i < 4; i++) {
				tempRow[i] = matrix[(row*4) + i];
				tempCol[i] = rightTerm.matrix[(i*4) + col];
			}
			value = dotf(tempRow, tempCol, 4);
			ret.matrix[(row * columns) + col] = value;
			std::cout << row << ' ' << col << ' ' << value << std::endl;
		}
	}
	std::cout << "ret.matrix[0]: " << ret.GetRawMatrix()[0] << std::endl;
	return ret;
}