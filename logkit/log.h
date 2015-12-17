/*
This file is licensed under the MIT-License
Copyright (c) 2015 Marius Messerschmidt
For more details view file 'LICENSE'
*/

#ifndef _JETSPACE_LOGKIT
#define _JETSPACE_LOGKIT

#include <stdio.h>  //printing
#include <stdlib.h> //memory
#include <string.h> //creating output
#include <time.h>   //time code

// DISABLE IF YOU DO NOT WANT TO USE GLIB LOG HANDLERS
#define _LOGKIT_ENABLE_GLIB_SUPPORT

#ifdef _LOGKIT_ENABLE_GLIB_SUPPORT
#include <glib.h>
#endif

enum
{//print all with log level >= log_level
  JET_LOG_LEVEL_DEBUG   = 0,
  JET_LOG_LEVEL_NOTE,
  JET_LOG_LEVEL_MESSAGE,
  JET_LOG_LEVEL_WARNING,
  JET_LOG_LEVEL_ERROR,
  JET_LOG_LEVEL_CRITICAL,
  JET_LOG_LEVEL_FAILURE
};

//set to a default, usefull level
extern int JET_LOGLEVEL;

//Get current Log Level
#define jet_log_get_log_level() JET_LOGLEVEL

//Set Log Level
#define jet_log_set_log_level(x) JET_LOGLEVEL = x

//log macros
#define jet_log_debug(x) jet_log(JET_LOG_LEVEL_DEBUG, x)
#define jet_log_note(x) jet_log(JET_LOG_LEVEL_NOTE, x)
#define jet_log_message(x) jet_log(JET_LOG_LEVEL_MESSAGE, x)
#define jet_log_warning(x) jet_log(JET_LOG_LEVEL_WARNING, x)
#define jet_log_error(x) jet_log(JET_LOG_LEVEL_ERROR, x)
#define jet_log_critical(x) jet_log(JET_LOG_LEVEL_CRITICAL, x)
#define jet_log_failure(x) jet_log(JET_LOG_LEVEL_FAILURE, x)

//log_function
short jet_log(short type, char *err);

//set log_level from env
void jet_log_set_log_level_from_enviroment(void);

#ifdef _LOGKIT_ENABLE_GLIB_SUPPORT
void jetspace_logkit_enable_glib_handler(void);
#endif


#endif
