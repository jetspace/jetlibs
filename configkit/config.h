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
extern bool is_ignored(char *entry);
//dump config file to screen
extern void jet_dump_config_file(char *file);

//get value asigned to entry in file
extern char *jet_lookup_value(char *file,char *entry);

//Add a new entry to file with value (you should normaly not use this)
extern void jet_add_new_value(char *file,  char *entry, char *value);
//set value to entry in file. If add is true, a new one will be created if value entry is not found
extern void jet_set_value(char *file, char *entry, char *value, bool add);

extern FILE *jet_config_file;

extern void jet_init_config_read(char *file);
extern char *jet_get_next_entry(void);
extern void jet_close_config_read(void);


#endif
