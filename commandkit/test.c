#include <jetspace/commandkit.h>
#include <stdio.h>

bool argcb(int argc, char **argv, int id, void *data)
{
  printf("Recived arg %d\n", id);

  return true;
}

int main(int argc, char **argv)
{

  jetspace_cmd_line_init("TestApp", "1.0.5");

  jetspace_add_cmd_line_argument('o', "other-example", 1, "Some ohter example action", argcb);
  jetspace_add_cmd_line_argument('e', "example", 2, "Some example action", argcb);

  jetspace_parse_cmd_line(argc,argv);
  return 0;
}
