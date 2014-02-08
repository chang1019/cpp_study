#ifndef _LIST_H_
#define _LIST_H_

namespace practice {
////////////////////////////////////////////////////////////////////////////////

/**
 * Bidirectional Linked List class.
 */
class List {
public:
class Iterator;

private:
  class Element {
    friend class Iterator;
    friend class List;

  private:
    Element* prev_;
    Element* next_;
    void* elem_;

  public:
    Element(void* elem);
    ~Element();

  public:
    static void linkNext(Element* pre, Element* nex);
  };

public:
  class Iterator {
  private:
    Element* elem_;

  public:
    Iterator(Element* elem);
    ~Iterator();
    Iterator(const Iterator& itr);
    Iterator& operator=(const Iterator& itr);

    void* operator*();
    Iterator operator++(int i);

    bool operator==(const Iterator& itr);
    bool operator!=(const Iterator& itr);
  };

private:
  Element* head_;
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

  Iterator begin();
  Iterator end();

private:
  Element* elemAt(unsigned int index);
};

////////////////////////////////////////////////////////////////////////////////
} //namespace practice

#endif
