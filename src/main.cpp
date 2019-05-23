#include <gtest/gtest.h>

int main() {
  ::testing::InitGoogleTest();
  ::testing::GTEST_FLAG(filter) = "Thorup.*";
  return RUN_ALL_TESTS();
}