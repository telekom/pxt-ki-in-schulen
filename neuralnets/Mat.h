#ifndef MAT_H
#define MAT_H

class Vect;

class Mat
{
	int     nRows;
	int     nCols;
	float   *data;

public:

	Mat(int rows, int cols);
	Mat(const Mat *mat);
	Mat(const Mat& mat);
	Mat(int rows, int cols, const float *data);
	int getCols() const;
	int getRows() const;
	float get(int row, int col) const;
	void set(int row, int col, float v);
	Mat* transpose();

	void add(const Mat *mat);
	void sub(const Mat *mat);

	Mat* multiply(Mat *mat);
	Mat* multiplyT(Mat *mat);

	void multiply(float f);

	void addR(Vect *vect);
	void addC(Vect *vect);

	void print() const;

	~Mat();
};

#endif
