//
// SENAC BCC PI 2 
// Projeto Betelgeuse
//
// logger.h
// wrapper para mensagens. uso:
// - Logger.error("invalid display mode!");
// - Logger.info("hello %s!", name);

#ifndef betelgeuse_engine_logger_h
#define betelgeuse_engine_logger_h

// proto de uma função de log:
typedef void (*logMessage)(const char *format, ...);

typedef struct LogWrapper{
	logMessage info;
	logMessage warning;
	logMessage error;
	logMessage complement;
} LogWrapper;

LogWrapper Logger;
void setupLogger();

#endif