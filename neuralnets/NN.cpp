#include "Mat.h"
#include "Vect.h"
#include "NNLayer.h"
#include "NN.h"
#include "../platform/Utils.h"
#include <stdio.h>



NN::NN(int num_input) {
	this->num_input = num_input;
	this->num_layers = 0;
	this->layers = 0;
}

int NN::getNumLayers() const {
	return num_layers;
}

NNLayer* NN::getLayer(int n) const {
	return layers[n];
}

void NN::addLayer(int num_output) {
	int old_output = getNumOutput();
	if (num_layers == 0) {
		layers = new NNLayer*[1];
	}
	else {
		NNLayer **old_layers = layers;
		layers = new NNLayer*[num_layers+1];
		for (int i=0; i<num_layers; i++) {
			layers[i] = old_layers[i];
		}
		delete old_layers;
	}
	layers[num_layers] = new NNLayer(old_output, num_output);
	num_layers = num_layers + 1;
}


int NN::getNumInput() const {
	return num_input;
}

int NN::getNumOutput() const {
	if (num_layers == 0) {
		return getNumInput();
	}
	return layers[num_layers-1]->getNumOutput();
}

Vect* NN::forwardPropagate(const Vect *input) {
	if (num_layers == 0) {
		Vect *result = new Vect(input);
		return result;
	}
	Vect *result = (Vect *)input;
	Vect* tempResult = 0;
	for (int i=0; i<num_layers; i++) {
		result = layers[i]->forwardPropagate(result);
		if (tempResult != 0) {
			delete tempResult;
		}
		tempResult = result;
	}
	return result;
}

Vect* NN::backwardPropagate(const Vect *expected_output, const Vect *last_output, float learning_rate) {
	Vect *err = new Vect(last_output);
	err->sub(expected_output);
	for (int n=num_layers-1; n>=0; n--) {
		NNLayer *layer = layers[n];
		Vect *err_in = layer->backwardPropagate(err, learning_rate);
		delete err;
		err = err_in;
	}
	return err;
}



void NN::print() const {
	char buf[32];
	sprintf(buf, "NN(%d)\r\n", num_layers);
	log(buf);
	for (int i=0; i<num_layers; i++) {
		layers[i]->print();
	}
}

//static const float car_race_net_weights12TEST[2][3] = {
//		{-0.19054012,  0.75732634, -0.82117337},
//		{-0.44180573, -0.52005017, -0.61912042}
//};
//static const float car_race_net_biases12TEST[3] = {
//		-0.67861546, -0.56278163, -0.50019205
//};
//static const float car_race_net_weights23TEST[3][2] = {
//		{-0.17790172,  0.08958844},
//        { 0.26170852, -0.50326608},
//        { 0.56101698, -0.76496092}
//};
//static const float car_race_net_biases23TEST[2] = {
//		0.09764059, 0.10069135
//};
static const float car_race_net_weights12TEST[2][1] = {
		{-0.35088017},
		{ 0.47722959}
};
static const float car_race_net_biases12TEST[1] = {
		-1.55983051
};
static const float car_race_net_weights23TEST[1][2] = {
		{-0.31765768, -1.03063498}
};
static const float car_race_net_biases23TEST[2] = {
		-0.87784716, -0.61996188
};


static const float car_race_net_weights12[6][10] = {
   { 2.92982598, -2.59533988,  1.68390812, -6.45044018,  2.21847395,
	 9.09846116,  2.09019814,  7.47994636, -1.55154732,  4.053405  },
   {-0.13951569,  0.16532004,  0.35031744, -0.14538902, -0.14230515,
	-0.04077859,  0.06114672,  0.56549284, -0.98225385, -0.24975129},
   { 1.3779408 , -0.65626776,  0.72276261,  0.91624962,  1.02740159,
	 0.85154398, -1.16521592, -0.7208113 , -6.0999097 ,  0.50902216},
   { 4.94442865,  1.16562836,  0.67292358,  1.8444296 , -0.84909359,
	-0.38658771, -0.68875699, -3.23481914, -4.54541425,  1.73644381},
   { 0.34283657,  3.49122586, -1.07141273,  0.30191829,  1.88195363,
	 1.18214337, -5.25065642, -1.5788444 ,  2.81243613,  1.36685535},
   {-0.05290731, -0.36936821, -1.37291634,  0.35314155,  0.65418381,
	-0.15870702, -0.05026738,  0.27220292,  2.65996218, -0.21896395}
};
static const float car_race_net_weights12ZERO[6][10] = {
  { 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0, 0.0 },
};


static const float car_race_net_biases12[10] = {
   -3.80692954, -0.99609635, -0.760793  ,  3.34655166, -1.14131986,
   -5.14198978,  2.46194382, -3.65475694,  0.59807103, -2.08264843
};
static const float car_race_net_biases12ZERO[10] = {
	0.0, 0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0, 0.0,
};



static const float car_race_net_weights23[10][10] = {
   {-2.95089874e+00,  6.33863210e+00, -5.64784825e-01,
	-1.34862174e-01,  6.32867453e+00, -6.93072053e+00,
	-2.76446263e+00, -4.28698039e+00, -8.03317104e-01,
	 2.76539314e+00},
   { 5.79895095e-01, -9.19510015e+00,  2.33771386e-01,
	 1.32312884e+01,  8.54901934e+00, -5.56905363e-01,
	 3.37500716e+00,  5.79642971e+00,  3.14798403e-01,
	-3.59972036e+00},
   {-1.14265946e+00, -1.35520658e+01, -5.36028785e-03,
	-2.94413770e+00,  4.46875500e+00,  7.85978839e+00,
	-3.05620140e+00,  9.21020632e-01,  1.51585913e-01,
	 3.61368181e+00},
   { 6.45857555e+00, -6.01469394e-01, -1.03160308e+00,
	-2.60155781e+00,  3.66358923e+00,  2.74846385e+00,
	 5.31858144e+00,  1.76314377e+01,  7.10212466e-02,
	-1.06319317e+01},
   {-1.97276685e+00, -2.15927960e+00,  4.15142518e-01,
	-4.21676472e+00,  1.79578768e+00,  8.45763920e+00,
	-6.76088439e+00, -1.40965105e+00, -4.85121956e-02,
	-1.56227099e+00},
   { 3.36960513e+00, -1.44461726e+00, -3.94443030e+00,
	-6.36305430e+00,  1.51471980e-01,  1.15357224e+01,
	-7.88027186e+00,  6.98760934e-01, -1.19283372e+00,
	-4.80561946e+00},
   { 1.26324526e+00, -8.79875175e+00, -1.57579062e+00,
	 9.10906053e+00,  5.52157045e+00,  7.09297928e+00,
	-8.06926747e+00,  5.86703321e+00, -5.09300852e-02,
	-3.98477665e+00},
   { 3.69880541e+00, -1.12316158e+00,  1.35547589e+00,
	 4.70517062e+00,  1.13739045e+01,  6.11269490e+00,
	 6.92073105e+00,  4.49550849e+00,  1.02886093e-01,
	-2.70772383e+00},
   { 2.51334232e-01, -1.13002334e+01, -4.16675575e-01,
	-8.07980143e-01, -4.43702092e-02, -9.85902553e-01,
	 1.04786543e+00,  5.12631959e-01, -2.84400132e-01,
	 1.98691284e+00},
   { 3.52555263e+00,  1.71847070e+01,  3.62415484e+00,
	-6.37929472e+00,  3.25595435e+00, -2.43483794e+00,
	 1.65547364e+00,  3.05531071e+00,  1.97123054e+00,
	-2.17144239e+00}
};
static const float car_race_net_weights23ZERO[10][10] = {
  { 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0, 0.0 },
};

static const float car_race_net_biases23[10] = {
	-2.57641358,   5.22974549,   0.18196597,   3.55930069,
	 7.76041084, -10.3746859 ,   5.17933678, -14.01284557,
	 0.27489897,   0.22506589
};
static const float car_race_net_biases23ZERO[10] = {
	1.0, -0.1, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0, 0.0,
};


static const float car_race_net_weights34[10][3] = {
   {  0.30475765,  -3.72432552,   2.89807721},
   {  2.47523919,  -0.07113565,  -2.34002766},
   {  6.47865935,  -3.58909989,  -4.11516189},
   { -7.46690826,   2.18849342,   5.37326228},
   {  1.69779199,  -2.94359089,   0.5098125 },
   {  2.33500901,  -2.59166875,   0.43530021},
   {  1.29487568,  -2.89745911,   0.87452631},
   {  1.37053505,   1.68520382,  -2.80015337},
   {-12.1493566 ,   3.98479873,   9.31744796},
   { -3.46432305,  -2.00026348,   3.62938781}
};
static const float car_race_net_weights34ZERO[10][3] = {
  { 1.0, 2.0, 1.0 },
  { 1.0, 2.0, 1.0 },
  { 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0 },
  { 0.0, 0.0, 0.0 },
};

static const float car_race_net_biases34[3] = {
  -3.91892902, -3.24655446,  6.87568216
};
static const float car_race_net_biases34ZERO[3] = {
  0.0, 0.0, 0.0,
};



void set_weights(Mat* weights, float* data) {
	for (int r=0; r<weights->getRows(); r++) {
		for (int c=0; c<weights->getCols(); c++) {
			weights->set(r, c, *data);
			data++;
		}
	}
//	for (int c=0; c<weights->getCols(); c++) {
//		for (int r=0; r<weights->getRows(); r++) {
//			weights->set(r, c, *data);
//			data++;
//		}
//	}
}

void set_biases(Vect* biases, float* data) {
	for (int i=0; i<biases->getLength(); i++) {
		biases->set(i, *data);
		data++;
	}
}


void NN::init_car_race_net() {
	set_weights(layers[0]->getWeights(), (float*) car_race_net_weights12);
	set_biases(layers[0]->getBiases(), (float*) car_race_net_biases12);
	set_weights(layers[1]->getWeights(), (float*) car_race_net_weights23);
	set_biases(layers[1]->getBiases(), (float*) car_race_net_biases23);
	set_weights(layers[2]->getWeights(), (float*) car_race_net_weights34);
	set_biases(layers[2]->getBiases(), (float*) car_race_net_biases34);
}


void NN::init_car_race_netZERO() {
	set_weights(layers[0]->getWeights(), (float*) car_race_net_weights12ZERO);
	set_biases(layers[0]->getBiases(), (float*) car_race_net_biases12ZERO);
	set_weights(layers[1]->getWeights(), (float*) car_race_net_weights23ZERO);
	set_biases(layers[1]->getBiases(), (float*) car_race_net_biases23ZERO);
	set_weights(layers[2]->getWeights(), (float*) car_race_net_weights34ZERO);
	set_biases(layers[2]->getBiases(), (float*) car_race_net_biases34ZERO);
}


void NN::init_car_race_netTEST() {
	set_weights(layers[0]->getWeights(), (float*) car_race_net_weights12TEST);
	set_biases(layers[0]->getBiases(), (float*) car_race_net_biases12TEST);
	set_weights(layers[1]->getWeights(), (float*) car_race_net_weights23TEST);
	set_biases(layers[1]->getBiases(), (float*) car_race_net_biases23TEST);
}


NN::~NN() {
	for (int i=0; i<num_layers; i++) {
		delete layers[i];
	}
	num_layers = 0;
	delete layers;
	layers = 0;
}

