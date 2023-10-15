#include <gtest/gtest.h>
#include <stdexcept>

#include "../s21_containers.h"
#include "../util.hpp"

TEST(VectorTest, Creation) { s21::vector<int> vec; }

TEST(VectorTest, Push) {
  s21::vector<int> vec;

  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  EXPECT_EQ(vec.at(0), 1);
  EXPECT_EQ(vec.at(1), 2);
  EXPECT_EQ(vec.at(2), 3);
}

TEST(VectorTest, Iterator) {
  s21::vector<int> vec({5, 4, 3, 2, 1});

  int start = 5;
  int count = 0;
  for (int &elem : vec) {
    EXPECT_EQ(elem, start--);
    count++;
  }

  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(count, 5);
}

TEST(VectorTest, Reserve) {
  s21::vector<int> vec;

  for (int i = 0; i < 10'000; i++)
    vec.push_back(i);

  vec.reserve(9999);
  vec.reserve(20000);
  vec.reserve(100);
  vec.reserve(10000);
  vec.reserve(200);

  EXPECT_EQ(vec.size(), 100);
  int start = 0;
  for (int elem : vec)
    EXPECT_EQ(elem, start++);
}

TEST(VectorTest, MoveAssign) {
  s21::vector<int> vec_a({5, 4, 3, 2, 1});
  s21::vector<int> vec_b({1, 2, 3, 4, 5, 6});

  auto a = std::move(vec_a);

  vec_a = std::move(vec_b);
  vec_b = std::move(a);

  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(vec_a.size(), 6);
  EXPECT_EQ(vec_b.size(), 5);

  EXPECT_EQ(vec_a.at(5), 6);
  EXPECT_EQ(vec_b.at(4), 1);
}


TEST(VectorTest, Eq) {
  s21::vector<int> a({5, 4, 3, 2, 1});
  s21::vector<int> b({1, 2, 3, 4, 5, 6});
  s21::vector<int> c({5, 4, 3, 2, 1, 5});
  c.pop_back();

  EXPECT_EQ(a, c);
  EXPECT_EQ(c, a);
  EXPECT_NE(a, b);
  EXPECT_NE(b, c);
  EXPECT_NE(a, 5);
  EXPECT_NE(b, "HELLO THERE");
}


TEST(VectorTest, Insert) {
  s21::vector<int> a({5, 4, 3, 2, 1});
  s21::vector<int> b({5, 4, 10, 3, 2, 1});

  EXPECT_NE(a, b);

  a.insert(a.begin() + 2, 10);
  EXPECT_EQ(a, b);
}