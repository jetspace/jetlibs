/*
This file is licensed under the MIT-License
Copyright (c) 2015 Marius Messerschmidt
For more details view file 'LICENSE'
*/
#include "command.h"

static JetSpaceCMDArg *commandkit_arg_handle;
static char *commandkit_app_name;
static char *commandkit_app_version;
static int commandkit_arg_handle_n = 0;

void jetspace_add_cmd_line_argument(char sh, char *arg, int id, char *disc, JetSpaceCMDArgCallback cb, void *data)
{
  commandkit_arg_handle_n++;
  commandkit_arg_handle = realloc(commandkit_arg_handle, sizeof(JetSpaceCMDArg) * commandkit_arg_handle_n);

  commandkit_arg_handle[commandkit_arg_handle_n - 1].sh = sh;
  commandkit_arg_handle[commandkit_arg_handle_n - 1].id = id;
  commandkit_arg_handle[commandkit_arg_handle_n - 1].cb = cb;

  commandkit_arg_handle[commandkit_arg_handle_n - 1].arg = malloc(strlen(arg) +2);
  memset(commandkit_arg_handle[commandkit_arg_handle_n -1].arg, 0, strlen(arg) +2);
  strncpy(commandkit_arg_handle[commandkit_arg_handle_n -1].arg, "--", 2);
  strncat(commandkit_arg_handle[commandkit_arg_handle_n - 1].arg, arg, strlen(arg));

  commandkit_arg_handle[commandkit_arg_handle_n - 1].disc = malloc(strlen(disc));
  memset(commandkit_arg_handle[commandkit_arg_handle_n -1].disc, 0, strlen(disc));
  strncat(commandkit_arg_handle[commandkit_arg_handle_n - 1].disc, disc, strlen(disc));

  commandkit_arg_handle[commandkit_arg_handle_n - 1].data = data;
}

bool jetspace_parse_cmd_line(int argc, char **argv)
{
  for(int x = 0; x < argc; x++)
  {
    if(argv[x][0] == '-') // Argument
    {
      if(argv[x][1] == '-')  // Long argument
      {
          if(strcmp(argv[x], "--help") == 0)
          {
            jetspace_cmd_line_print_help();
            continue;
          }
          for(int z = 0; z < commandkit_arg_handle_n; z++)
          {
            if(strcmp(argv[x], commandkit_arg_handle[z].arg) == 0)
            {
              commandkit_arg_handle[z].cb(argc, argv, commandkit_arg_handle[z].id, commandkit_arg_handle[z].data);
              continue;
            }
          }
      }
      else  // Short Argument
      {
        for(int y = 1; y < strlen(argv[x]); y++)
        {
          char querry = argv[x][y];

          if(querry == 'h')
          {
            jetspace_cmd_line_print_help();
          }


          for(int z = 0; z < commandkit_arg_handle_n; z++)
          {
            if(commandkit_arg_handle[z].sh == 0)
              continue; //SKIP, does not provide short option

            if(commandkit_arg_handle[z].sh == querry)
            { // Found match for short argument

              commandkit_arg_handle[z].cb(argc, argv, commandkit_arg_handle[z].id, commandkit_arg_handle[z].data);
              continue;
            }
          }
        }
      }
    }
  }
  return true;
}

void jetspace_cmd_line_print_help(void)
{
  printf("%s - Version %s\n", commandkit_app_name, commandkit_app_version);
  for(int x = 0; x < strlen(commandkit_app_name) + strlen(commandkit_app_version) + 11; x++)
    putchar('-');
  putchar('\n');

  for(int x = 0; x < commandkit_arg_handle_n; x++)
  {
    if(commandkit_arg_handle[x].sh != 0)
      printf(" -%c | %s", commandkit_arg_handle[x].sh, commandkit_arg_handle[x].arg);
    else
      printf("      %s", commandkit_arg_handle[x].arg);
    for(int y = 0; y < (30 - strlen(commandkit_arg_handle[x].arg)); y++)
      putchar(' ');
    printf(" : %s\n", commandkit_arg_handle[x].disc);
  }

}

void jetspace_cmd_line_init(char *name, char *version)
{
  commandkit_app_name = malloc(strlen(name));
  memset(commandkit_app_name, 0, strlen(name));
  strncat(commandkit_app_name, name, strlen(name));

  commandkit_app_version = malloc(strlen(version));
  memset(commandkit_app_version, 0, strlen(version));
  strncat(commandkit_app_version, version, strlen(version));
}

void jetspace_cmd_line_free(void)
{
  for(int x = 0; x < commandkit_arg_handle_n; x++)
  {
    free(commandkit_arg_handle[x].disc);
    free(commandkit_arg_handle[x].arg);
  }
  free(commandkit_arg_handle);
  free(commandkit_app_version);
  free(commandkit_app_name);
}
