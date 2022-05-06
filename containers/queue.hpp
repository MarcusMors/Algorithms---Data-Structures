// Copyright (C) 2022 José Enrique Vilca Campana
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// Copyright (C) 2022 José Enrique Vilca Campana
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// standard library
#include <initializer_list>
#include <iostream>
// fake library
#include "node.hpp"

using namespace std;

namespace fstd {
using fstd::node;

template<typename T> struct queue
{
  using value_type = T;
  using size_type = std::size_t;
  class iterator;
  using const_iterator = const iterator;

  queue() = default;
  // cppcheck-suppress noExplicitConstructor ; allowing queue A = {1,2,3} and A{1,2,3}
  queue(std::initializer_list<T> init) : sz{ init.size() }, head{ new node<T>(*init.begin()) }
  {
    iterator nav{ head };
    for (auto i = init.begin() + 1; i != init.end(); ++i) {
      nav->next = new node<T>(*i);
      nav->next->prev = nav;
      ++nav;
    }
    tail = nav;
  }
  queue(const queue &t_q) : head{ t_q.head }, tail{ t_q.tail } {}// copy constructor


  ~queue()
  {
    iterator current_n{ begin() };
    while (current_n) {
      iterator next_n{ current_n->next };
      delete current_n;
      current_n = next_n;
    }
  }

  //  ELEMENT ACCESS
  T front() const { return head->value; }
  T back() const { return tail->value; }

  // ITERATORS
  iterator begin() { return head; }
  iterator end() { return iterator{ nullptr }; }
  const_iterator begin() const { return head; }// NOLINT
  const_iterator end() const { return iterator{ nullptr }; }// NOLINT
  const_iterator cbegin() const { return head; }// NOLINT
  const_iterator cend() const { return const_iterator{ nullptr }; }// NOLINT
  iterator rbegin() { return tail; }
  iterator rend() { return iterator{ nullptr }; }
  const_iterator crbegin() const { return tail; }// NOLINT
  const_iterator crend() const { return const_iterator{ nullptr }; }// NOLINT

  // CAPACITY
  [[nodiscard]] bool empty() const { return (sz == 0 && !tail && !head); }
  size_type size() { return sz; }

  // MODIFIERS
  void push(const T t_value);
  // emplace
  void pop();
  // void swap(queue &);

  // OPERATIONS
  // merge
  // splice
  // remove
  // remove_if
  // reverse
  // unique
  // sort

  // OPERATORS

  T &operator[](const size_type &t_i)
  {
    iterator nav{ head };
    for (size_type i = 0; i < t_i; ++i) { nav = nav->next; }
    return nav->value;
  }
  const T &operator[](const size_type &t_i) const
  {
    iterator nav{ head };
    for (size_type i = 0; i < t_i; ++i) { nav = nav->next; }
    return nav->value;
  }
  queue &operator=(const queue rhs)
  {
    sz = rhs.sz;
    head = rhs.head;
    tail = rhs.tail;
    return *this;
  }

private:
  size_type sz{ 0 };
  iterator head{ nullptr };
  iterator tail{ nullptr };
};

//  Non-member functions
// operator ==
// operator !=
// operator <
// operator <=
// operator >
// operator >=
// swap
// erase
// erase_if


template<typename T> class queue<T>::iterator
{
  node<T> *curr;

public:
  explicit iterator(node<T> *node) : curr{ node } {}
  iterator(const iterator &t_it) : curr{ t_it.curr } {}
  ~iterator() = default;

  iterator &operator++()
  {
    curr = curr->next;
    return *this;
  }// forward
  iterator &operator--()
  {
    curr = curr->prev;
    return *this;
  }// backward

  iterator operator+(int rhs)
  {
    while (rhs > 0) {
      ++(*this);
      --rhs;
    }
  }
  iterator operator-(int rhs)
  {
    while (rhs < 0) {
      --(*this);
      rhs++;
    }
  }

  T &operator*() const { return curr->value; }// dereference
  node<T> *operator->() const { return curr; }// member of pointer
  iterator &operator=(const iterator &it)
  {
    curr = it.curr;
    return *this;
  }
  iterator operator=(node<T> *const &it)
  {
    curr = it;
    return *this;
  }

  operator bool() const { return curr; }
  operator node<T> *() const { return curr; }
  bool operator==(const iterator &rhs) const { return curr == rhs.curr; }
  bool operator!=(const iterator &rhs) const { return curr != rhs.curr; }
};

template<typename T> ostream &operator<<(std::ostream &os, const queue<T> &t_queue)
{
  for (auto &&elem : t_queue) { os << elem << ", "; }
  return os;
}
//
//
// template<class T> ostream &operator<<(std::ostream &os, const node<T> &t_node) { return os << t_node.value; }
// template<class T> ostream &operator<<(std::ostream &os, const node<T> *t_node) { return os << t_node->value; }


}// namespace fstd

/****************************************************************************
 * IMPLEMENTATION DETAILS
 ****************************************************************************/


// CAPACITY
// max_size //returns the maximum possible number of elements

// MODIFIERS
// clear
// insert
// emplace
// erase
template<class T> void fstd::queue<T>::push(const T t_value)
{
  iterator temp{ new node<T>(t_value) };
  if (empty()) {
    head = tail = temp;
  } else {
    tail->next = temp;
    temp->prev = tail;
    tail = temp;
    ++sz;
  }
}

// emplace

template<class T> void fstd::queue<T>::pop()
{
  head = head->next;
  delete head->prev;
  --sz;
}


// template<class T> void fstd::queue<T>::swap(queue &t_queue)
// {
//   queue temp{ *this };
//   *this = t_queue;
//   t_queue = temp;
// }
// void swap(iterator &a, iterator &b) const
// {
//   iterator temp{ a };
//   a->prev = b->prev;
//   a->next = b->next;
//   temp->next->prev = b;
//   temp->prev->next = b;
//   b->prev = temp->prev;
//   b->next = temp->next;
// }
