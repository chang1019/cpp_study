#include <gtest/gtest.h>
#include <stdio.h>

#include "List.h"
#include "StrUtil.h"

using namespace practice;

////////////////////////////////////////////////////////////////////////////////
// test util class

class Value {
private:
  const char* str_;

public:
  Value(const char* str)
    : str_(copyCStr(str))
  {}

  ~Value() { delete[] str_; }

  const char* get() { return str_; }
};

////////////////////////////////////////////////////////////////////////////////
// tests
class ListTest : public ::testing::Test {
};

TEST_F(ListTest, addGetTest_001) {
  Value v1("foo");
  Value v2("bar");
  Value v3("foobar");

  List l;
  ASSERT_FALSE(l.add(1, &v1));

  ASSERT_TRUE(l.add(0, &v1));
  ASSERT_EQ(1U, l.size());

  ASSERT_TRUE(l.add(0, &v2));
  ASSERT_EQ(2U, l.size());

  ASSERT_TRUE(l.add(0, &v3));
  ASSERT_EQ(3U, l.size());

  Value* v = NULL;
  v = static_cast<Value*>(l.get(0));
  ASSERT_STREQ("foobar", v->get());
  v = static_cast<Value*>(l.get(1));
  ASSERT_STREQ("bar", v->get());
  v = static_cast<Value*>(l.get(2));
  ASSERT_STREQ("foo", v->get());
  v = static_cast<Value*>(l.get(3));
  ASSERT_TRUE(NULL == v);

  ASSERT_EQ(3U, l.size());
  l.clear();
  ASSERT_EQ(0, l.size());
}

TEST_F(ListTest, addGetTest_002) {
  Value v1("foo");
  Value v2("bar");
  Value v3("foobar");

  List l;
  ASSERT_FALSE(l.add(1, &v1));
  ASSERT_TRUE(l.add(0, &v1));
  ASSERT_EQ(1U, l.size());

  ASSERT_TRUE(l.add(1, &v2));
  ASSERT_EQ(2U, l.size());

  ASSERT_TRUE(l.add(2, &v3));
  ASSERT_EQ(3U, l.size());

  Value* v = NULL;
  v = static_cast<Value*>(l.get(0));
  ASSERT_STREQ("foo", v->get());
  v = static_cast<Value*>(l.get(1));
  ASSERT_STREQ("bar", v->get());
  v = static_cast<Value*>(l.get(2));
  ASSERT_STREQ("foobar", v->get());
  v = static_cast<Value*>(l.get(3));
  ASSERT_TRUE(NULL == v);

  ASSERT_EQ(3U, l.size());
  l.clear();
  ASSERT_EQ(0, l.size());
}

TEST_F(ListTest, addRemoveTest_001) {
  Value v1("foo");
  Value v2("bar");
  Value v3("foobar");

  List l;
  ASSERT_FALSE(l.add(1, &v1));
  ASSERT_TRUE(l.add(0, &v1));
  ASSERT_EQ(1U, l.size());

  ASSERT_TRUE(l.add(1, &v2));
  ASSERT_EQ(2U, l.size());

  ASSERT_TRUE(l.add(2, &v3));
  ASSERT_EQ(3U, l.size());

  Value* v = NULL;
  v = static_cast<Value*>(l.remove(3));
  ASSERT_TRUE(NULL == v);
  v = static_cast<Value*>(l.remove(2));
  ASSERT_STREQ("foobar", v->get());
  v = static_cast<Value*>(l.remove(1));
  ASSERT_STREQ("bar", v->get());
  v = static_cast<Value*>(l.remove(0));
  ASSERT_STREQ("foo", v->get());

  ASSERT_EQ(0, l.size());
}

TEST_F(ListTest, putPopFrontTest_001) {
  Value v1("foo");
  Value v2("bar");
  Value v3("foobar");

  List l;
  l.put(&v1);
  ASSERT_EQ(1U, l.size());

  l.put(&v2);
  ASSERT_EQ(2U, l.size());

  l.put(&v3);
  ASSERT_EQ(3U, l.size());

  Value* v = NULL;
  v = static_cast<Value*>(l.popFront());
  ASSERT_STREQ("foobar", v->get());
  v = static_cast<Value*>(l.popFront());
  ASSERT_STREQ("bar", v->get());
  v = static_cast<Value*>(l.popFront());
  ASSERT_STREQ("foo", v->get());

  ASSERT_EQ(0, l.size());
}

TEST_F(ListTest, pushBackPopFrontTest_001) {
  Value v1("foo");
  Value v2("bar");
  Value v3("baz");
  Value v4("foobar");
  Value v5("foobaz");
  Value v6("barfoo");
  Value v7("barbaz");
  Value v8("bazfoo");
  Value v9("bazbar");

  List l;
  l.pushBack(&v1); ASSERT_EQ(1U, l.size());
  l.pushBack(&v2); ASSERT_EQ(2U, l.size());
  l.pushBack(&v3); ASSERT_EQ(3U, l.size());
  l.pushBack(&v4); ASSERT_EQ(4U, l.size());
  l.pushBack(&v5); ASSERT_EQ(5U, l.size());
  l.pushBack(&v6); ASSERT_EQ(6U, l.size());
  l.pushBack(&v7); ASSERT_EQ(7U, l.size());
  l.pushBack(&v8); ASSERT_EQ(8U, l.size());
  l.pushBack(&v9); ASSERT_EQ(9U, l.size());

  Value* v = NULL;
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("foo", v->get());
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("bar", v->get());
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("baz", v->get());
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("foobar", v->get());
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("foobaz", v->get());
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("barfoo", v->get());
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("barbaz", v->get());
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("bazfoo", v->get());
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("bazbar", v->get());

  ASSERT_EQ(0, l.size());
}
