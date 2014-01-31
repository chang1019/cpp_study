#include <pthread.h>

#include "Mutex.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

Mutex::Lock::Lock(Mutex& mutex)
  : mutex_(&mutex)
{
  mutex_->lock();
}

Mutex::Lock::~Lock() {
  mutex_->unlock();
}

////////////////////////////////////////////////////////////////////////////////

Mutex::Mutex() {
  pthread_mutex_init(&mutex_, NULL);
}

Mutex::~Mutex() {
  pthread_mutex_destroy(&mutex_);
}

void Mutex::lock() {
  pthread_mutex_lock(&mutex_);
}

void Mutex::unlock() {
  pthread_mutex_unlock(&mutex_);
}

////////////////////////////////////////////////////////////////////////////////
} // namespace practice
