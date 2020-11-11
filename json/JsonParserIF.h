/*
 * JsonParserIF.h
 *
 *  Created on: 29.02.2020
 *      Author: A307131
 */

#ifndef JSONPARSERIF_H_
#define JSONPARSERIF_H_

class JsonParserIF {

public:
	virtual void init(){};

	virtual void beginObject(const char* name){};  					// "obj_name: {"  -> beginObject("obj_name")
	virtual void endObject(){};                    					// "}" -> endObject();
	virtual void beginList(const char* name){};                    	// "[" -> beginList()
	virtual void endList(){};                      					// "]" -> endList()
	virtual void attribute(const char* name, const char* value){};	// "'attr_name': 'attr_value', -> attribute("attr_name", "attr_value")
	virtual void element(const char* value){};						// "'value'," -> element(value)
    virtual void unexpected(int char_pos){};						// "???" -> unexpected(char_pos);

	virtual void exit(){};

    virtual void* getResult() = 0;

    virtual ~JsonParserIF(){};

};

#endif /* JSONPARSERIF_H_ */
