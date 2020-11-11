#include "Parser.h"
#include "Token.h"
#include "../platform/Utils.h"
#include "JsonParserIF.h"

Parser::Parser(JsonParserIF *jsonParser) {
	this->buflen = 0;
	this->parse_state = STATE_INIT;
	this->token = new Token(Token::TOK_NONE);
	this->currentToken = this->token;
	this->jsonParser = jsonParser;
	this->expectCommaToken = false;
	this->chars_parsed = 0;
}

void Parser::parse(const char *text) {
	const char* pc = text;
	jsonParser->init();
	while (*pc) {
		parse(*pc++);
	}
	finalizeCurrentToken(' ');
	jsonParser->exit();
}

void Parser::parse(char c) {
	chars_parsed++;
	Literal lit = getLiteral(c);
	if (continuesCurrentToken(lit)) {
		addToBuf(c);
	}
	else {
		c = finalizeCurrentToken(c);
		if (c == '\0') {
			createNewToken(LIT_WHITESPACE);
		}
		else {
			createNewToken(lit);
			addToBuf(c);
		}
	}
}

void Parser::addToBuf(char c) {
	if (buflen >= PARSER_BUF_MAXLEN) {
		// TODO: throw exception? enlarge buf? ignore?
		// -> ignore
		return;
	}
	buf[buflen++] = c;
}

char Parser::finalizeCurrentToken(char c) {
	switch (currentToken->type) {
	case Token::TOK_TEXT:
		currentToken->setValue(buf, buflen);
		break;
	case Token::TOK_STRING:
		currentToken->setValue(buf+1, buflen-1);
		c = '\0';
		break;
	case Token::TOK_NUMBER:
		currentToken->setValue(buf, buflen);
		break;
	default:
		break;
	}
	buflen = 0;
	processTokens();
	return c;

}

void Parser::createNewToken(Literal lit) {
	Token::TokenType type = Token::TOK_NONE;
	switch (lit) {
	case LIT_COLON:
		type = Token::TOK_COLON;
		break;
	case LIT_COMMA:
		type = Token::TOK_COMMA;
		break;
	case LIT_DASH:
		type = Token::TOK_NUMBER;
		break;
	case LIT_DOT:
		type = Token::TOK_NUMBER;
		break;
	case LIT_LEFT_CURLY_BRACKET:
		type = Token::TOK_LEFT_CURL_BR;
		break;
	case LIT_LEFT_SQUARE_BRACKET:
		type = Token::TOK_LEFT_SQR_BR;
		break;
	case LIT_LETTER:
		type = Token::TOK_TEXT;
		break;
	case LIT_NUM:
		type = Token::TOK_NUMBER;
		break;
	case LIT_QUOTE:
		type = Token::TOK_STRING;
		break;
	case LIT_RIGHT_CURLY_BRACKET:
		type = Token::TOK_RIGHT_CURL_BR;
		break;
	case LIT_RIGHT_SQUARE_BRACKET:
		type = Token::TOK_RIGHT_SQR_BR;
		break;
	case LIT_WHITESPACE:
		type = Token::TOK_NONE;
		break;
	default:
		type = Token::TOK_ERROR;
	}
	currentToken->next = new Token(type);
	currentToken = currentToken->next;
}


bool Parser::continuesCurrentToken(Literal lit) {
	switch (currentToken->type) {
	case Token::TOK_TEXT:
		return (lit == LIT_LETTER) || (lit == LIT_NUM) || (lit == LIT_UNDERSCORE);
	case Token::TOK_STRING:
		return (lit != LIT_QUOTE);
	case Token::TOK_NUMBER:
		return (lit == LIT_NUM) || (lit == LIT_DOT) || (lit == LIT_DASH) || (lit == LIT_PLUS) || (lit == LIT_LETTER);
	case Token::TOK_NONE:
		return (lit == LIT_WHITESPACE);
	default:
		return false;
	}
}


Parser::Literal Parser::getLiteral(char c) {
	if ((c >= '0') && (c <= '9')) {
		return LIT_NUM;
	}
	if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))) {
		return LIT_LETTER;
	}
	switch (c)
	{
	case '{':
		return LIT_LEFT_CURLY_BRACKET;
	case '}':
		return LIT_RIGHT_CURLY_BRACKET;
	case '(':
		return LIT_LEFT_ROUND_BRACKET;
	case ')':
		return LIT_RIGHT_ROUND_BRACKET;
	case '[':
		return LIT_LEFT_SQUARE_BRACKET;
	case ']':
		return LIT_RIGHT_SQUARE_BRACKET;
	case ',':
		return LIT_COMMA;
	case '.':
		return LIT_DOT;
	case '-':
		return LIT_DASH;
	case '_':
		return LIT_UNDERSCORE;
	case '+':
		return LIT_PLUS;
	case ':':
		return LIT_COLON;
	case '\'':
	case '"':
		return LIT_QUOTE;
	case ' ':
	case '\t':
	case '\r':
	case '\n':
		return LIT_WHITESPACE;
	default:
		return LIT_UNKNOWN;
	}
}


Token *Parser::getToken() {
	return this->token;
}


Token *Parser::nextNonEmptyToken(Token *tok) {
	while ((tok != 0) && (tok->type == Token::TOK_NONE)) {
		tok = tok->nextToken();
	}
	return tok;
}

bool Parser::processTokens() {
	Token *tok = nextNonEmptyToken(getToken());
	if (tok == 0) {
		return false;
	}
	switch (tok->type) {
	case Token::TOK_LEFT_CURL_BR:
		if (expectCommaToken) {
			jsonParser->unexpected(chars_parsed);
			break;
		}
		jsonParser->beginObject(NULL);
		break;
	case Token::TOK_RIGHT_CURL_BR:
		jsonParser->endObject();
		expectCommaToken = true;
		break;
	case Token::TOK_LEFT_SQR_BR:
		if (expectCommaToken) {
			jsonParser->unexpected(chars_parsed);
			break;
		}
		jsonParser->beginList(NULL);
		break;
	case Token::TOK_RIGHT_SQR_BR:
		jsonParser->endList();
		expectCommaToken = true;
		break;
	case Token::TOK_TEXT:
	case Token::TOK_STRING:
	case Token::TOK_NUMBER: {
		if (expectCommaToken) {
			jsonParser->unexpected(chars_parsed);
			break;
		}
		Token *tok2 = nextNonEmptyToken(tok->nextToken());
		if (tok2 == 0) {
			return false;
		}
		if (tok2->type != Token::TOK_COLON) {
			const char *value = tok->value;
			switch (tok2->type) {
			case Token::TOK_COMMA:
				jsonParser->element(value);
				tok = tok2;   // eat the comma
				break;
			case Token::TOK_RIGHT_CURL_BR:
			case Token::TOK_RIGHT_SQR_BR:
				jsonParser->element(value);
				break;
			default:
				jsonParser->unexpected(chars_parsed);
				tok = tok2;
				break;
			}
			break;
		}
		tok2 = nextNonEmptyToken(tok2->nextToken());
		if (tok2 == 0) {
			return false;
		}
		const char *name = tok->value;
		switch (tok2->type) {
		case Token::TOK_LEFT_CURL_BR:
			jsonParser->beginObject(name);
			break;
		case Token::TOK_LEFT_SQR_BR:
			jsonParser->beginList(name);
			break;
		case Token::TOK_TEXT:
		case Token::TOK_STRING:
		case Token::TOK_NUMBER: {
				Token *tok3 = nextNonEmptyToken(tok2->nextToken());
				if (tok3 == 0) {
					return false;
				}
				const char *value = tok2->value;
				switch (tok3->type) {
				case Token::TOK_COMMA:
					jsonParser->attribute(name, value);
					tok2 = tok3; // eat the comma
					break;
				case Token::TOK_RIGHT_CURL_BR:
				case Token::TOK_RIGHT_SQR_BR:
					jsonParser->attribute(name, value);
					break;
				default:
					jsonParser->unexpected(chars_parsed);
					tok2 = tok3;
					break;
				}
			}
			break;
		default:
			jsonParser->unexpected(chars_parsed);
			break;
		}
		tok = tok2;
		break;
	}
	case Token::TOK_COMMA:
		if (!expectCommaToken) {
			jsonParser->unexpected(chars_parsed);
		}
		expectCommaToken = false;
		break;
	default:
		jsonParser->unexpected(chars_parsed);
		break;
	}
	Token *t = getToken();
	while ((t != 0 ) && (t != tok)) {
		Token *t2 = t;
		t = t->nextToken();
		delete t2;
	}
	if (t == tok) {
		t = tok->nextToken();
		delete tok;
	}
	if (t != 0) {
		token = t;
	}
	else {
		token = new Token(Token::TOK_NONE);
		this->currentToken = this->token;
	}
	return true;
}


Parser::~Parser() {
	while (token != 0) {
		Token *t = token;
		token = t->nextToken();
		delete t;
	}
}

