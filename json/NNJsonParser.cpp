/*
 * NNJsonParser.cpp
 *
 *  Created on: 29.02.2020
 *      Author: A307131
 */

#include "NNJsonParser.h"
#include "../platform/Utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../neuralnets/NN.h"
#include "../neuralnets/NNLayer.h"
#include "../neuralnets/Vect.h"
#include "../neuralnets/Mat.h"



NNJsonParser::NNJsonParser() {
	this->current_list = NONE;
	this->nn = 0;
	this->layers = new Vect(0);
	this->activation_function = NNL_ACT_FUN_UNDEF;
}


void NNJsonParser::init() {
}

void NNJsonParser::beginObject(const char* name) {
}


void NNJsonParser::endObject() {
}

void NNJsonParser::beginList(const char* name) {
	if (current_list != NONE) {
		element_level++;
		element_pos[element_level] = 0;
		return;
	}
	if (name == 0) {
		return;
	}
	if (strcmp(name, "layers") == 0) {
		current_list = ELEM_LAYERS;
	}
	else if (strcmp(name, "coefs") == 0) {
		initNN();
		current_list = ELEM_COEFS;
	}
	else if (strcmp(name, "intercepts") == 0) {
		current_list = ELEM_INTERCEPTS;
	}
	else {
		return;
	}
	element_level = 0;
	element_pos[element_level] = 0;
	log("reading ");
	log(name);
	log("\r\n");
//	logInt(element_level);
//	log(":");
//	logInt(element_pos[element_level]);
//	log("\r\n");
}

void NNJsonParser::endList() {
	if (current_list == NONE) {
		return;
	}
	element_level--;
	if (element_level < 0) {
		if (current_list == ELEM_LAYERS) {
			log("LAYERS:");
			layers->print();
		}
		current_list = NONE;
	}
	else {
		element_pos[element_level]++;
	}
}

void NNJsonParser::attribute(const char* name, const char* value) {
	if (strcmp(name, "act") == 0) {
		if (strcmp(value, "relu") == 0) {
			activation_function = NNL_ACT_FUN_RELU;
		}
		else if (strcmp(value, "tanh") == 0) {
			activation_function = NNL_ACT_FUN_TANHYP;
		}
		else if (strcmp(value, "sigmoid") == 0) {
			activation_function = NNL_ACT_FUN_SIGMOID;
		}
		else if (strcmp(value, "softmax") == 0) {
			activation_function = NNL_ACT_FUN_SOFTMAX;
		}
		else if (strcmp(value, "none") == 0) {
			activation_function = NNL_ACT_FUN_NONE;
		}
		else {
			char errMsg[100];
			sprintf(errMsg, "unknown activation function: '%s'", value);
			throwError(errMsg);
		}
	}

}

void NNJsonParser::element(const char* value) {
	switch (current_list) {
	case NONE:
		break;
	case ELEM_LAYERS: {
		int int_value = atoi(value);
		layers->insert(int_value);
		break;
	}
	case ELEM_COEFS: {
		NNLayer *layer = nn->getLayer(element_pos[0]);
		float f = char2float(value);
		layer->getWeights()->set(element_pos[1], element_pos[2], f);
		element_pos[element_level]++;
		break;
	}
	case ELEM_INTERCEPTS: {
		NNLayer *layer = nn->getLayer(element_pos[0]);
		float f = char2float(value);
		layer->getBiases()->set(element_pos[1], f);
		element_pos[element_level]++;
		break;
	}
	default:
		break;
	}
}


void NNJsonParser::unexpected(int char_pos) {
	char buf[100];
	sprintf(buf, "json error before character %d!", char_pos);
	throwError(buf);
}

void NNJsonParser::exit() {
}

void* NNJsonParser::getResult() {
	return nn;
}

void NNJsonParser::initNN() {
	if (nn != 0) {
		return;
	}
	if (layers->getLength() < 3) {
		throwError("invalid layers element (at least 3 layers are required: [input, hidden, output]!");
	}
	if (activation_function == NNL_ACT_FUN_UNDEF) {
		throwError("activation function not found in header!");
	}

	nn = new NN(layers->get(0));
	for (int i=1; i<layers->getLength()-1; i++) {
		nn->addLayer(layers->get(i));
	}
	nn->addLayer(layers->get(layers->getLength()-1));

	for (int i=0; i<nn->getNumLayers()-1; i++) {
		nn->getLayer(i)->setActivationFunction(activation_function);
	}
	nn->getLayer(nn->getNumLayers()-1)->setActivationFunction(NNL_ACT_FUN_SOFTMAX);
//	nn->getLayer(nn->getNumLayers()-1)->setActivationFunction(NNL_ACT_FUN_NONE);

}


NNJsonParser::~NNJsonParser() {
	delete layers;
	layers = 0;
}

