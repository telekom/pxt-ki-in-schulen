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
	this->input_size = 0;
	this->hidden_layers_size = new Vect(0);
	this->output_size = 0;
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
	if (strcmp(name, "hidden_layer_sizes") == 0) {
		current_list = ELEM_HIDDEN_LAYERS_SIZE;
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
		if (current_list == ELEM_HIDDEN_LAYERS_SIZE) {
			log("HIDDEN_LAYERS:");
			hidden_layers_size->print();
		}
		current_list = NONE;
	}
	else {
		element_pos[element_level]++;
	}
}

void NNJsonParser::attribute(const char* name, const char* value) {
	if (strcmp(name, "input_layer_size") == 0) {
		input_size = atoi(value);
		log(name);
		log("=");
		logInt(input_size);
		log("\r\n");
	}
	else if (strcmp(name, "output_layer_size") == 0) {
		output_size = atoi(value);
		log(name);
		log("=");
		logInt(output_size);
		log("\r\n");
	}
	else if (strcmp(name, "activation") == 0) {
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
	case ELEM_HIDDEN_LAYERS_SIZE: {
		int int_value = atoi(value);
		hidden_layers_size->insert(int_value);
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
	if (input_size == 0) {
		throwError("input_layer_size not found in header!");
	}
	if (output_size == 0) {
		throwError("output_layer_size not found in header!");
	}
	if (hidden_layers_size->getLength() == 0) {
		throwError("hidden_layer_sizes not found in header!");
	}
	if (activation_function == NNL_ACT_FUN_UNDEF) {
		throwError("activation function not found in header!");
	}

	nn = new NN(input_size);
	for (int i=0; i<hidden_layers_size->getLength(); i++) {
		nn->addLayer(hidden_layers_size->get(i));
	}
	nn->addLayer(output_size);

	for (int i=0; i<nn->getNumLayers()-1; i++) {
		nn->getLayer(i)->setActivationFunction(activation_function);
	}
	nn->getLayer(nn->getNumLayers()-1)->setActivationFunction(NNL_ACT_FUN_SOFTMAX);
//	nn->getLayer(nn->getNumLayers()-1)->setActivationFunction(NNL_ACT_FUN_NONE);

}


NNJsonParser::~NNJsonParser() {
	delete hidden_layers_size;
	hidden_layers_size = 0;
}

