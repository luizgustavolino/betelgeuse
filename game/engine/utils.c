//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include <stdlib.h>
#include <string.h>

// Code by David Heffernan
// from: https://bit.ly/2zVGJZS (oct 6, 2018)
char* allocStringJoining(const char *s1, const char *s2){

	// +1 for the null-terminator
    char *result = malloc(strlen(s1) + strlen(s2) + 1); 
    strcpy(result, s1);
    strcat(result, s2);
    
    return result;
}