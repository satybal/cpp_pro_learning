add_test( test_version.version_is_valid /home/timur/CPP_basic/cpp_pro_learning/homeworks/build/test_version [==[--gtest_filter=test_version.version_is_valid]==] --gtest_also_run_disabled_tests)
set_tests_properties( test_version.version_is_valid PROPERTIES WORKING_DIRECTORY /home/timur/CPP_basic/cpp_pro_learning/homeworks/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( test_version_TESTS test_version.version_is_valid)
