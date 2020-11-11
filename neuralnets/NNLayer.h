#ifndef NNLAYER_H
#define NNLAYER_H

class Mat;
class Vect;

const int NNL_ACT_FUN_NONE=0, NNL_ACT_FUN_RELU=1, NNL_ACT_FUN_SIGMOID=2, NNL_ACT_FUN_SOFTMAX=3, NNL_ACT_FUN_TANHYP=4, NNL_ACT_FUN_UNDEF=99;

class NNLayer
{
	int num_input;
	int num_output;
	Mat *w;
	Vect *b;
	Vect *_z;
	Vect *_x;
	int act_fun;

public:

	NNLayer(int num_input, int num_output) : NNLayer(num_input, num_output, NNL_ACT_FUN_NONE) {}
	NNLayer(int num_input, int num_output, int activation_function);

	void setActivationFunction(int activation_function);

	Vect* forwardPropagate(const Vect* input);
	Vect* backwardPropagate(const Vect *e, float lr);

	int getNumInput() const;
	int getNumOutput() const;

	void print() const;

	Mat* getWeights() const;
	Vect* getBiases() const;

	~NNLayer();
};


#endif  // NNLAYER_H
