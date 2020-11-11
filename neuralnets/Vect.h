#ifndef VECT_H
#define VECT_H

class Mat;

class Vect
{
	int     length;
	float   *data;

public:

	Vect(int length);
	Vect(int length, const float* data);
	Vect(const Vect *vect);
	Vect(const Vect& vect);
	Vect(const Mat *mat);
	int getLength() const;
	float get(int n) const;
	void set(int n, float v);
	void multiply(const Vect *vect);
	void add(const Vect *vect);
	void sub(const Vect *vect);
	void sqr();
	float sum();
	Vect* multiplyR(const Mat *mat) const;
	Vect* multiplyC(const Mat *mat) const;
	Mat* multiplyRC(const Vect *vect) const;
	Mat* multiplyCR(const Vect *vect) const;


	void multiply(float f);

	Mat* toMatRow() const;
	Mat* toMatCol() const;

	void insert(float value, int pos=-1);

	void print() const;

	~Vect();
};


#endif
