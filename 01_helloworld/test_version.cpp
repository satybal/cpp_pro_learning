#include <gtest/gtest.h>
#include "lib.h"

// Demonstrate some basic assertions.
TEST(test_version, version_is_valid) {
    ASSERT_NE(version(), 100);
}