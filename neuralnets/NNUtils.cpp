#ifndef NNUTILS_H
#define NNUTILS_H

#include "Vect.h"
#include "Mat.h"

#include<stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


void initRand() {
	 time_t t;
	 srand((unsigned) time(&t));
	 rand(); rand(); rand();
}

void fillRandom(Mat* mat, float from, float to) {
	float diff = to-from;
	int maxR = mat->getRows();
	int maxC = mat->getCols();
	for (int r=0; r<maxR; r++) {
		for (int c=0; c<maxC; c++) {
			float v = ((float) (rand() % 1001))/1001.0f;
			float vRange = from+diff*v;
			mat->set(r, c, vRange);
		}
	}
}

void fillRandom(Vect* vect, float from, float to) {
	float diff = to-from;
	for (int i=0; i<vect->getLength(); i++) {
		float v = ((float) (rand() % 1001))/1001.0f;
		float vRange = from+diff*v;
		vect->set(i, vRange);
	}
}

void fillRandomNorm(Mat* mat, float from, float to) {
	float diff = to-from;
	int maxR = mat->getRows();
	int maxC = mat->getCols();
	for (int r=0; r<maxR; r++) {
		for (int c=0; c<maxC; c++) {
			float v = ((float) ((rand() % 1001)+(rand() % 1001)+(rand() % 1001)))/3003.0;
			float vRange = from+diff*v;
			mat->set(r, c, vRange);
		}
	}
}

void fillRandomNorm(Vect* vect, float from, float to) {
	float diff = to-from;
	for (int i=0; i<vect->getLength(); i++) {
		float v = ((float) ((rand() % 1001)+(rand() % 1001)+(rand() % 1001)))/3003.0;
		float vRange = from+diff*v;
		vect->set(i, vRange);
	}
}


void fill(Vect* vect, float v) {
	for (int i=0; i<vect->getLength(); i++) {
		vect->set(i, v);
	}
}

void fill(Mat* mat, float v) {
	for (int r=0; r<mat->getRows(); r++) {
		for (int c=0; c<mat->getRows(); r++) {
			mat->set(r,c, v);
		}
	}
}


float relu(float f) {
	if (f<0.0f) {
		return 0.0f;
	}
	return f;
}

void relu(Vect *vect) {
	for (int i=0; i<vect->getLength(); i++) {
		vect->set(i, relu(vect->get(i)));
	}
}

float tanhyp(float f) {
	return tanh(f);
}

void tanhyp(Vect *vect) {
	for (int i=0; i<vect->getLength(); i++) {
		vect->set(i, tanhyp(vect->get(i)));
	}
}

float sigmoid(float f) {
	return 1/(1+pow(2.71828182845905f, -f));
}

void sigmoid(Vect *vect) {
	for (int i=0; i<vect->getLength(); i++) {
		vect->set(i, sigmoid(vect->get(i)));
	}
}

void softmax(Vect *vect) {
	float sum = 0.0f;
	for (int i=0; i<vect->getLength(); i++) {
		float exp = pow(2.71828182845905f, vect->get(i));
		sum = sum + exp;
		vect->set(i, exp);
	}
	if (sum != 0.0f) {
		for (int i=0; i<vect->getLength(); i++) {
			vect->set(i, vect->get(i)/sum);
		}
	}
}

float relu_prime(float f) {
	if (f<0.0f) {
		return 0.0f;
	}
	return 1.0f;
}

void relu_prime(Vect *vect) {
	for (int i=0; i<vect->getLength(); i++) {
		vect->set(i, relu_prime(vect->get(i)));
	}
}

Vect createVect(int length, ...) {
	va_list argp;
	va_start(argp, length);
	Vect result = Vect(length);
	for (int i=0; i<length; i++) {
		float f = va_arg(argp, double);
		result.set(i, f);
	}
	va_end(argp);
	return result;
}

Mat createMat(int rows, int cols, ...) {
	va_list argp;
	va_start(argp, cols);
	Mat result = Mat(rows, cols);
	for (int r=0; r<rows; r++) {
		for (int c=0; c<cols; c++) {
			float f = va_arg(argp, double);
			result.set(r,c, f);
		}
	}
	va_end(argp);
	return result;
}





#endif // NNUTILS_H
