#ifndef NN_H
#define NN_H

class Vect;
class NNLayer;

class NN
{
	int num_input;
	int num_layers;
	NNLayer **layers;

public:

	NN(int num_input);
	void addLayer(int num_output);

	int getNumLayers()  const;
	NNLayer* getLayer(int n)  const;

	int getNumInput() const;
	int getNumOutput() const;

	Vect* forwardPropagate(const Vect *input);
	Vect* backwardPropagate(const Vect *expected_output, const Vect *last_output, float learning_rate);

	void print() const;

	void init_car_race_net();
	void init_car_race_netZERO();
	void init_car_race_netTEST();

	~NN();
};


#endif  // NNLAYER_H
