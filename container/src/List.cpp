#include <iostream>

#include "List.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

List::Element::Element(void* elem)
  : elem_(elem)
{}

List::Element::~Element() {}

void List::Element::linkNext(List::Element* pre, List::Element* nex) {
  pre->next_ = nex;
  nex->prev_ = pre;
}

////////////////////////////////////////////////////////////////////////////////

List::List()
  : head_(new List::Element(NULL)),
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
  Element* e = elemAt(index);
  Element* newE = new List::Element(elem);

  Element::linkNext(e->prev_, newE);
  Element::linkNext(newE, e);

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

  Element* e = elemAt(index);

  Element::linkNext(e->prev_, e->next_);
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
  Element* e = head_->prev_;
  while (head_ != e) {
    Element* tmp = e;
    e = e->prev_;
    delete tmp;
  }
  size_ = 0;
  Element::linkNext(head_, head_);
}

unsigned int List::size() {
  return size_;
}

List::Iterator List::begin() {
  List::Iterator tmp(head_->next_);
  return tmp;
}

List::Iterator List::end() {
  List::Iterator tmp(head_->prev_);
  return tmp;
}

List::Element* List::elemAt(unsigned int index) {
  Element* e = head_;
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

List::Iterator::Iterator(Element* elem)
  : elem_(elem)
{}

List::Iterator::~Iterator() {}

List::Iterator::Iterator(const Iterator& itr)
  : elem_(itr.elem_)
{}

List::Iterator& List::Iterator::operator=(const Iterator& itr) {
  elem_ = itr.elem_;
  return *this;
}

void* List::Iterator::operator*() {
  return elem_->elem_;
}

List::Iterator List::Iterator::operator++(int i) {
  List::Iterator itr = *this;
  elem_ = elem_->next_;
  return itr;
}

bool List::Iterator::operator==(const Iterator& itr) {
  return (itr.elem_ == elem_);
}

bool List::Iterator::operator!=(const Iterator& itr) {
  return (itr.elem_ != elem_);
}

////////////////////////////////////////////////////////////////////////////////
} //namespace practice
