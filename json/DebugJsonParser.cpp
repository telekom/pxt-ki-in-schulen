/*
 * DebugJsonParser.cpp
 *
 *  Created on: 29.02.2020
 *      Author: A307131
 */

#include "DebugJsonParser.h"
#include "../platform/Utils.h"
#include <stdio.h>



DebugJsonParser::DebugJsonParser() {
}


void DebugJsonParser::init() {
	log("init()\r\n");
}

void DebugJsonParser::beginObject(const char* name) {
	log("beginObject('");
	if (name != 0) {
		log(name);
	}
	log("')\r\n");
}


void DebugJsonParser::endObject() {
	log("endObject()\r\n");
}

void DebugJsonParser::beginList(const char* name) {
	log("beginList('");
	if (name != 0) {
		log(name);
	}
	log("')\r\n");
}

void DebugJsonParser::endList() {
	log("endList()\r\n");
}

void DebugJsonParser::attribute(const char* name, const char* value) {
	log("attribute('");
	if (name != 0) {
		log(name);
	}
	log("', '");
	if (value != 0) {
		log(value);
	}
	log("')\r\n");
}

void DebugJsonParser::element(const char* value) {
	log("element('");
	if (value != 0) {
		log(value);
	}
	log("')\r\n");
}


void DebugJsonParser::unexpected(int char_pos) {
	char buf[100];
	sprintf(buf, "json error before character %d!", char_pos);
	throwError(buf);
}

void DebugJsonParser::exit() {
	log("exit()\r\n");
}

void* DebugJsonParser::getResult() {
	log("getResult()\r\n");
	return 0;
}



DebugJsonParser::~DebugJsonParser() {
}

