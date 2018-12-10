//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include <stdio.h>
#include <stdarg.h>
#include "logger.h"

#define LOGGING 0

static void logInfo(const char *format, ...) {
	if (LOGGING) {
		fprintf(stdout, "\033[32m[info]\033[0m ");
		va_list arg;
		va_start (arg, format);
   		vfprintf (stdout, format, arg);
   		va_end (arg);
   		fprintf(stdout, "\n");
   	}
}

static void logWarning(const char *format, ...) {
	if (LOGGING) {
		fprintf(stdout, "\033[33m[warning]\033[0m ");
		va_list arg;
		va_start (arg, format);
   		vfprintf (stdout, format, arg);
   		va_end (arg);
   		fprintf(stdout, "\n");
   	}
}

static void logError(const char *format, ...) {
	if (LOGGING) {
		fprintf(stdout, "\033[31m[error]\033[0m ");
		va_list arg;
		va_start (arg, format);
   		vfprintf (stdout, format, arg);
   		va_end (arg);
   		fprintf(stdout, "\n");
   	}
}

static void logComplement(const char *format, ...) {
	if (LOGGING) {
		fprintf(stdout, "\t⮑  ");
		va_list arg;
		va_start (arg, format);
   		vfprintf (stdout, format, arg);
   		va_end (arg);
   		fprintf(stdout, "\n");
   	}
}

void setupLogger(){
	Logger.info 		= logInfo;
	Logger.warning 		= logWarning;
	Logger.error 		= logError;
	Logger.complement   = logComplement; 
}

