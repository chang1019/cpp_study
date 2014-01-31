#ifndef _RWLOCK_H_
#define _RWLOCK_H_

#include <pthread.h>

namespace practice {
////////////////////////////////////////////////////////////////////////////////

/**
 * Read/Write Lock class.
 */
class RwLock {
  friend class Read;
  friend class Write;

public:
  class Read {
  private:
    RwLock* rwlock_;

  public:
    Read(RwLock& rwlock);
    ~Read();

  private:
    Read(const Read&);
    Read& operator=(const Read&);
  };

  class Write {
  private:
    RwLock* rwlock_;

  public:
    Write(RwLock& rwlock);
    ~Write();

  private:
    Write(const Write&);
    Write& operator=(const Write&);
  };

private:
  pthread_rwlock_t rwlock_;

public:
  RwLock();
  ~RwLock();

private:
  RwLock(const RwLock&);
  RwLock& operator=(const RwLock&);

private:
  void readLock();
  void writeLock();
  void unlock();
};

////////////////////////////////////////////////////////////////////////////////
} // namespace practice

#endif
