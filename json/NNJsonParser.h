/*
 * NNJsonParser.h
 *
 *  Created on: 29.02.2020
 *      Author: A307131
 */

#ifndef NNJSONPARSER_H_
#define NNJSONPARSER_H_

#include "JsonParserIF.h"

class NN;
class Vect;

class NNJsonParser: public JsonParserIF {

private:

	enum ListTypes {
		NONE,
		ELEM_HIDDEN_LAYERS_SIZE,
		ELEM_COEFS,
		ELEM_INTERCEPTS
	};
	ListTypes current_list;
	int element_level;
	int element_pos[3];

	NN *nn;
	int input_size;
	Vect *hidden_layers_size;
	int output_size;
	int activation_function;


public:
	NNJsonParser();

	void init();

	void beginObject(const char* name);
	void endObject();
	void beginList(const char* name);
	void endList();
	void attribute(const char* name, const char* value);
	void element(const char* value);
    void unexpected(int char_pos);

	void exit();

    void* getResult();

private:
	void initNN();

public:
	~NNJsonParser();

};

#endif /* NNJSONPARSER_H_ */
