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
  int i_;

public:
  Value(const char* str)
    : str_(copyCStr(str))
  {}

  Value(int i)
    : str_(NULL),
      i_(i)
  {}

  ~Value() {
    if (NULL != str_) { delete[] str_; }
  }

  const char* getStr() { return str_; }
  int getInt() { return i_; }
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
  v = static_cast<Value*>(l.get(0)); ASSERT_STREQ("foobar", v->getStr());
  v = static_cast<Value*>(l.get(1)); ASSERT_STREQ("bar", v->getStr());
  v = static_cast<Value*>(l.get(2)); ASSERT_STREQ("foo", v->getStr());
  v = static_cast<Value*>(l.get(3)); ASSERT_TRUE(NULL == v);

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
  v = static_cast<Value*>(l.get(0)); ASSERT_STREQ("foo", v->getStr());
  v = static_cast<Value*>(l.get(1)); ASSERT_STREQ("bar", v->getStr());
  v = static_cast<Value*>(l.get(2)); ASSERT_STREQ("foobar", v->getStr());
  v = static_cast<Value*>(l.get(3)); ASSERT_TRUE(NULL == v);

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
  v = static_cast<Value*>(l.remove(3)); ASSERT_TRUE(NULL == v);
  v = static_cast<Value*>(l.remove(2)); ASSERT_STREQ("foobar", v->getStr());
  v = static_cast<Value*>(l.remove(1)); ASSERT_STREQ("bar", v->getStr());
  v = static_cast<Value*>(l.remove(0)); ASSERT_STREQ("foo", v->getStr());

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
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("foobar", v->getStr());
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("bar", v->getStr());
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("foo", v->getStr());

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
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("foo", v->getStr());
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("bar", v->getStr());
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("baz", v->getStr());
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("foobar", v->getStr());
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("foobaz", v->getStr());
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("barfoo", v->getStr());
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("barbaz", v->getStr());
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("bazfoo", v->getStr());
  v = static_cast<Value*>(l.popFront()); ASSERT_STREQ("bazbar", v->getStr());

  ASSERT_EQ(0, l.size());
}


TEST_F(ListTest, IteratorTest_001) {
  List l;
  Value v1(0); l.pushBack(&v1);
  Value v2(1); l.pushBack(&v2);
  Value v3(2); l.pushBack(&v3);

  List::Iterator i = l.begin();
  ASSERT_EQ(0, static_cast<Value*>(*i)->getInt());
  List::Iterator j = i++;
  ASSERT_EQ(1, static_cast<Value*>(*i)->getInt());
  ASSERT_EQ(0, static_cast<Value*>(*j)->getInt());
  j = i++;
  ASSERT_EQ(2, static_cast<Value*>(*i)->getInt());
  ASSERT_EQ(1, static_cast<Value*>(*j)->getInt());
  ASSERT_TRUE(i == l.end());
}

TEST_F(ListTest, IteratorTest_002) {
  List l;
  Value v1(0); l.pushBack(&v1);
  Value v2(1); l.pushBack(&v2);
  Value v3(2); l.pushBack(&v3);
  Value v4(3); l.pushBack(&v4);
  Value v5(4); l.pushBack(&v5);
  Value v6(5); l.pushBack(&v6);
  Value v7(6); l.pushBack(&v7);
  Value v8(7); l.pushBack(&v8);
  Value v9(8); l.pushBack(&v9);
  Value v10(9); l.pushBack(&v10);
  int val = 0;
  List::Iterator i = l.begin();
  List::Iterator j = l.begin();
  List::Iterator end = l.end();
  ASSERT_FALSE(i == end);
  for (; i != end; j = i++) {
    ASSERT_EQ(val, (static_cast<Value*>(*i))->getInt());
    if (0 < val) {
      ASSERT_EQ(val - 1, (static_cast<Value*>(*j))->getInt());
    }
    val++;
  }
  ASSERT_TRUE(i == end);
}
