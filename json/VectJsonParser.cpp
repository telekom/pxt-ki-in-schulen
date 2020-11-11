/*
 * VectJsonParser.cpp
 *
 *  Created on: 29.02.2020
 *      Author: A307131
 */

#include "VectJsonParser.h"
#include "../platform/Utils.h"

#include "../neuralnets/Vect.h"

VectJsonParser::VectJsonParser() {
	this->vect = new Vect(0);
}

void VectJsonParser::element(const char* value) {
	if (vect != 0) {
		float f = char2float(value);
		vect->insert(f);
	}
}

void* VectJsonParser::getResult() {
	Vect *result = vect;
	vect = 0;
	return result;
}
VectJsonParser::~VectJsonParser() {
	if (vect != 0) {
		delete vect;
	}
	vect = 0;
}

