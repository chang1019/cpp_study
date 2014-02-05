#ifndef _LIST_H_
#define _LIST_H_

namespace practice {
////////////////////////////////////////////////////////////////////////////////

/**
 * Bidirectional Linked List class.
 */
class List {
private:
  class Elem {
    friend class List;

  private:
    Elem* prev_;
    Elem* next_;
    void* elem_;

  public:
    Elem(void* elem);
    ~Elem();

  public:
    static void linkNext(Elem* pre, Elem* nex);
  };

private:
  Elem* head_;
  unsigned int size_;

public:
  List();
  ~List();

private:
  List(const List&);
  List& operator=(const List&);

public:
  bool add(unsigned int index, void* elem);
  void* get(unsigned int index);
  void* remove(unsigned int index);
  void put(void* elem);
  void pushBack(void* elem);
  void* popFront();
  void clear();

  unsigned int size();

private:
  Elem* elemAt(unsigned int index);
};

////////////////////////////////////////////////////////////////////////////////
} //namespace practice

#endif
