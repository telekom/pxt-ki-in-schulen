#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>

class Token
{
public:
	enum TokenType {
		TOK_NONE,
		TOK_ERROR,
		TOK_NUMBER,
		TOK_TEXT,
		TOK_LEFT_CURL_BR,
		TOK_RIGHT_CURL_BR,
		TOK_LEFT_SQR_BR,
		TOK_RIGHT_SQR_BR,
		TOK_COLON,
		TOK_COMMA,
		TOK_STRING
	};

public:
	TokenType type;
	char *value;
	Token *next;

public:
	Token(TokenType type, const char *value=0, int valueLen=0);

	void setValue(const char *newValue, int newValueLen=0);

	size_t toString(char *buf, size_t maxlen);
	Token *nextToken();

	~Token();
};


#endif // TOKEN_H
