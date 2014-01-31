#include <iostream>
#include <stdio.h>

#include <gtest/gtest.h>

#include "File.h"

using namespace practice;

class FileTest : public ::testing::Test {
protected:
  static void SetUpTestCase() {
    printf("[SetupTestCase] trying to remove test output files...\n");
    remove("sample_out.txt");
    remove("sample_out.jpg");
  }

  static void TearDownTestCase() {
    printf("[TearDwonTestCase] trying to remove test output files...\n");
    remove("sample_out.txt");
    remove("sample_out.jpg");
  }
};

TEST_F(FileTest, readTest_001) {
  File::Reader reader("sample_in.txt");
  char* buf = NULL;
  int bufCount = 0;
  while (-1 < (bufCount = reader.read(&buf))) {
  }
  ASSERT_STREQ("hoge piyo\n", buf);
  delete[] buf;
}

TEST_F(FileTest, writeTest_001) {
  {
    File::Writer writer("sample_out.txt");
    writer.write("a", 1);
    writer.write("bcd", 3);
    writer.write("\n", 1);
    writer.write("漢字");
  }
  {
    File::Reader reader("sample_out.txt");
    char* buf = NULL;
    int bufCount = 0;
    while (-1 < (bufCount = reader.read(&buf))) {}
    ASSERT_STREQ("abcd\n漢字", buf);
    delete[] buf;
  }
}

TEST_F(FileTest, copyTest_001) {
  int fileSize = 0;
  {
    File::Reader reader("sample_in.jpg");
    File::Writer writer("sample_out.jpg");
    Byte* buf = NULL;
    int bufCount = 0;
    while (-1 < (bufCount = reader.read(&buf))) {
      fileSize += bufCount;
      writer.write(buf, bufCount);
    }
  }
  ASSERT_EQ(57679U, fileSize);
  {
    File::Reader origin("sample_in.jpg");
    File::Reader target("sample_out.jpg");
    Byte* bufOrigin = NULL;
    Byte* bufTarget = NULL;
    int bufCountOrigin = 0;
    int bufCountTarget = 0;
    while (true) {
      bufCountOrigin = origin.read(&bufOrigin);
      bufCountTarget = target.read(&bufTarget);
      ASSERT_EQ(bufCountTarget, bufCountOrigin);
      if (bufCountOrigin < 0) break;
      ASSERT_STREQ(bufTarget, bufOrigin);
    }
  }
}
