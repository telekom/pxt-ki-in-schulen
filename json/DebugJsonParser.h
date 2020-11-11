/*
 * DebugJsonParser.h
 *
 *  Created on: 29.02.2020
 *      Author: A307131
 */

#ifndef DEBUGJSONPARSER_H_
#define DEBUGJSONPARSER_H_

#include "JsonParserIF.h"

class DebugJsonParser: public JsonParserIF {
public:
	DebugJsonParser();

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

	~DebugJsonParser();
};

#endif /* DEBUGJSONPARSER_H_ */
