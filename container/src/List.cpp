#include <iostream>

#include "List.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

List::Elem::Elem(void* elem)
  : elem_(elem)
{}

List::Elem::~Elem() {}

void List::Elem::linkNext(List::Elem* pre, List::Elem* nex) {
  pre->next_ = nex;
  nex->prev_ = pre;
}

////////////////////////////////////////////////////////////////////////////////

List::List()
  : head_(new List::Elem(NULL)),
    size_(0)
{
  head_->prev_ = head_;
  head_->next_ = head_;
}

List::~List() {
  clear();
  delete head_;
}

bool List::add(unsigned int index, void* elem) {
  if (size_ < index) {
    return false;
  }
  Elem* e = elemAt(index);
  Elem* newE = new List::Elem(elem);

  Elem::linkNext(e->prev_, newE);
  Elem::linkNext(newE, e);

  size_++;
  return true;
}

void* List::get(unsigned int index) {
  if (size_ <= index) {
    return NULL;
  }
  return elemAt(index)->elem_;
}

void* List::remove(unsigned int index) {
  if (size_ <= index) {
    return NULL;
  }

  Elem* e = elemAt(index);

  Elem::linkNext(e->prev_, e->next_);
  void* elem = e->elem_;
  delete e;
  size_--;
  return elem;
}

void List::put(void* elem) {
  add(0, elem);
}

void List::pushBack(void* elem) {
  add(size_, elem);
}

void* List::popFront() {
  return remove(0);
}

void List::clear() {
  if (0 == size_) return;
  Elem* e = head_->prev_;
  while (head_ != e) {
    Elem* tmp = e;
    e = e->prev_;
    delete tmp;
  }
  size_ = 0;
  Elem::linkNext(head_, head_);
}

unsigned int List::size() {
  return size_;
}

List::Elem* List::elemAt(unsigned int index) {
  Elem* e = head_;
  if (index < size_ / 2) {
    for (int i = 0; i < index + 1; i++) {
      e = e->next_;
    }
  }
  else {
    for (int i = size_; index < i; i--) {
      e = e->prev_;
    }
  }
  return e;
}

////////////////////////////////////////////////////////////////////////////////
} //namespace practice
