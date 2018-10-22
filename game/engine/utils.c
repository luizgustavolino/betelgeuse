//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include <stdlib.h>
#include <string.h>
#include "utils.h"

// Code by David Heffernan
// from: https://bit.ly/2zVGJZS (oct 6, 2018)
char* allocStringJoining(const char *s1, const char *s2){

	// +1 for the null-terminator
    char *result = malloc(strlen(s1) + strlen(s2) + 1); 
    strcpy(result, s1);
    strcat(result, s2);
    
    return result;
}


// Code by Warren Moore
// from: https://github.com/warrenm/AHEasing (oct 20, 2018)
// -- cubicEaseInOut
// Modeled after the piecewise cubic
// y = (1/2)((2x)^3)       ; [0, 0.5)
// y = (1/2)((2x-2)^3 + 2) ; [0.5, 1]
// -- cubicEaseOut
// Modeled after the cubic y = (x - 1)^3 + 1

float cubicEaseInOut(float p){
	if(p < 0.5){
		return 4.0 * p * p * p;
	} else {
		float f = ((2.0 * p) - 2.0);
		return 0.5 * f * f * f + 1.0;
	}
}

float cubicEaseOut(float p){
	float f = (p - 1);
	return f * f * f + 1;
}

float applyCubicEaseInOut(int fromFrame, int toFrame, int current, float delta){

	if (current >= toFrame) return delta;
	if (current <= fromFrame) return 0.0;

	float percent = ((float) current - (float) fromFrame) / ((float) toFrame - (float)fromFrame);
	float easeTransformed = cubicEaseInOut(percent);
	return delta * easeTransformed;
}

float applyCubicEaseOut(int fromFrame, int toFrame, int current, float delta){

	if (current >= toFrame) return delta;
	if (current <= fromFrame) return 0.0;

	float percent = ((float) current - (float) fromFrame) / ((float) toFrame - (float)fromFrame);
	float easeTransformed = cubicEaseOut(percent);
	return delta * easeTransformed;
}