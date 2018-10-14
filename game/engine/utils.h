//
// SENAC BCC PI 2 
// Projeto Betelgeuse
//
// utils.h
// funções de apoio
// 

#ifndef betelgeuse_engine_utils_h
#define betelgeuse_engine_utils_h

 #define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

 #define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

char* allocStringJoining(const char *s1, const char *s2);

#endif
