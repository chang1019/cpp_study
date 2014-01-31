#include <iostream>
#include <stdio.h>

#include "Thread.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

Thread::RunWrapper::RunWrapper()
  : runnable_(NULL),
    arg_(NULL)
{}

void Thread::RunWrapper::init(Runnable* runnable, void* arg) {
  runnable_ = runnable;
  arg_ = arg;
}

////////////////////////////////////////////////////////////////////////////////

Thread::Thread()
  : thread_(),
    wrapper_(),
    isStarted_(false)
{}

Thread::~Thread() {}

void Thread::start(Runnable& runnable, void* arg) {
  if (isStarted_) {
    printf("[start] fail to start thread. thread has been already started. \n");
    return;
  }
  wrapper_.init(&runnable, arg);
  pthread_create(&thread_, NULL, runWrapper, &wrapper_);
  isStarted_ = true;
}

void Thread::join() {
  if (!isStarted_) {
    printf("[join] fail to join thread. thread has not been started yet.");
    return;
  }
  pthread_join(thread_, NULL);
}

void* Thread::runWrapper(void* arg) {
  Thread::RunWrapper* wrapper = static_cast<Thread::RunWrapper*>(arg);
  return wrapper->runnable_->run(wrapper->arg_);
}

////////////////////////////////////////////////////////////////////////////////
} //namespace practice
