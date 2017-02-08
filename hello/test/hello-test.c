#include <check.h>

START_TEST(addition) {
	ck_assert_int_eq(1 + 1, 2);
}
END_TEST

START_TEST(multiplication) {
	ck_assert_int_eq(2 * 2, 4);
}
END_TEST

Suite *arithmetic_suite(void) {
	Suite* s = suite_create("Arithmetic");
	TCase *tc_core = tcase_create("Core");

	tcase_add_test(tc_core, addition);
	tcase_add_test(tc_core, multiplication);
	suite_add_tcase(s, tc_core);

	return s;
}

int main(void) {
	Suite *s = arithmetic_suite();
	SRunner *sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	int number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return number_failed == 0 ? 0 : 1;
}
