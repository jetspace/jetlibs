//Public Domain (CC0) tool to test ConfigKit

#include <jetspace/configkit.h>

int main(void)
{
  jet_dump_config_file("configkit/test.conf");
  jet_lookup_value("configkit/test.conf", "a");
  jet_set_value("configkit/test.conf", "ABC", "123", true);
  return 0;
}
