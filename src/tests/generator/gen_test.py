import random 
import string
import sys
from datetime import date, timedelta, datetime
header = """
#include <gtest/gtest.h>
#include <stdexcept>
#include "../s21_containers.h"
    """

arg1 = int(sys.argv[1]) if len(sys.argv) > 1 else 5
def init_list(format_list):
    return str(format_list).replace('[', '').replace(']', '')


def test(name, file, function):
    for i in range(arg1):
        file.write(function(name+str(i)))
    

def test_case_copy(name, values = None):
    if values is None:
        values = random.choices(range(1000), k=random.randint(1, 100))
    test = """
TEST(ListTest, {0}) {{
  s21::list<int> lst1({{{1}}});
  s21::list<int> lst2(lst1);
  EXPECT_EQ(lst1.size(), lst2.size());
  auto it1 = lst1.begin();
  auto it2 = lst2.begin();
  for (; it1 != lst1.end() && it2 != lst2.end(); ++it1, ++it2) {{
    EXPECT_EQ(*it1, *it2);
  }}
  EXPECT_TRUE(it1 == lst1.end() && it2 == lst2.end());
}}
""".format(name, init_list(values))
    return test

def test_case_move(name, values = None):
    if values is None:
        values = random.choices(range(1000), k=random.randint(1, 100))
    test = """
TEST(ListTest, {0}) {{
  s21::list<int> lst1({{{1}}});
  s21::list<int> lst2(std::move(lst1));
  EXPECT_EQ(lst1.size(), 0);
  EXPECT_EQ(lst2.size(), {2});
}}
""".format(name, init_list(values), len(values))
    return test

def test_case_assign(name, values = None):
    if values is None:
        values = random.choices(range(1000), k=random.randint(1, 100))
    test = """
TEST(ListTest, {0}) {{
  s21::list<int> lst1({{{1}}});
  s21::list<int> lst2;
  lst2 = std::move(lst1);
  EXPECT_EQ(lst1.size(), 0);
  EXPECT_EQ(lst2.size(), {2});
}}
""".format(name, init_list(values), len(values))
    return test

def test_case_create(name, values = None):
    if values is None:
        values = random.choices(range(1000), k=random.randint(1, 100))  
    test = """
TEST(ListTest, {0}) {{
  s21::list<int> lst({{{1}}});
  EXPECT_EQ(lst.size(), {2});
  EXPECT_FALSE(lst.empty());
}}
""".format(name, init_list(values), len(values))
    return test


def test_case_sort(name, values = None):
    if values is None:
        values = random.choices(range(1000), k=random.randint(1, 100)) 
    sorted_val = sorted(values)
    test = """
TEST(ListTest, {0}) {{
  s21::list<int> lst({{{1}}});
  s21::list<int> res({{{2}}});
  lst.sort();
  EXPECT_EQ(lst, res);
}}
""".format(name, init_list(values), init_list(sorted_val))
    return test

def test_case_unique(name, values=None):
    if values is None:
        values = random.choices(range(1000), k=random.randint(1, 100))
    unique_values = list(set(values))
    
    test = """
TEST(ListTest, {0}) {{
  s21::list<int> lst({{{1}}});
  s21::list<int> res({{{2}}});
  lst.unique();
  EXPECT_EQ(lst, res);
}}
""".format(name, init_list(values), init_list(unique_values))
    return test


def test_case_clear(name, values = None):
    if values is None:
        values = random.choices(range(1000), k=random.randint(1, 100)) 
    sorted_val = sorted(values)
    test = """
TEST(ListTest, {0}) {{
  s21::list<int> lst({{{1}}});
  lst.clear();
  EXPECT_TRUE(lst.empty());
}}
""".format(name, init_list(values), init_list(sorted_val))
    return test

def test_case_reverse(name, values = None):
    if values is None:
        values = random.choices(range(1000), k=random.randint(1, 100)) 
    reversed_val = list(reversed(values))
    test = """
TEST(ListTest, {0}) {{
  s21::list<int> lst({{{1}}});
  lst.clear();
  EXPECT_TRUE(lst.empty());
}}
""".format(name, init_list(values), init_list(reversed_val))
    return test

with open("test_list.cpp", "w") as f:
    f.write(header)
    test("Create", f, test_case_create)
    test("Copy", f, test_case_copy)
    test("Assign", f, test_case_assign)
    test("Move", f, test_case_move)
    test("Sort", f, test_case_sort)
    test("Clear", f, test_case_clear)
    test("Unique", f, test_case_unique)
    test("Reverses", f, test_case_reverse)


