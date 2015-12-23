/*
This file is licensed under the MIT-License
Copyright (c) 2015 Marius Messerschmidt
For more details view file 'LICENSE'
*/

#ifndef _JETSPACE_LOGKIT
#define _JETSPACE_LOGKIT

#define LOGKIT_VERSION "1.0-1"

#include <stdio.h>      //printing
#include <stdlib.h>     //memory
#include <string.h>     //creating output
#include <time.h>       //time code
#include <ctype.h>      //User input (debug promt)
#include <execinfo.h>   // Backtrace
#include <unistd.h>     // PID
#include <stdarg.h>     // printf like logging

// ENABLE IF YOU DO NOT WANT TO USE GLIB LOG HANDLERS
//#define _LOGKIT_DISABLE_GLIB_SUPPORT

#define MAXBACKTRACE 500 // number of maximum Backtrace buffer size
#define MAX_LOG_LEN 2500

#ifndef _LOGKIT_DISABLE_GLIB_SUPPORT
#include <glib.h>
#endif

enum
{//print all with log level >= log_level
  JETSPACE_LOG_LEVEL_DEBUG   = 0,
  JETSPACE_LOG_LEVEL_NOTE,
  JETSPACE_LOG_LEVEL_MESSAGE,
  JETSPACE_LOG_LEVEL_WARNING,
  JETSPACE_LOG_LEVEL_ERROR,
  JETSPACE_LOG_LEVEL_CRITICAL,
  JETSPACE_LOG_LEVEL_FAILURE,
  JETSPACE_LOG_LEVEL_NA
};

//set to a default, usefull level
extern int JETSPACE_LOGLEVEL;
extern int JETSPACE_ERROR_LEVEL;
extern FILE *JETSPACE_OLD_STDERR;

//Get current Log Level
#define jetspace_get_log_level() JETSPACE_LOGLEVEL

//Set Log Level
#define jetspace_set_log_level(x) JETSPACE_LOGLEVEL = x

//log macros
#define jetspace_debug(x, ...) jetspace_log(JETSPACE_LOG_LEVEL_DEBUG, x, ##__VA_ARGS__)
#define jetspace_note(x, ...) jetspace_log(JETSPACE_LOG_LEVEL_NOTE, x, ##__VA_ARGS__)
#define jetspace_message(x, ...) jetspace_log(JETSPACE_LOG_LEVEL_MESSAGE, x, ##__VA_ARGS__)
#define jetspace_warning(x, ...) jetspace_log(JETSPACE_LOG_LEVEL_WARNING, x, ##__VA_ARGS__)
#define jetspace_error(x, ...) jetspace_log(JETSPACE_LOG_LEVEL_ERROR, x, ##__VA_ARGS__)
#define jetspace_critical(x, ...) jetspace_log(JETSPACE_LOG_LEVEL_CRITICAL, x, ##__VA_ARGS__)
#define jetspace_failure(x, ...) jetspace_log(JETSPACE_LOG_LEVEL_FAILURE, x, ##__VA_ARGS__)

//log_function
short jetspace_log(short type, char *format, ...);


//set log_level from env
void jetspace_set_log_level_from_environment(void);

//GLibc
#ifndef _LOGKIT_DISABLE_GLIB_SUPPORT
void jetspace_logkit_enable_glib_handler(void);
#endif

// Backtrace
void jetspace_logkit_backtrace(void);

// Show promt to user to select debuging options
void jetspace_logkit_debug_promt(void);

// init everything
void jetspace_logkit_init(int argc, char **argv);

#endif
