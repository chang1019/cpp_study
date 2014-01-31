#include <stdio.h>

#include "Mutex.h"
#include "Thread.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

/**
 * Runnable Implementation.
 */
class Executor : public Runnable {
private:
  Mutex mutex_;
  int count_;

public:
  Executor() : count_(0) {}

  ~Executor() {}

  //////////////////////////////////////////////////////////////////////////////
  // Implementation of Runnable.
  void* run(void* arg) {
    {
      Mutex::Lock lock(mutex_);
      printf("hello pthread! (count = %d)\n", count_++);
    }
    return NULL;
  }
};

////////////////////////////////////////////////////////////////////////////////
} //namespace practice

using namespace practice;

int main(int argc, char** argv) {
  Executor executor;
  Thread threads[10];

  int size = sizeof(threads) / sizeof(Thread);
  for (int i = 0; i < size; i++) {
    threads[i].start(executor, NULL);
  }

  for (int i = 0; i < size; i++) {
    threads[i].join();
  }
  return 0;
}
