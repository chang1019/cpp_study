#ifndef _FILE_H_
#define _FILE_H_

#include <fstream>

#include "Byte.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

class FileReader {
private:
  enum {
    INIT = 0,
    OPENED,
    READING,
    FINISHED,
  } status_;
  std::ifstream ifs_;
  const char* path_;

  unsigned int file_size_;
  unsigned int read_at_once_;
  unsigned int read_already_;

public:
  /**
   * Constructor of File Reader.
   *
   * @param[in] path file path to read.
   */
  FileReader(const char* path);
  ~FileReader();

  /**
   * read byte data from file as binary data.
   *
   * @param[out] content byte array as a data container.
   * @param[in] size size of byte array.
   * @return read byte size if succeeded. -1 if failed.
   */
  int read(Byte* content, unsigned int size);
};

////////////////////////////////////////////////////////////////////////////////
} //namespace practice

#endif
