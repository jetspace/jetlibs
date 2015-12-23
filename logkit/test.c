//Public Domain (CC0) tool to test the logkit
#include <jetspace/logkit.h>

int main(int argc, char **argv)
{
    jetspace_logkit_init(argc, argv);
    jet_log_set_log_level_from_enviroment();
    jetspace_logkit_enable_glib_handler();

    printf("Current Loglevel is :%d\n", jet_log_get_log_level());
    long x = 0;
    time(&x);
    jet_log_warning("Test Warning with variable parameter %.2f", (float) 10/3);

    return 0;
}
