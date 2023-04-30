// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <iostream>
#include <string>

template <typename T>
class TPQueue {
 public:
  TPQueue() : head(nullptr), tail(nullptr) { }
  ~TPQueue();
  void push(const T&);
  T pop();
  void print();

 private:
  struct Item {
    T data;
    Item* nxt;
    Item* prv;
  };
  Item* head;
  Item* tail;
  TPQueue::Item* create(const T&);
};

template <typename T>
TPQueue<T>::~TPQueue() {
  while (head) {
    pop();
  }
}

template <typename T>
void TPQueue<T>::print() {
  Item* tmp = head;
  while (tmp) {
    std::cout << tmp->data << '\t';
    tmp = tmp->nxt;
  }
  std::cout << std::endl;
}

template <typename T>
typename TPQueue<T>::Item* TPQueue<T>::create(const T& data) {
  Item* item = new Item;
  item->data = data;
  item->nxt = nullptr;
  item->prv = nullptr;
  return item;
}

template <typename T>
T TPQueue<T>::pop() {
  if (!head) {
    throw std::string("Empty!");
  } else {
    Item* tmp = head->nxt;
    T data = head->data;
    delete head;
    head = tmp;
    return data;
  }
}

template <typename T>
void TPQueue<T>::push(const T& val) {
  if (head == nullptr) {
    head = create(val);
    tail = head;
  } else if (tail->data.prior >= val.prior) {
    if (tail->data.ch == val.ch) {
      tail->data = val;
    } else {
      tail->nxt = create(val);
      tail->nxt->prv = tail;
      tail = tail->nxt;
    }
  } else if (head == tail) {
    tail->prv = create(val);
    head = tail->prv;
    head->nxt = tail;
  } else {
    Item* tmp = tail;
    while (tmp != head && tmp->data.prior < val.prior) {
      tmp = tmp->prv;
    }
    if (tmp->data.prior > val.prior) {
      Item* cell = new Item;
      cell->nxt = tmp->nxt;
      cell->prv = tmp;
      cell->data = val;
      tmp->nxt->prv = cell;
      tmp->nxt = cell;
    }
    if (tmp == head && tmp->data.prior < val.prior) {
      head->prv = create(val);
      head = head->prv;
      head->nxt = tmp;
    }
  }
}

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
