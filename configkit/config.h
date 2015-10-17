/*
This file is licensed under the MIT-License
Copyright (c) 2015 Marius Messerschmidt
For more details view file 'LICENSE'
*/
#ifndef _JETSPACE_CONFIGKIT
#define _JETSPACE_CONFIGKIT

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//check if string is ignored for config parsing
bool is_ignored(char *entry);
//dump config file to screen
void jet_dump_config_file(char *file);

//get value asigned to entry in file
char *jet_lookup_value(char *file,char *entry);

//Add a new entry to file with value (you should normaly not use this)
void jet_add_new_value(char *file,  char *entry, char *value);
//set value to entry in file. If add is true, a new one will be created if value entry is not found
void jet_set_value(char *file, char *entry, char *value, bool add);

FILE *jet_config_file;

void jet_init_config_read(char *file);
char *jet_get_next_entry(void);
void jet_close_config_read(void);


#endif
