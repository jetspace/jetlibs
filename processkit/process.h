/*
This file is licensed under the MIT-License
Copyright (c) 2015 Marius Messerschmidt
For more details view file 'LICENSE'
*/
#ifndef _JETSPACE_PROCESSKIT
#define _JETSPACE_PROCESSKIT
#include <pwd.h>

typedef struct _jetspace_process
{ // For details see proc(5)
  int pid;
  char *name;
  char state;
  int priority;
  int uid;
  struct passwd *user;
}JetSpaceProcess;

extern int *jetspace_get_pids(int *size);
extern JetSpaceProcess *jetspace_get_process(int pid);




#endif
