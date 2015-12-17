/*
This file is licensed under the MIT-License
Copyright (c) 2015 Marius Messerschmidt
For more details view file 'LICENSE'
*/

#include "log.h"

 int JET_LOGLEVEL = JET_LOG_LEVEL_MESSAGE;


char *logkit_prefix(void)
{
  char *ret = malloc(50);

  time_t t = time(NULL);
  struct tm *timedata = localtime(&t);

  strftime(ret, 50, "[%c] - ", timedata);
  return ret;

}


#ifdef _LOGKIT_ENABLE_GLIB_SUPPORT
void logkit_glib_loghandler(const char *domain, GLogLevelFlags log_level, const char *msg, gpointer data)
{
  char *m = g_strdup(msg);

  switch(log_level)
  {
    case G_LOG_LEVEL_DEBUG:
      jet_log_debug(m);
      break;

    case G_LOG_LEVEL_INFO:
      jet_log_note(m);
      break;

    case G_LOG_LEVEL_MESSAGE:
      jet_log_message(m);
      break;

    case G_LOG_LEVEL_WARNING:
      jet_log_warning(m);
      break;

    case G_LOG_LEVEL_CRITICAL:
      jet_log_critical(m);
      break;

    case G_LOG_LEVEL_ERROR:
      jet_log_error(m);
      break;

    case G_LOG_FLAG_FATAL:
      jet_log_failure(m);
      break;

    default:
      jet_log_failure(m);
      break;
  }
  g_free(m);
}
#endif

short jet_log(short type, char *err)
{

  if(type < JET_LOGLEVEL)
    return type;


  char *prefix = logkit_prefix();

  switch(type)
  {
    //DEBUG
    case JET_LOG_LEVEL_DEBUG:
      fprintf(stderr, "%s[D] : %s\n",prefix, err);
    break;

    //NOTE
    case JET_LOG_LEVEL_NOTE:
      fprintf(stderr, "%s[N] : %s\n",prefix, err);
    break;

    //MESSAGE
    case JET_LOG_LEVEL_MESSAGE:
      fprintf(stderr, "%s[M] : %s\n",prefix, err);
    break;

    //WARNING
    case JET_LOG_LEVEL_WARNING:
      fprintf(stderr, "%s[W] : %s\n",prefix, err);
    break;

    //ERROR
    case JET_LOG_LEVEL_ERROR:
      fprintf(stderr, "%s[!] : %s\n",prefix, err);
    break;

    //CRITICAL
    case JET_LOG_LEVEL_CRITICAL:
      fprintf(stderr, "%s[*!]: %s\n",prefix, err);
    break;

    //FAILURE
    case JET_LOG_LEVEL_FAILURE:
      fprintf(stderr, "%s[!!]: %s\n",prefix, err);
    break;

    //FALLBACK
    default:
      fprintf(stderr, "%sINVALID LOGLEVEL! SOME INFOS: %s\n",prefix, err);
    break;




  }
  free(prefix);
  return type;

}


#ifdef _LOGKIT_ENABLE_GLIB_SUPPORT
void jetspace_logkit_enable_glib_handler(void)
{
  g_log_set_default_handler(logkit_glib_loghandler, NULL);
  g_log_set_handler("Gtk", G_LOG_LEVEL_MASK | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION, logkit_glib_loghandler, NULL);
  g_log_set_handler(NULL, G_LOG_LEVEL_MASK | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION, logkit_glib_loghandler, NULL);
  g_log_set_handler("GLib", G_LOG_LEVEL_MASK | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION, logkit_glib_loghandler, NULL);
}
#endif

void jet_log_set_log_level_from_enviroment(void)
{
  char *p = getenv("LOGLEVEL");
  if(p == NULL)
    return;
  else
    JET_LOGLEVEL = atoi(p);
  return;
}
