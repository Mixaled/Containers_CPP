#include <gtest/gtest.h>

#include <stdexcept>

#include "../s21_containers.h"

TEST(StackTest, Creation) {
  s21::stack<int> stk;
  EXPECT_EQ(stk.size(), 0);
  EXPECT_TRUE(stk.empty());
}

TEST(StackTest, Pushing) {
  s21::stack<int> stk;
  stk.push(10);
  EXPECT_FALSE(stk.empty());
}

TEST(StackTest, Removing) {
  s21::stack<int> stk;
  stk.push(10);
  EXPECT_FALSE(stk.empty());
  stk.pop();
  EXPECT_TRUE(stk.empty());
}

TEST(StackTest, BeginEndTest) {
  s21::stack<int> mystack;
  mystack.push(10);
  mystack.push(10);
  mystack.push(10);

  s21::stack<int>::iterator it = mystack.begin();

  while (it != mystack.end()) {
    EXPECT_EQ(*it, 10);
    ++it;
  }
}
TEST(StackTest, TopTest) {
  s21::stack<int> stk;
  stk.push(10);
  EXPECT_EQ(stk.top(), 10);
  stk.push(20);
  EXPECT_EQ(stk.top(), 20);
}

TEST(StackTest, CopyConstructorTest) {
  s21::stack<int> original;
  original.push(10);
  original.push(20);
  s21::stack<int> copy(original);
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.top(), original.top());
}

TEST(StackTest, AssignmentOperatorTest) {
  s21::stack<int> original;
  original.push(10);
  original.push(20);
  s21::stack<int> copy;
  copy = original;
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.top(), original.top());
}

TEST(StackTest, MoveConstructorTest) {
  s21::stack<int> original;
  original.push(10);
  original.push(20);
  s21::stack<int> moved(std::move(original));
  EXPECT_TRUE(original.empty());
  EXPECT_EQ(moved.size(), 2);
  EXPECT_EQ(moved.top(), 20);
}
