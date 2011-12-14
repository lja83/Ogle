#pragma once
class OgleMatrix
{
private:
	int rows;
	int columns;
	float *matrix;
public:
	OgleMatrix(void);
	OgleMatrix(const OgleMatrix &copyMe);
	OgleMatrix(int x, int y);
	~OgleMatrix(void);
	OgleMatrix & OgleMatrix::operator=(const OgleMatrix & other);
	void copy(const OgleMatrix & copyMe);

	int GetRows(void) { return rows; };
	int GetColumns(void) { return columns; }
	const float *GetRawMatrix(void) { return matrix; };
	void Set(int r, int c, float newValue) {matrix[(r*columns) + c] = newValue; }

	void SetIdentity(void);
	void SetMatrix(const float *newValues);
	OgleMatrix MultMatrix(const OgleMatrix &rightTerm);
};

