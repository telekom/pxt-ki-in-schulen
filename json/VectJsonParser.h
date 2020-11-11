/*
 * VectJsonParser.h
 *
 *  Created on: 29.02.2020
 *      Author: A307131
 */

#ifndef VECTJSONPARSER_H_
#define VECTJSONPARSER_H_

#include "JsonParserIF.h"

class Vect;

class VectJsonParser: public JsonParserIF {

private:
	Vect *vect;

public:
	VectJsonParser();
	void element(const char* value);
    void* getResult();
	~VectJsonParser();

};

#endif /* VECTJSONPARSER_H_ */
