#ifndef _FILEWRITER_H_
#define _FILEWRITER_H_

#include <fstream>

#include "Byte.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

/**
 * File Writer class.
 */
class FileWriter {
private:
  enum {
    INIT = 0,
    OPENED,
  } status_;
  std::ofstream ofs_;
  const char* path_;

public:
  /**
   * Constructor of File Writer.
   *
   * @param[in] path file path to write.
   */
  FileWriter(const char* path);
  ~FileWriter();

  /**
   * write byte data from file as binray data.
   *
   * @param[in] content byte array for being written.
   * @param[in] size size of byte array.
   *            if size is zero, this function search null termination.
   * @return written size if succeeded(That is equals with len). -1 if failed.
   */
  int write(const Byte* content, unsigned int size = 0);
};

////////////////////////////////////////////////////////////////////////////////
} //namespace practice

#endif
