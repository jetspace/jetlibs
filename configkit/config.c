/*
This file is licensed under the MIT-License
Copyright (c) 2015 Marius Messerschmidt
For more details view file 'LICENSE'
*/
#include "config.h"

FILE *jet_config_file;

bool is_ignored(char *entry)
{
  return((entry[0] == '/' && entry[1] == '/') || entry[0] == '\n');
}

void jet_dump_config_file(char *file)
{
  FILE *f = fopen(file, "r");
  if(!f)
    {
      fprintf(stderr, "JetSpaceConfigParser: can't dump file '%s'\n", file);
      return;
    }

  char buffer[2000];
  puts(" ::BEGIN CONFIG DUMP");
  while(fgets(buffer, 2000, f))
  {
    if(is_ignored(buffer))
      continue;
    char *ent, *val;

    ent = strtok(buffer, ":");
    val = strtok(NULL, "\n");

    printf(" :: %s is set to %s\n", ent, val);
  }
  puts(" ::END CONFIG DUMP");
}

char *jet_lookup_value(char *file,char *entry)
{
  FILE *f = fopen(file, "r");
  if(!f)
    {
      fprintf(stderr, "JetSpaceConfigParser: can't open file '%s'\n", file);
      return NULL;
    }
  if(entry == NULL)
  {
    fprintf(stderr, "JetSpaceConfigParser: Entry not submitted\n");
    return NULL;
  }

  char buffer[2000];
  while(fgets(buffer, 2000, f))
  {
    if(is_ignored(buffer) || strncmp(buffer, entry, strlen(entry)) != 0)
      continue;
    char *val;

    if(strcmp(strtok(buffer, ":"), entry) != 0)
      continue;
    val = strtok(NULL, "\n");
    return val;
  }

  return NULL;
}

void jet_add_new_value(char *file,  char *entry, char *value)
{
  FILE *f = fopen(file, "a");
  if(!f)
  {
    fprintf(stderr, "JetSpaceConfigParser: can't open file '%s'\n", file);
    return;
  }
  fprintf(f, "%s:%s\n", entry, value);
  fclose(f);
}

void jet_set_value(char *file, char *entry, char *value, bool add)
{
  FILE *f = fopen(file, "r");
  if(!f)
  {
    fprintf(stderr, "JetSpaceConfigParser: can't open file '%s'\n", file);
    return;
  }
  FILE *temp = tmpfile();
  if(!temp)
  {
    fprintf(stderr, "JetSpaceConfigParser: can't open tempfile\n");
    return;
  }

  char buffer[2000];
  while(fgets(buffer, 2000, f))
  {
    if(is_ignored(buffer))
    {
      fprintf(temp, "%s", buffer);
      continue;
    }

    bool notEqual = false;

    if(strlen(entry) > strlen(buffer))
      notEqual = true;
    else
    {
      int x;
      for(x = 0; x < strlen(entry); x++)
        if(buffer[x] != entry[x])
          notEqual = true;

      if(buffer[strlen(entry)] != ':')
        notEqual = true;
    }

    if(notEqual == true)
    {
      fprintf(temp, "%s", buffer);
    }
    else
    {
      fprintf(temp, "%s:%s\n", entry, value);
      add = false;
    }
  }

  if(add)
    fprintf(temp, "%s:%s\n", entry, value);

  fclose(f);
  f = fopen(file, "w");
  if(!f)
  {
    fprintf(stderr, "JetSpaceConfigParser: can't open file '%s' (LOCK FOR WRITE)\n", file);
    return;
  }
  fseek(temp, 0L, SEEK_SET);

  //update configuration
  while(fgets(buffer, 2000, temp))
    fprintf(f,"%s", buffer);

  fclose(temp);
  fclose(f);
}

void jet_init_config_read(char *file)
{
  jet_config_file = fopen(file, "r");
}

void jet_close_config_read(void)
{
  fclose(jet_config_file);
}

char *jet_get_next_entry(void)
{
  char buffer[2000];

  fgets(buffer, 2000, jet_config_file);

  if(is_ignored(buffer))
    return jet_get_next_entry();

  if(strstr(buffer, ":") == 0)
    return NULL;

  return strtok(buffer, ":");
}
