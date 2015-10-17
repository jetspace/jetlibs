%module logkit
%{
#include "log.h"
%}
short jet_log_debug(char *);
short jet_log_note(char *);
short jet_log_message(char *);
short jet_log_warning(char *);
short jet_log_error(char *);
short jet_log_critical(char *);
short jet_log_failure(char *);
%include "log.h"
