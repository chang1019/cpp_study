#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>

namespace practice {
////////////////////////////////////////////////////////////////////////////////

/**
 * Runnable Interface.
 */
class Runnable {
public:
  virtual void* run(void* arg) = 0;
};

////////////////////////////////////////////////////////////////////////////////

/**
 * Thread class.
 */
class Thread {
private:
  class RunWrapper {
    friend class Thread;

  private:
    Runnable* runnable_;
    void* arg_;

  public:
    RunWrapper();

    void init(Runnable* runnable, void* arg);
  };

private:
  pthread_t thread_;
  RunWrapper wrapper_;
  bool isStarted_;

public:
  Thread();
  ~Thread();

private:
  Thread(const Thread&);
  Thread& operator=(const Thread&);

public:
  void start(Runnable& runnable, void* arg);
  void join();

private:
  static void* runWrapper(void* arg);
};

////////////////////////////////////////////////////////////////////////////////
} //namespace proctice

#endif
