#ifndef PARSER_H
#define PARSER_H

#define PARSER_BUF_MAXLEN 32

class Token;
class JsonParserIF;

class Parser
{
public:
	enum ParserState {
		STATE_INIT,
		STATE_NUMBER,
		STATE_TEXT,
		STATE_CHAR
	};

	enum Literal {
		LIT_UNKNOWN,
		LIT_WHITESPACE,
		LIT_NUM,
		LIT_LETTER,
		LIT_LEFT_ROUND_BRACKET,
		LIT_RIGHT_ROUND_BRACKET,
		LIT_LEFT_SQUARE_BRACKET,
		LIT_RIGHT_SQUARE_BRACKET,
		LIT_LEFT_CURLY_BRACKET,
		LIT_RIGHT_CURLY_BRACKET,
		LIT_COMMA,
		LIT_DOT,
		LIT_DASH,
		LIT_UNDERSCORE,
		LIT_PLUS,
		LIT_COLON,
		LIT_QUOTE

	};

private:
	char buf[PARSER_BUF_MAXLEN];
	int  buflen;
	ParserState parse_state;
	Token *token;
	Token *currentToken;
	bool expectCommaToken;
	int chars_parsed;
	JsonParserIF *jsonParser;

public:
	Parser(JsonParserIF *jsonParser);

	void parse(const char *text);
	void parse(char c);
	Literal getLiteral(char c);
	bool continuesCurrentToken(Literal lit);
	Token *getToken();
	void addToBuf(char c);
	void createNewToken(Literal lit);
	char finalizeCurrentToken(char c);

private:
	bool processTokens();
	Token *nextNonEmptyToken(Token *tok);

public:
	~Parser();

};


#endif  // PARSER_H
