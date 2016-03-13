/*
This file is licensed under the MIT-License
Copyright (c) 2015 Marius Messerschmidt
For more details view file 'LICENSE'
*/
#include "process.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/resource.h>

int *jetspace_get_pids(int *size)
{
  DIR *dir = opendir("/proc/");
  if(dir == NULL)
    return NULL;

  struct dirent *ent;

  int n = 0;
  int *tgt = malloc(sizeof(int));
  while((ent = readdir(dir)) != NULL)
  {
    bool valid = true;

    for(int x = 0; x < strlen(ent->d_name); x++)
      if(!isdigit(ent->d_name[x]))
        valid = false;

    if(!valid)
      continue;

    n++;
    tgt = realloc(tgt, sizeof(*tgt)*n);
    tgt[n-1] = atoi(ent->d_name);
  }

  closedir(dir);
  *size = n;
  return tgt;
}


JetSpaceProcess *jetspace_get_process(int pid)
{
  char *path = malloc(strlen("/proc//status") + 10);
  snprintf(path, strlen("/proc//stat") + 10, "/proc/%d/stat", pid);
  FILE *f = fopen(path, "r");
  if(f == NULL)
    return NULL;

  JetSpaceProcess *p = malloc(sizeof(*p));

  fscanf(f, "%d %ms %c", &p->pid, &p->name, &p->state);
  fclose(f);

  p->priority = getpriority(PRIO_PROCESS, p->pid);

  return p;
}
