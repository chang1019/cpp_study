#ifndef _FILE_H_
#define _FILE_H_

#include <fstream>

#include "Byte.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

#define BUFFER_MAX 4096

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
   * @param[out] content allocated internal. caller must to delete[] this byte array.
   * @param[in] size size of byte array.
   *            if size is not given implicitly, BUFFER_MAX is used as default value.
   * @return read byte size if succeeded. -1 if failed.
   */
  int read(Byte** content, unsigned int size = BUFFER_MAX);
};

////////////////////////////////////////////////////////////////////////////////
} //namespace practice

#endif
