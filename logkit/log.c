/*
This file is licensed under the MIT-License
Copyright (c) 2015 Marius Messerschmidt
For more details view file 'LICENSE'
*/

#include "log.h"

 int JETSPACE_LOGLEVEL = JETSPACE_LOG_LEVEL_MESSAGE;
 int JETSPACE_ERROR_LEVEL = JETSPACE_LOG_LEVEL_NA;
 FILE *JETSPACE_OLD_STDERR;

char *JETSPACE_LOGKIT_APP;

char *logkit_prefix(void)
{
  char *ret = malloc(50);

  time_t t = time(NULL);
  struct tm *timedata = localtime(&t);

  strftime(ret, 50, "[%c] - ", timedata);
  return ret;

}


#ifndef _LOGKIT_DISABLE_GLIB_SUPPORT
void logkit_glib_loghandler(const char *domain, GLogLevelFlags log_level, const char *msg, gpointer data)
{
  char *m = g_strdup(msg);

  switch(log_level)
  {
    case G_LOG_LEVEL_DEBUG:
      jetspace_debug(m);
      break;

    case G_LOG_LEVEL_INFO:
      jetspace_note(m);
      break;

    case G_LOG_LEVEL_MESSAGE:
      jetspace_message(m);
      break;

    case G_LOG_LEVEL_WARNING:
      jetspace_warning(m);
      break;

    case G_LOG_LEVEL_CRITICAL:
      jetspace_critical(m);
      break;

    case G_LOG_LEVEL_ERROR:
      jetspace_error(m);
      break;

    case G_LOG_FLAG_FATAL:
      jetspace_failure(m);
      break;

    default:
      jetspace_failure(m);
      break;
  }
  g_free(m);
}
#endif

short jetspace_log(short type, char *format, ...)
{

  if(type < JETSPACE_LOGLEVEL)
    return type;

  char err[MAX_LOG_LEN];
  va_list p;
  va_start(p, format);
  vsnprintf(err, MAX_LOG_LEN, format, p);
  va_end(p);

  char *prefix = logkit_prefix();

  switch(type)
  {
    //DEBUG
    case JETSPACE_LOG_LEVEL_DEBUG:
      fprintf(stderr, "%s[D] : %s\n",prefix, err);
    break;

    //NOTE
    case JETSPACE_LOG_LEVEL_NOTE:
      fprintf(stderr, "%s[N] : %s\n",prefix, err);
    break;

    //MESSAGE
    case JETSPACE_LOG_LEVEL_MESSAGE:
      fprintf(stderr, "%s[M] : %s\n",prefix, err);
    break;

    //WARNING
    case JETSPACE_LOG_LEVEL_WARNING:
      fprintf(stderr, "%s[W] : %s\n",prefix, err);
    break;

    //ERROR
    case JETSPACE_LOG_LEVEL_ERROR:
      fprintf(stderr, "%s[!] : %s\n",prefix, err);
    break;

    //CRITICAL
    case JETSPACE_LOG_LEVEL_CRITICAL:
      fprintf(stderr, "%s[*!]: %s\n",prefix, err);
    break;

    //FAILURE
    case JETSPACE_LOG_LEVEL_FAILURE:
      fprintf(stderr, "%s[!!]: %s\n",prefix, err);
    break;

    //FALLBACK
    default:
      fprintf(stderr, "%sINVALID LOGLEVEL! SOME INFOS: %s\n",prefix, err);
    break;

  }
  free(prefix);

  if(type >= JETSPACE_ERROR_LEVEL)
  {
    jetspace_logkit_debug_promt();
  }

  return type;

}


#ifndef _LOGKIT_DISABLE_GLIB_SUPPORT
void jetspace_logkit_enable_glib_handler(void)
{
  g_log_set_default_handler(logkit_glib_loghandler, NULL);
  g_log_set_handler("Gtk", G_LOG_LEVEL_MASK | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION, logkit_glib_loghandler, NULL);
  g_log_set_handler(NULL, G_LOG_LEVEL_MASK | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION, logkit_glib_loghandler, NULL);
  g_log_set_handler("GLib", G_LOG_LEVEL_MASK | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION, logkit_glib_loghandler, NULL);
}
#endif

void jetspace_set_log_level_from_environment(void)
{
  char *p = getenv("LOGLEVEL");
  if(p == NULL)
    return;
  else
    JETSPACE_LOGLEVEL = atoi(p);
  return;
}

void jetspace_logkit_backtrace(void)
{
  void *buffer[MAXBACKTRACE];
  char **funcs;
  int count = 0;

  count = backtrace(buffer, MAXBACKTRACE);
  funcs = backtrace_symbols(buffer, count);

  fprintf(stderr, "JetSpace Logkit - Backtrace of %d addresses:\n", count);
  for(int x = 0; x < count; x++)
  {
    fprintf(stderr, " :: [%03d] %s\n", count -x ,funcs[x]);
  }
  fprintf(stderr, "End of Backtrace\n");


}

void jetspace_logkit_debug_promt(void)
{
  printf("Application reached critical error!");
  int c = 0;
  char cmd[200];
  while(c != 'E' && c != 'C')
  {
    printf("\n[E]xit - [B]acktrace - [O]pen in GDB - [C]ontinue: ");
    c = toupper(getchar());
    switch(c)
    {
        case 'E':
          exit(-1);
        break;

        case 'B':
          jetspace_logkit_backtrace();
        break;

        case 'O':
          snprintf(cmd, 200, "gdb -p %d", getpid());
          system(cmd);
        break;
    }
  }
}

void jetspace_logkit_init(int argc, char **argv)
{
  if(argc < 1)
  {
    jetspace_error("Could not init JetspaceLogkit: invalid arguments");
    return;
  }
  for(int x = 0; x < argc; x++)
  {
    if(strcmp(argv[x], "--jetspace-debug-level") == 0 && argc > x)
    {
      JETSPACE_ERROR_LEVEL = atoi(argv[x+1]);
    }
    if(strcmp(argv[x], "--jetspace-log-to-file") == 0 && argc > x)
    {
        FILE* temp = fopen(argv[x+1], "w+");
        if(temp == NULL)
        {
            jetspace_error("COULD NOT OPEN LOG FILE, DEFAULTING TO STDERR");
            continue;
        }
        JETSPACE_OLD_STDERR = stderr;
        stderr = temp;
    }
    if(strcmp(argv[x], "--jetspace-logkit-version") == 0)
    {
      printf("JetSpace Logkit version %s\n", LOGKIT_VERSION);
      printf("Compiled on %s at %s\n", __DATE__, __TIME__);
      exit(0);
    }
  }

  JETSPACE_LOGKIT_APP = argv[0]; // Pointer to application name
}
