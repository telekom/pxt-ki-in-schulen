#include <stdio.h>
#include<string.h>

#include "Token.h"
#include "../platform/Utils.h"


Token::Token(TokenType type, const char *value, int valueLen) {
	this->type = type;
	this->next = 0;
	if (valueLen == 0) {
		this->value = 0;
	}
	else {
		this->value = new char[valueLen+1];
		strncpy(this->value, value, valueLen);
		this->value[valueLen] = '\0';
	}
}


size_t Token::toString(char *buf, size_t maxlen) {
	switch (type) {
	case TOK_COLON:
		return snprintf(buf, maxlen, ":");
	case TOK_COMMA:
		return snprintf(buf, maxlen, ",");
	case TOK_LEFT_CURL_BR:
		return snprintf(buf, maxlen, "{");
	case TOK_RIGHT_CURL_BR:
		return snprintf(buf, maxlen, "}");
	case TOK_LEFT_SQR_BR:
		return snprintf(buf, maxlen, "[");
	case TOK_RIGHT_SQR_BR:
		return snprintf(buf, maxlen, "]");
	case TOK_NONE:
		buf[0] = '\0';
		return 0;
	case TOK_NUMBER: {
		char numbuf[20];
		float f = char2float(this->value);
		float2char(numbuf, f, 4);
		return snprintf(buf, maxlen, "%s", numbuf);
	}
	case TOK_TEXT:
		return snprintf(buf, maxlen, "%s", this->value);
	case TOK_STRING:
		return snprintf(buf, maxlen, "'%s'", this->value);
	default:
		return snprintf(buf, maxlen, "???");
	}
}

Token *Token::nextToken() {
	return this->next;

};

void Token::setValue(const char *newValue, int newValueLen) {
	if (value != 0) {
		delete value;
		value = 0;
	}
	if (newValue == 0) {
		return;
	}
	if (newValueLen == 0) {
		newValueLen = strlen(newValue);
	}
	this->value = new char[newValueLen+1];
	strncpy(this->value, newValue, newValueLen);
	this->value[newValueLen] = '\0';
}


Token::~Token() {
	if (value != 0) {
		delete value;
		value = 0;
	}
}

