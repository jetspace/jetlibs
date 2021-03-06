#include <jetspace/commandkit.h>
#include <stdio.h>

bool argcb(int argc, char **argv, int id, void *data)
{

  printf("Recived arg %d with payload {%s | %d}\n", id, (char *) data, *(int *)data);

  return true;
}

int main(int argc, char **argv)
{
  jetspace_cmd_line_init("TestApp", "1.0.2b");

  int x = 42;
  jetspace_add_cmd_line_argument('o', "other-example", 1, "Some ohter example action", argcb, &x);
  jetspace_add_cmd_line_argument('e', "example", 2, "Some example action", argcb, "box");
  jetspace_add_cmd_line_argument(0, "only-long-option", 2, "Super complex thing", argcb, "complex");

  jetspace_parse_cmd_line(argc,argv);
  jetspace_cmd_line_free();
  return 0;
}
