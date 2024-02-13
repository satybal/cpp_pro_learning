#include <gtest/gtest.h>
#include "ip_filter.hpp"

TEST(split_test, splits_well) {
    ASSERT_EQ(split("1.2.3.4", '.').size(), 4);
    ASSERT_EQ(split("1\t2\t3", '\t').size(), 3);
}

TEST(reverse_sort_test, sorts_well) {
    std::vector<std::vector<std::string>> pool {
        {"1", "2", "3", "4"},
        {"123", "234", "345", "456"},
        {"321", "432", "543", "654"}
    };

    reverse_sort(pool);

    ASSERT_EQ(pool[0][0], "321");
    ASSERT_EQ(pool[1][0], "123");
    ASSERT_EQ(pool[2][0], "1");
}