#include <iostream>
#include <stdio.h>

#include <gtest/gtest.h>

#include "FileReader.h"
#include "FileWriter.h"

using namespace practice;

class FileTest : public ::testing::Test {
protected:
  static void SetUpTestCase() {
    printf("[SetupTestCase] trying to remove test output files...\n");
    remove("sample_out.txt");
    remove("sample_out.jpg");
    remove("sample_void_out");
  }

  static void TearDownTestCase() {
    printf("[TearDownTestCase] trying to remove test output files...\n");
    remove("sample_out.txt");
    remove("sample_out.jpg");
    remove("sample_void_out");
  }
};

TEST_F(FileTest, readTest_001) {
  FileReader reader("sample_in.txt");
  char buf[4096];
  int bufCount = 0;
  while (-1 < (bufCount = reader.read(buf, 4096))) {
  }
  ASSERT_STREQ("hoge piyo\n", buf);
}

TEST_F(FileTest, readTest_002) {
  FileReader reader("sample_void_in");
  char buf[4096];
  int bufCount = 0;
  bufCount = reader.read(buf, 4096);
  ASSERT_EQ(0, bufCount);
  bufCount = reader.read(buf, 4096);
  ASSERT_EQ(-1, bufCount); // fail to read, for readching eof.
}

TEST_F(FileTest, writeTest_001) {
  {
    FileWriter writer("sample_out.txt");
    writer.write("a", 1);
    writer.write("bcd", 3);
    writer.write("\n", 1);
    writer.write("漢字");
  }
  {
    FileReader reader("sample_out.txt");
    char buf[4096];
    int bufCount = 0;
    while (-1 < (bufCount = reader.read(buf, 4096))) {}
    ASSERT_STREQ("abcd\n漢字", buf);
  }
}

TEST_F(FileTest, copyTest_001) {
  int fileSize = 0;
  {
    FileReader reader("sample_in.jpg");
    FileWriter writer("sample_out.jpg");
    Byte buf[4096];
    int bufCount = 0;
    while (-1 < (bufCount = reader.read(buf, 4096))) {
      fileSize += bufCount;
      writer.write(buf, bufCount);
    }
  }
  ASSERT_EQ(57679U, fileSize);
  {
    FileReader origin("sample_in.jpg");
    FileReader target("sample_out.jpg");
    Byte bufOrigin[4096];
    Byte bufTarget[4096];
    int bufCountOrigin = 0;
    int bufCountTarget = 0;
    while (true) {
      bufCountOrigin = origin.read(bufOrigin, 4096);
      bufCountTarget = target.read(bufTarget, 4096);
      ASSERT_EQ(bufCountTarget, bufCountOrigin);
      if (bufCountOrigin < 0) break;
      ASSERT_STREQ(bufTarget, bufOrigin);
    }
  }
}

TEST_F(FileTest, copyTest_002) {
  int fileSize = 0;
  {
    FileReader reader("sample_void_in");
    FileWriter writer("sample_void_out");
    Byte buf[4096];
    int bufCount = 0;
    while (-1 < (bufCount = reader.read(buf, 4096))) {
      fileSize += bufCount;
      writer.write(buf, bufCount);
    }
  }
  ASSERT_EQ(0, fileSize);
  {
    FileReader origin("sample_void_in");
    FileReader target("sample_void_out");
    Byte bufOrigin[4096];
    Byte bufTarget[4096];
    int bufCountOrigin = 0;
    int bufCountTarget = 0;
    while (true) {
      bufCountOrigin = origin.read(bufOrigin, 4096);
      bufCountTarget = target.read(bufTarget, 4096);
      ASSERT_EQ(bufCountTarget, bufCountOrigin);
      if (bufCountOrigin < 0) break;
      ASSERT_STREQ(bufTarget, bufOrigin);
    }
  }
}
