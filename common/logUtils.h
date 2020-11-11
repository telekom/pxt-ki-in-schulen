#ifndef LOGUTILS_H
#define LOGUTILS_H

#include <stdint.h>
#include <stddef.h>

void logLn();
void logLn(const char *msg);
void logLnInt(int i);
void logLnFloat(float f);

void logNamedInt(const char * name, int i);
void logNamedFloat(const char * name, float f);


#endif // LOGUTILS_H
