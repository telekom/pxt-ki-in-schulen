#include "pxt.h"

#include "Utils.h"

//#include<stdio.h>
#include<stdarg.h>
//#include<string.h>
//#include <math.h>
//#include <float.h>
//#include <iostream>


// from: https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/Print.cpp
size_t float2char(char* buf, float number, uint8_t digits) {
  size_t n = 0;

  if (isnan(number)) return sprintf(buf, "nan");
  if (isinf(number)) return sprintf(buf, "inf");
  if(number > 4294967040.0) {
      return sprintf(buf, "ovf");    // constant determined empirically
  }
  if(number < -4294967040.0) {
      return sprintf(buf, "ovf");    // constant determined empirically
}

  // Handle negative numbers
  if (number < 0.0)
  {
     n += sprintf((char*)(buf+n), "-");
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  float rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  n += sprintf((char*)(buf+n), "%lu", int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    n += sprintf((char*)(buf+n), ".");
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    n += sprintf((char*)(buf+n), "%d",toPrint);
    remainder -= toPrint;
  }

  return n;
}

#define SEC_PREFIX 		0
#define SEC_INTPART 	1
#define SEC_FRAGPART 	2
#define SEC_EXPPREFIX 	3
#define SEC_EXP 		4
#define SEC_FINISHED 	99

// after calling atof("4.7452347e-316") the program gets stuck some times later.
// so, use an own char2float() method instead of atof().
//
// Example: -12.34e+03
// Section: 011 22 344
//
float char2float(const char* text) {
	bool neg = false;
	bool negexp = false;
	float result = 0;
	float decpos = 0.1;
	float exp = 0;
	const char* pc = text;
	int section = SEC_PREFIX;
	while ((section != SEC_FINISHED) && (*pc)) {
		char c = *pc++;
		switch (section) {
		case SEC_PREFIX:
			if (c == '-') {
				neg = true;
			}
			else if (c == '+') {
				neg = false;
			}
			else {
				pc--;
			}
			section = SEC_INTPART;
			break;
		case SEC_INTPART:
			if (c == '.') {
				section = SEC_FRAGPART;
			}
			else if ((c == 'e') || (c == 'E')) {
				section = SEC_EXPPREFIX;
			}
			else if ((c >= '0') && (c <= '9')) {
				result = result*10 + (c-'0');
			}
			else {
				section = SEC_FINISHED;
			}
			break;
		case SEC_FRAGPART:
			if ((c == 'e') || (c == 'E')) {
				section = SEC_EXPPREFIX;
			}
			else if ((c >= '0') && (c <= '9')) {
				result = result + (decpos*(c-'0'));
				decpos = decpos / 10;
			}
			else {
				section = SEC_FINISHED;
			}
			break;
		case SEC_EXPPREFIX:
			if (c == '+') {
				negexp = false;
				section = SEC_EXP;
			}
			else if (c == '-') {
				negexp = true;
				section = SEC_EXP;
			}
			else {
				section = SEC_FINISHED;
			}
			break;
		case SEC_EXP:
			if ((c >= '0') && (c <= '9')) {
				exp = exp*10 + (c-'0');
			}
			else {
				section = SEC_FINISHED;
			}
			break;
		default:
			section = SEC_FINISHED;
			break;
		}
	}
	if (negexp) {
		exp = -exp;
	}
	while (exp > 0) {
		result = result*10;
		exp--;
	}
	while (exp < 0) {
		result = result/10;
		exp++;
	}
	if (neg) {
		result = -result;
	}
	return result;
}


void throwError(const char *errMsg) {
	while (true) {
	    uBit.serial.send(errMsg);
		uBit.display.scroll(errMsg);
        uBit.sleep(1000);
        if ( uBit.buttonA.isPressed() == true ) {
        	uBit.sleep(24*60*60*1000);
        }
	}
}

void log(const char *msg) {
//	uBit.display.scroll(msg);
    uBit.serial.send(msg);
}

void logFloat(float f) {
	char buf[100];
	float2char(buf, f, 3);
	log(buf);
}

void logInt(int i) {
	char buf[100];
	sprintf(buf, "%d", i);
	log(buf);
}
