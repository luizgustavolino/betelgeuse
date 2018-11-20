//
// SENAC BCC PI 2 
// Projeto Betelgeuse
//
// utils.h
// funções de apoio
// 

#ifndef betelgeuse_engine_utils_h
#define betelgeuse_engine_utils_h

#define PI 3.14159265359

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

void swap(int *a, int *b);

int roundFloatToInt(float x);
float deg2rad(float deg);
float rad2deg(float rad);

char* allocStringJoining(const char *s1, const char *s2);
void replaceChar(char *source, char orig, char repl);

// funções de suavização
float cubicEaseInOut(float p);
float applyCubicEaseInOut(int fromFrame, int toFrame, int current, float delta);

float cubicEaseOut(float p);
float applyCubicEaseOut(int fromFrame, int toFrame, int current, float delta);

float bounceEaseOut(float p);
float applyBounceEaseOut(int fromFrame, int toFrame, int current, float delta);

float backEaseOut(float p);
float applyBackEaseOut(int fromFrame, int toFrame, int current, float delta);

// funções de apoio ao gameplay
int travelTime(float lat1, float lon1, float lat2, float lon2);

#endif
