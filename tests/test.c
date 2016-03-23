#include <check.h>
#include <stdbool.h>
#include <jetspace/configkit.h>

#define CONFIG "test.conf"

START_TEST(test_ignored)
{
  if(!is_ignored("// Comment"))
  {
    ck_abort_msg("configkit does not identify comments");
  }
  else if(!is_ignored("\n"))
  {
    ck_abort_msg("configkit does not ignore empty lines");
  }
  else if(is_ignored("abc:def"))
  {
    ck_abort_msg("configkit does skip valid entry");
  }
}
END_TEST

START_TEST(lookup)
{
    ck_assert_str_eq("value", jet_lookup_value(CONFIG, "key"));
    ck_assert_str_eq("123", jet_lookup_value(CONFIG, "abc"));
}
END_TEST

START_TEST(batch_read)
{
  jet_init_config_read(CONFIG);

  char *buff;
  buff = jet_get_next_entry(); // key
  ck_assert_str_eq("key", buff);
  buff = jet_get_next_entry(); // abc
  ck_assert_str_eq("abc", buff);
  jet_close_config_read();
}
END_TEST

START_TEST(add_value)
{
  jet_add_new_value(CONFIG, "test", "sample");
  ck_assert_str_eq("sample", jet_lookup_value(CONFIG, "test"));
}
END_TEST

START_TEST(set_value)
{
  jet_set_value(CONFIG, "key", "cba", false);
  ck_assert_str_eq("cba", jet_lookup_value(CONFIG, "key"));
  jet_set_value(CONFIG, "newkey", "1234", true);
  ck_assert_str_eq("1234", jet_lookup_value(CONFIG, "newkey"));
}
END_TEST

START_TEST(conf_dump)
{
  jet_dump_config_file(CONFIG);
}
END_TEST

Suite *test_suite(void)
{
  Suite *s = suite_create("Jetspace Jetlibs");
  TCase *confkit = tcase_create("configkit");
  tcase_add_test(confkit, test_ignored);
  tcase_add_test(confkit, lookup);
  tcase_add_test(confkit, batch_read);
  tcase_add_test(confkit, add_value);
  tcase_add_test(confkit, set_value);
  tcase_add_test(confkit, conf_dump);
  suite_add_tcase(s, confkit);

  return s;
}

int main(int argc, char **argv)
{
  Suite *s = test_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);

  int res = srunner_ntests_failed(sr);
  srunner_free(sr);

  return sr;
}
