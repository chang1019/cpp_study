#include <stdio.h>

#include "File.h"
#include "StrUtil.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

File::Reader::Reader(const char* path)
  : status_(INIT),
    ifs_(),
    path_(copyCStr(path)),
    file_size_(0),
    read_at_once_(0),
    read_already_(0)
{
  ifs_.exceptions(std::ios::failbit);
}

File::Reader::~Reader() {
  delete[] path_;
}

int File::Reader::read(Byte** content, unsigned int size) {
  if(FINISHED == status_) {
      printf("[read] fail to read. stream alredy has been reached eof.\n");
      return -1;    
  }
  if(INIT == status_) {
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

  if (0 == file_size_) { return 0; }

  unsigned int rest_size = file_size_ - read_already_;
  read_at_once_ = ((size < rest_size) ? size : rest_size);
  *content = new char[read_at_once_];
  ifs_.read(*content, read_at_once_);

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

File::Writer::Writer(const char* path)
  : status_(INIT),
    ofs_(),
    path_(copyCStr(path))
{
  ofs_.exceptions(std::ios::failbit);
}

File::Writer::~Writer() {
  delete[] path_;
}

int File::Writer::write(const Byte* content, unsigned int len) {
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
  if (0 == len)  { len = getStrLen(content); }
  ofs_.write(content, len);
  return len;
}

////////////////////////////////////////////////////////////////////////////////
} //namespace practice
