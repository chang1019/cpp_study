#include <stdio.h>

#include "FileReader.h"
#include "StrUtil.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

FileReader::FileReader(const char* path)
  : status_(INIT),
    ifs_(),
    path_(copyCStr(path)),
    file_size_(0),
    read_at_once_(0),
    read_already_(0)
{
  ifs_.exceptions(std::ios::failbit);
}

FileReader::~FileReader() {
  delete[] path_;
}

int FileReader::read(Byte* content, unsigned int size) {
  if (NULL == content) {
      printf("[read] fail to read. parameter is illegal.\n");
      return -1;
  }
  if (FINISHED == status_) {
      printf("[read] fail to read. stream alredy has been reached eof.\n");
      return -1;    
  }
  if (INIT == status_) {
    // open stream
    try{
      ifs_.open(path_);
    }
    catch (std::ios_base::failure& e) {
      return -1;
    }
    status_ = OPENED;
    ifs_.seekg(0, std::ifstream::end);
    file_size_ = static_cast<unsigned int>(ifs_.tellg());
    ifs_.seekg(0, std::ifstream::beg);
  }

  unsigned int rest_size = file_size_ - read_already_;
  read_at_once_ = ((size < rest_size) ? size : rest_size);
  ifs_.read(content, read_at_once_);
  if (read_at_once_ < size) {
    memset(content + read_at_once_, '\0', size - read_at_once_);
  }

  unsigned int tmp_already = read_already_;
  read_already_ += read_at_once_;
  if (read_already_ < file_size_) {
    status_ = READING;
  }
  else {
    status_ = FINISHED;
    read_already_ = file_size_;
  }

  return (read_already_ - tmp_already);
}

////////////////////////////////////////////////////////////////////////////////
} //namespace practice
