//Public Domain (CC0) tool to test the logkit

#include <jetspace/logkit.h>

int main(void)
{
    jet_log_set_log_level_from_enviroment();

    printf("Current Loglevel is :%d\n", jet_log_get_log_level());
    jet_log_debug("DEBUG!");
    jet_log_note("NOTE!");
    jet_log_message("MESSAGE!");
    jet_log_warning("WARNING!");
    jet_log_error("ERROR!");
    jet_log_critical("CRITICAL!");
    jet_log_failure("FAILURE!");
    return 0;
}
