#ifndef _FILE_H_
#define _FILE_H_

#include <fstream>

namespace practice {
////////////////////////////////////////////////////////////////////////////////

typedef char Byte;

#define BUFFER_MAX 4096

/**
 * File class
 */
class File {
public:
  /**
   * File Reader class.
   */
  class Reader {
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
    Reader(const char* path);
    ~Reader();

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

  /**
   * File Writer class.
   */
  class Writer {
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
    Writer(const char* path);
    ~Writer();

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
};

////////////////////////////////////////////////////////////////////////////////
} //namespace practice

#endif
