#ifndef _MUTEX_H_
#define _MUTEX_H_

#include <pthread.h>

namespace practice {
////////////////////////////////////////////////////////////////////////////////

/**
 * Mutex class.
 */
class Mutex {
  friend class Lock;

public:
  class Lock {
  private:
    Mutex* mutex_;

  public:
    Lock(Mutex& mutex);
    ~Lock();

  private:
    Lock(const Lock&);
    Lock& operator=(const Lock&);
  };

private:
  pthread_mutex_t mutex_;

public:
  Mutex();
  ~Mutex();

private:
  Mutex(const Mutex&);
  Mutex& operator=(const Mutex&);

private:
  void lock();
  void unlock();
};

////////////////////////////////////////////////////////////////////////////////
} //namespace proctice

#endif
