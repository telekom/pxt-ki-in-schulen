#include "Mat.h"
#include "Vect.h"
#include "../platform/Utils.h"
#include <stdio.h>


Mat::Mat(int rows, int cols)
{
	this->nRows = rows;
	this->nCols = cols;
	data = new float[rows*cols];
}

Mat::Mat(const Mat *mat)
{
	this->nRows = mat->getRows();
	this->nCols = mat->getCols();
	int size = nRows * nCols;
	this->data = new float[size];
	for (int i = 0; i < size; i++) {
		data[i] = mat->data[i];
	}
}

Mat::Mat(const Mat& mat)
{
	this->nRows = mat.getRows();
	this->nCols = mat.getCols();
	int size = nRows * nCols;
	this->data = new float[size];
	for (int i = 0; i < size; i++) {
		data[i] = mat.data[i];
	}
}

Mat::Mat(int rows, int cols, const float *data) {
	this->nRows = rows;
	this->nCols = cols;
	int size = nRows*nCols;
	this->data = new float[size];
	for (int i=0; i<size; i++) {
		this->data[i] = data[i];
	}
}

int Mat::getCols() const
{
	return nCols;
}

int Mat::getRows() const
{
	return nRows;
}

float Mat::get(int row, int col) const
{
	if (row < 0 || col < 0 || row >= nRows || col >= nCols) {
	    print();
		char buf[100];
		sprintf(buf, "\r\nrow: %d, col: %d\r\n", row, col);
		log(buf);
		throwError("Mat::get: index out of range");
	}
	return data[row*nCols + col];
}

void Mat::set(int row, int col, float v)
{
	if (row < 0 || col < 0 || row >= nRows || col >= nCols) {
	    print();
		char buf[100];
		sprintf(buf, "\r\nrow: %d, col: %d\r\n", row, col);
		log(buf);
		throwError("Mat::set: index out of range");
	}
	data[row*nCols + col] = v;
}

Mat* Mat::transpose()
{
	Mat* result = new Mat(nCols, nRows);
	for (int r = 0; r < nRows; r++) {
		for (int c = 0; c < nCols; c++) {
			result->set(c, r, get(r, c));
		}
	}
	return result;
}


void Mat::add(const Mat *mat) {
	if (getRows()!=mat->getRows() || getCols()!=mat->getCols() ) {
		print();
		mat->print();
		throwError("Mat::add: cols and rows do not match");
	}
	for (int r=0; r<nRows; r++) {
		for (int c=0; c<nCols; c++) {
			set(r,c, get(r,c)+mat->get(r,c));
		}
	}
}

void Mat::sub(const Mat *mat) {
	if (getRows()!=mat->getRows() || getCols()!=mat->getCols() ) {
		print();
		mat->print();
		throwError("Mat::sub: cols and rows do not match");
	}
	for (int r=0; r<nRows; r++) {
		for (int c=0; c<nCols; c++) {
			set(r,c, get(r,c)-mat->get(r,c));
		}
	}
}

Mat* Mat::multiply(Mat *matrix)
{
    int co = nCols;
    int ro = nRows;
	if (co != matrix->getRows()) {
		print();
		matrix->print();
		throwError("Mat::multiply: cols and rows do not match");
	}
	Mat *result = new Mat(ro, matrix->getCols());
	for (int r = 0; r < result->getRows(); r++)
	{
		for (int c = 0; c < result->getCols(); c++)
		{
			float v = 0.0;
			for (int i = 0; i < co; i++) {
				v += get(r, i) * matrix->get(i, c);
			}
			result->set(r, c, v);
		}
	}
	return result;
}


Mat* Mat::multiplyT(Mat *matrix)
{
    int co = nRows;
    int ro = nCols;
	if (co != matrix->getRows()) {
		print();
		matrix->print();
		log("TRANSPOSE\r\n");
		throwError("Mat::multiply: cols and rows do not match");
	}
	Mat *result = new Mat(ro, matrix->getCols());
	for (int r = 0; r < result->getRows(); r++)
	{
		for (int c = 0; c < result->getCols(); c++)
		{
			float v = 0.0;
			for (int i = 0; i < co; i++) {
				v += get(i, r) * matrix->get(i, c);
			}
			result->set(r, c, v);
		}
	}
	return result;
}


void Mat::multiply(float f) {
	for (int r=0; r<nRows; r++) {
		for (int c=0; c<nCols; c++) {
			set(r, c, get(r,c)*f);
		}
	}
}


void Mat::addR(Vect *vect) {
	if (vect->getLength() != nCols) {
		print();
		vect->print();
		throwError("Mat::addR: cols and vector-length do not match.");
	}
	for (int r=0; r<nRows; r++) {
		for (int i=0; i<nCols; i++) {
			float v = get(r,i) + vect->get(i);
			set(r, i, v);
		}
	}
}

void Mat::addC(Vect *vect) {
	if (vect->getLength() != nRows) {
		print();
		vect->print();
		throwError("Mat::addR: rows and vector-length do not match.");
	}
	for (int i=0; i<nRows; i++) {
		for (int c=0; c<nCols; c++) {
			float v = get(i,c) + vect->get(i);
			set(i, c, v);
		}
	}
}



void Mat::print() const {
	log("MAT\r\n");
	char buf[100];
	for (int r=0; r<nRows; r++) {
		for (int c=0; c<nCols; c++) {
			float v = get(r,c);
			int len = float2char(buf, v, 4);
			for (int i=len; i<10; i++) {
				log(" ");
			}
			log(buf);
		}
		log("\r\n");
	}
	log("\r\n");
}


Mat::~Mat()
{
	delete data;
	data = 0;
}
