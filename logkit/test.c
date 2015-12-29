//Public Domain (CC0) tool to test the logkit
#define _LOGKIT_DISABLE_GLIB_SUPPORT
#include <jetspace/logkit.h>

int main(int argc, char **argv)
{
    jetspace_logkit_init(argc, argv);
    jetspace_set_log_level_from_environment();

    printf("Current Loglevel is :%d\n", jetspace_get_log_level());
    long x = 0;
    time(&x);
    jetspace_warning("Test Warning with variable parameter %.2f", (float) 10/3);

    return 0;
}
