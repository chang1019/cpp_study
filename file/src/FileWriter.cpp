#include <stdio.h>

#include "FileWriter.h"
#include "StrUtil.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

FileWriter::FileWriter(const char* path)
  : status_(INIT),
    ofs_(),
    path_(copyCStr(path))
{
  ofs_.exceptions(std::ios::failbit);
}

FileWriter::~FileWriter() {
  delete[] path_;
}

int FileWriter::write(const Byte* content, unsigned int size) {
  if (OPENED != status_) {
    try {
      ofs_.open(path_, std::ios::binary);
    }
    catch (std::ios_base::failure& e) {
      printf("[write] fail to open file output stream.\n");
      return -1;
    }
    status_ = OPENED;
  }
  if (0 == size)  { size = getStrLen(content); }
  ofs_.write(content, size);
  return size;
}

////////////////////////////////////////////////////////////////////////////////
} //namespace practice
