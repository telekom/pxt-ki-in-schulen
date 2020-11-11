#include "../platform/Utils.h"


void logLn() {
	log("\r\n");
}

void logLn(const char *msg) {
	log(msg);
	logLn();
}

void logLnInt(int i) {
	logInt(i);
	logLn();
}
void logLnFloat(float f) {
	logFloat(f);
	logLn();
}

void logNamedInt(const char * name, int i) {
	log(name);
	log(": ");
	logInt(i);
	logLn();
}

void logNamedFloat(const char * name, float f) {
	log(name);
	log(": ");
	logFloat(f);
	logLn();
}
