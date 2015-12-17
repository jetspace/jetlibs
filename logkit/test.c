//Public Domain (CC0) tool to test the logkit

#include <jetspace/logkit.h>

int main(void)
{
    jet_log_set_log_level_from_enviroment();
    jetspace_logkit_enable_glib_handler();

    printf("Current Loglevel is :%d\n", jet_log_get_log_level());

    g_debug("DEBUG");
    g_info("INFO");
    g_message("MESSAGE");
    g_warning("WARNING");
    g_critical("CRITICAL");
    g_error("ERROR");

    return 0;
}
