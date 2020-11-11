#include "Vect.h"
#include "Mat.h"
#include "../platform/Utils.h"
#include <stdio.h>


Vect::Vect(int length)
{
	this->length = length;
	data = new float[length];
}

Vect::Vect(const Vect *vect)
{
	this->length = vect->length;
	data = new float[length];
	for (int i = 0; i < length; i++)
		data[i] = vect->data[i];
}

Vect::Vect(int length, const float* data) {
	this->length = length;
	this->data = new float[length];
	for (int i = 0; i < length; i++)
		this->data[i] = data[i];
}

Vect::Vect(const Vect& copyVect)
{
	this->length = copyVect.getLength();
	data = new float[length];
	for (int i = 0; i < length; i++)
		data[i] = copyVect.data[i];
}

Vect::Vect(const Mat *mat)
{
	if (mat->getRows() == 1) {
		length = mat->getCols();
		data = new float[length];
		for (int i = 0; i < length; i++) {
			data[i] = mat->get(0, i);
		}
	}
	else if (mat->getCols() == 1) {
		length = mat->getRows();
		data = new float[length];
		for (int i = 0; i < length; i++) {
			data[i] = mat->get(i,0);
		}
	}
	else {
		print();
		mat->print();
		throwError("Vect::Vect: matrix has too many rows/cols");
	}
}

int Vect::getLength() const
{
	return length;
}

float Vect::get(int n) const
{
	if (n < 0 || n >= length) {
	    print();
		char buf[100];
		sprintf(buf, "\r\nn: %d\r\n", n);
		log(buf);
		throwError("Vect::get: index out of range");
	}
	return data[n];
}

void Vect::set(int n, float v)
{
	if (n < 0 || n >= length) {
	    print();
		char buf[100];
		sprintf(buf, "\r\nn: %d\r\n", n);
		log(buf);
		throwError("Vect::set: index out of range");
	}
	data[n] = v;
}

void Vect::multiply(const Vect *vect) {
	if (vect->length != length) {
		print();
		vect->print();
		throwError("Vect::multiply: langth mismatch");
	}
	for (int i = 0; i < length; i++)
	{
		set(i, get(i)*vect->get(i));
	}
}

void Vect::add(const Vect *vect) {
	if (vect->length != length) {
		print();
		vect->print();
		throwError("Vect::add: length mismatch");
	}
	for (int i = 0; i < length; i++)
	{
		set(i, get(i)+vect->get(i));
	}
}

void Vect::sub(const Vect *vect) {
	if (vect->length != length) {
		print();
		vect->print();
		throwError("Vect::sub: length mismatch");
	}
	for (int i = 0; i < length; i++)
	{
		set(i, get(i)-vect->get(i));
	}
}

void Vect::sqr() {
	for (int i = 0; i < length; i++)
	{
		set(i, get(i)*get(i));
	}
}

float Vect::sum() {
	float result = 0.0f;
	for (int i = 0; i < length; i++)
	{
		result += get(i);
	}
	return result;
}

Vect* Vect::multiplyR(const Mat *mat) const {
	if (mat->getCols() != length) {
		print();
		mat->print();
		throwError("Vect::multiplyC: length mismatch");
	}
	Vect *result = new Vect(mat->getRows());
	for (int r=0; r<mat->getRows(); r++) {
		float v=0;
		for (int i=0; i<length; i++) {
			v += get(i) * mat->get(r,i);
		}
		result->set(r, v);
	}
	return result;
}


Vect* Vect::multiplyC(const Mat *mat) const {
	if (mat->getRows() != length) {
		print();
		mat->print();
		throwError("Vect::multiplyR: length mismatch");
	}
	Vect *result = new Vect(mat->getCols());
	for (int c=0; c<mat->getCols(); c++) {
		float v=0;
		for (int i=0; i<length; i++) {
			v += get(i) * mat->get(i,c);
		}
		result->set(c, v);
	}
	return result;
}

Mat* Vect::multiplyCR(const Vect *vect) const {
	Mat* result = new Mat(vect->getLength(), getLength());
	for (int r=0; r<vect->getLength(); r++) {
		for (int c=0; c<getLength(); c++) {
			result->set(r,c, vect->get(r)*get(c));
		}
	}
	return result;
}


Mat* Vect::multiplyRC(const Vect *vect) const {
	Mat* result = new Mat(getLength(), vect->getLength());
	for (int r=0; r<getLength(); r++) {
		for (int c=0; c<vect->getLength(); c++) {
			result->set(r,c, get(r)*vect->get(c));
		}
	}
	return result;
}



void Vect::multiply(float f) {
	for (int i=0; i<length; i++) {
		set(i, get(i)*f);
	}
}


Mat* Vect::toMatRow() const {
	return new Mat(1, length, data);
}

Mat* Vect::toMatCol() const {
	return new Mat(length, 1, data);
}


void Vect::insert(float value, int pos) {
	if (pos == -1) {
		pos = length;
	}
	float *oldData = data;
	data = new float[length+1];
	for (int i=0; i<pos; i++) {
		data[i] = oldData[i];
	}
	data[pos] = value;
	for (int i=pos; i<length; i++) {
		data[i+1] = oldData[i];
	}
	length++;
	delete oldData;
}


void Vect::print() const {
	log("VECT\r\n");
	char buf[100];
	for (int i=0; i<length; i++) {
		float v = get(i);
		int len = float2char(buf, v, 4);
		for (int i=len; i<10; i++) {
			log(" ");
		}
		log(buf);
	}
	log("\r\n");
}


Vect::~Vect()
{
	delete data;
	data = 0;
}
