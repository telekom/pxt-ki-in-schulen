#include "Mat.h"
#include "Vect.h"
#include "NNLayer.h"
#include "NNUtils.h"
#include "../platform/Utils.h"
#include <stdio.h>
#include <math.h>


NNLayer::NNLayer(int num_input, int num_output, int activation_function) {
	this->num_input = num_input;
	this->num_output = num_output;
	w = new Mat(num_input, num_output);
	fillRandomNorm(w, -1.0f, 1.0f);
	w->multiply(sqrt(2.0f/num_input));
	b = new Vect(num_output);
	fill(b, 0.1f);
	_x = 0;
	_z = 0;
	act_fun = activation_function;
}

void NNLayer::setActivationFunction(int activation_function) {
	act_fun = activation_function;
}

int NNLayer::getNumInput() const {
	return num_input;
}

int NNLayer::getNumOutput() const {
	return num_output;
}


Vect* NNLayer::forwardPropagate(const Vect *x) {
	if (_x != 0) {
		delete _x;
		delete _z;
	}
	_x = new Vect(x);
	_z = x->multiplyC(w);
//log("MULTIPLY x*W = ");
//_z->print();
	_z->add(b);
//log("MULTIPLY x*W+b = ");
//_z->print();
	Vect *result = new Vect(_z);

	switch(act_fun) {
		case NNL_ACT_FUN_NONE:
			break;
		case NNL_ACT_FUN_RELU:
			relu(result);
			break;
		case NNL_ACT_FUN_SIGMOID:
			sigmoid(result);
			break;
		case NNL_ACT_FUN_SOFTMAX:
			softmax(result);
			break;
		case NNL_ACT_FUN_TANHYP:
			tanhyp(result);
			break;
	}

//log("ACT:");
//logInt(act_fun);
//result->print();
	return result;
}

Vect* NNLayer::backwardPropagate(const Vect *e, float lr) {
	if (_z == 0) {
		print();
		throwError("calling backProp without haveing called forwardProp.");
	}
	Vect *e_zrp = new Vect(_z);
	relu_prime(e_zrp);
	e_zrp->multiply(e);
	Mat *dw = e_zrp->multiplyCR(_x);
	dw->multiply(lr);
	w->sub(dw);
	Vect* e_in = e->multiplyR(w);
	delete e_zrp;
	delete dw;
	return e_in;
}

void NNLayer::print() const {
	char buf[64];
	const char*act;
	switch (act_fun) {
	case NNL_ACT_FUN_NONE:
		act="";
		break;
	case NNL_ACT_FUN_RELU:
		act="act=relu";
		break;
	case NNL_ACT_FUN_SIGMOID:
		act="act=sigmoid";
		break;
	case NNL_ACT_FUN_SOFTMAX:
		act="act=softmax";
		break;
	case NNL_ACT_FUN_TANHYP:
		act="act=tanh";
		break;
	default:
		act = "act=???";
	}
	sprintf(buf, "NNLayer(%d, %d) %s\r\n", num_input, num_output, act);
	log(buf);
	w->print();
	b->print();
}


Mat* NNLayer::getWeights() const {
	return w;
}

Vect* NNLayer::getBiases() const {
	return b;
}


NNLayer::~NNLayer() {
	if (_x != 0) {
		delete _x;
		delete _z;
		_x=0;
		_z=0;
	}
	delete w;
	delete b;
	w = 0;
	b = 0;
}
