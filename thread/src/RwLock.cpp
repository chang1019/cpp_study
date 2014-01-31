#include <pthread.h>

#include "RwLock.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

RwLock::Read::Read(RwLock& rwlock)
  : rwlock_(&rwlock)
{
  rwlock_->readLock();
}

RwLock::Read::~Read() {
  rwlock_->unlock();
}

////////////////////////////////////////////////////////////////////////////////

RwLock::Write::Write(RwLock& rwlock)
  : rwlock_(&rwlock)
{
  rwlock_->writeLock();
}

RwLock::Write::~Write() {
  rwlock_->unlock();
}

////////////////////////////////////////////////////////////////////////////////

RwLock::RwLock()
  : rwlock_()
{
  pthread_rwlock_init(&rwlock_, NULL);
}

RwLock::~RwLock() {
  pthread_rwlock_destroy(&rwlock_);
}

void RwLock::readLock() {
  pthread_rwlock_rdlock(&rwlock_);
}

void RwLock::writeLock() {
  pthread_rwlock_wrlock(&rwlock_);
}

void RwLock::unlock() {
  pthread_rwlock_unlock(&rwlock_);
}

////////////////////////////////////////////////////////////////////////////////
} // namespace practice
