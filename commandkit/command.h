/*
This file is licensed under the MIT-License
Copyright (c) 2015 Marius Messerschmidt
For more details view file 'LICENSE'
*/

#ifndef _JETSPACE_COMMANDKIT
#define _JETSPACE_COMMANDKIT

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef bool (*JetSpaceCMDArgCallback) (int argc, char **argv, int id, void *data);

struct _CMDArg
{
  char *arg;                  // Command line Option  --help
  char sh;                    // Short option         -h
  int id;                     // ID passed to Callback
  char *disc;                 // Descripton for --help
  void *data;                  // data POINTER passed to callback
  JetSpaceCMDArgCallback cb;  // Callback
};

typedef struct _CMDArg JetSpaceCMDArg;

extern void jetspace_add_cmd_line_argument(char sh, char *arg, int id, char *disc, JetSpaceCMDArgCallback cb, void *data);
bool jetspace_parse_cmd_line(int argc, char **argv);
void jetspace_cmd_line_print_help(void);
void jetspace_cmd_line_print_version(void);
void jetspace_cmd_line_init(char *name, char *version);

void jetspace_cmd_line_free(void);

#endif
