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

template<typename T> struct deque
{
  using value_type = T;
  using size_type = std::size_t;
  class iterator;
  using const_iterator = const iterator;

  deque() = default;
  explicit deque(std::initializer_list<T> init) : sz{ init.size() }, head{ new node<T>(*init.begin()) }
  {
    iterator nav{ head };
    for (auto i = init.begin() + 1; i != init.end(); ++i) {
      nav->next = new node<T>(*i);
      nav->next->prev = nav;
      ++nav;
    }
    tail = nav;
  }
  deque(const deque &l) : head{ l.head }, tail{ l.tail } {}


  ~deque()
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
  const_iterator begin() const { return head; }
  const_iterator end() const { return iterator{ nullptr }; }
  const_iterator cbegin() const { return head; }
  const_iterator cend() const { return const_iterator{ nullptr }; }
  iterator rbegin() { return tail; }
  iterator rend() { return iterator{ nullptr }; }
  const_iterator crbegin() const { return tail; }
  const_iterator crend() const { return const_iterator{ nullptr }; }

  // CAPACITY
  size_type size() { return sz; }
  bool empty() const { return (sz == 0 && !tail && !head); }
  // max_size //returns the maximum possible number of elements

  // MODIFIERS
  // clear
  // insert
  // emplace
  // erase
  void push_back(const T);
  // emplace back
  void pop_back();
  void push_front(const T);
  // emplace front
  void pop_front();
  // void resize(const size_type &count, T value = T{});// DefaultInsertable
  // void resize(const size_type &count, const T &value);// CopyInsertable
  // Type requirements
  // - T must meet the requirements of DefaultInsertable in order to use overload (1).
  // - T must meet the requirements of CopyInsertable in order to use overload (2).
  void resize(const size_type &);// CopyInsertable  // needs testing
  void swap(deque &);

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
  deque &operator=(const deque lhs)
  {
    sz = lhs.sz;
    head = lhs.head;
    tail = lhs.tail;
    return *this;
  }

private:
  const size_type default_primary_array_sz{ 8 };
  const size_type default_derived_array_sz{ 8 };
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


template<typename T> class deque<T>::iterator
{
  node<T> *curr;

public:
  explicit iterator(node<T> *p) : curr{ p } {}
  iterator(const iterator &it) : curr{ it.curr } {}

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

template<typename T> ostream &operator<<(std::ostream &os, const deque<T> &t_deque)
{
  for (auto &&elem : t_deque) { os << elem << ", "; }
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
template<class T> void fstd::deque<T>::push_back(const T t_value)
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


template<class T> void fstd::deque<T>::pop_back()
{
  const iterator current_n{ tail };
  tail = tail->prev;
  tail->next = nullptr;
  delete current_n;
  --sz;
}

template<class T> void fstd::deque<T>::push_front(const T t_value)
{
  node<T> *temp{ new node<T>(t_value) };
  temp->next = head;
  head->prev = temp;
  head = temp;
  ++sz;
}
// emplace front

template<class T> void fstd::deque<T>::pop_front()
{
  head = head->next;
  delete head->prev;
  --sz;
}


// void resize(const size_type &count, T value = T{});// DefaultInsertable
// void resize(const size_type &count, const T &value);// CopyInsertable
// Type requirements
// - T must meet the requirements of DefaultInsertable in order to use overload (1).
// - T must meet the requirements of CopyInsertable in order to use overload (2).
template<class T> void fstd::deque<T>::resize(const size_type &count)// CopyInsertable  // needs testing
{
  // static_assert(count > 0);
  const auto delete_nodes = [&]() {
    iterator current_n{ tail };
    while (sz > count) {
      iterator prev_n{ current_n->prev };
      delete current_n;
      current_n = prev_n;
      --sz;
    }
    tail = current_n;
  };
  const auto create_nodes = [&]() {
    while (sz < count) {
      tail->next = new node<T>();
      tail->next->prev = tail;
      ++tail;
      ++sz;
    }
  };

  (count < sz) ? delete_nodes() : create_nodes();
}
template<class T> void fstd::deque<T>::swap(deque &t_deque)
{
  deque temp{ *this };
  *this = t_deque;
  t_deque = temp;
}
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
