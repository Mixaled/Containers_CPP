#include <gtest/gtest.h>

#include <stdexcept>

#include "../s21_containers.h"

TEST(ListTest, Creation) {
  s21::list<int> lst;
  EXPECT_EQ(lst.size(), 0);
  EXPECT_TRUE(lst.empty());
}

TEST(ListTest, CreationList) {
  s21::list<int> lst({10, 2, 3, 4});
  EXPECT_EQ(lst.size(), 4);
}
