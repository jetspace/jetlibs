/*
This file is licensed under the MIT-License
Copyright (c) 2015 Marius Messerschmidt
For more details view file 'LICENSE'
*/

#include "log.h"

 int JET_LOGLEVEL = JET_LOG_LEVEL_MESSAGE;

short jet_log(short type, char *err)
{

  if(type < JET_LOGLEVEL)
    return type;


  switch(type)
  {
    //DEBUG
    case JET_LOG_LEVEL_DEBUG:
      fprintf(stderr, "[Debug] : %s\n", err);
    break;

    //NOTE
    case JET_LOG_LEVEL_NOTE:
      fprintf(stderr, "[NOTE]  : %s\n", err);
    break;

    //MESSAGE
    case JET_LOG_LEVEL_MESSAGE:
      fprintf(stderr, ">>  %s\n", err);
    break;

    //WARNING
    case JET_LOG_LEVEL_WARNING:
      fprintf(stderr, "  [WARNING] : %s\n", err);
    break;

    //ERROR
    case JET_LOG_LEVEL_ERROR:
      fprintf(stderr, ">>  [ERROR] : %s\n", err);
    break;

    //CRITICAL
    case JET_LOG_LEVEL_CRITICAL:
      fprintf(stderr, "Critical Error:\n");
      fprintf(stderr, ">>  [CRITICAL]  : %s\n", err);
    break;

    //FAILURE
    case JET_LOG_LEVEL_FAILURE:
      fprintf(stderr, "SYSTEM FAILURE:\n");
      fprintf(stderr, ">>>>  [FAILURE] : %s\n", err);
    break;

    //FALLBACK
    default:
      fprintf(stderr, "SIDE LOG FAILURE! SOME INFOS: %s\n", err);
    break;




  }

  return type;

}


void jet_log_set_log_level_from_enviroment(void)
{
  char *p = getenv("LOGLEVEL");
  if(p == NULL)
    return;
  else
    JET_LOGLEVEL = atoi(p);

  return;
}
