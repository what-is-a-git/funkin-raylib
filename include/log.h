#ifndef LOG_H
#define LOG_H

// taken from other c project

#include <stdio.h>

#define ANSI_ESCAPE_RESET "\033[m"
#define ANSI_ESCAPE(number) "\033[" #number "m"

#define log(message) fprintf(stdout, ANSI_ESCAPE(46) " LOG " ANSI_ESCAPE_RESET " " #message "\n")
#define log_fmt(message, ...) fprintf(stdout, ANSI_ESCAPE(46) " LOG " ANSI_ESCAPE_RESET " " #message "\n", __VA_ARGS__)

#define warn(message) fprintf(stdout, ANSI_ESCAPE(103) " WARNING " ANSI_ESCAPE_RESET " " #message "\n")
#define warn_fmt(message, ...) fprintf(stdout, ANSI_ESCAPE(103) " WARNING " ANSI_ESCAPE_RESET " " #message "\n", __VA_ARGS__)

#define error(message) fprintf(stderr, ANSI_ESCAPE(101) " ERROR " ANSI_ESCAPE_RESET " " #message "\n")
#define error_fmt(message, ...) fprintf(stderr, ANSI_ESCAPE(101) " ERROR " ANSI_ESCAPE_RESET " " #message "\n", __VA_ARGS__)

#endif // !LOG_H