#ifndef __FORWARD_LIST_H__
#define __FORWARD_LIST_H__

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
#include <limits>
// fake library
#include "node/forward_node.hpp"

using namespace std;

namespace fstd {

template<typename T> struct forward_list
{
  using value_type = T;
  using size_type = std::size_t;
  class iterator;
  using const_iterator = const iterator;

  // MEMBER FUNCTIONS
  forward_list() = default;
  forward_list(forward_list &&) = default;// NOLINT noexcept //copy constructor
  // forward_list(forward_list &&) noexcept;
  // cppcheck-suppress noExplicitConstructor ; allowing forward_list A = {1,2,3} and A{1,2,3}
  forward_list(std::initializer_list<T> init) : sz{ init.size() }, head{ new forward_node<T>(*init.begin()) }
  {
    iterator nav{ head };
    for (auto i = init.begin() + 1; i != init.end(); ++i) {
      nav->next = new forward_node<T>(*i);
      ++nav;
    }
    // cppcheck-suppress memleak ; i know what am doing... i know
  }

  forward_list(const forward_list &t_l) : head{ t_l.head } {}

  ~forward_list()
  {
    iterator current_n{ begin() };
    while (current_n != nullptr) {
      iterator next_n{ current_n->next };
      delete current_n;
      current_n = next_n;
    }
  }
  // operator=
  // assign
  // get_allocator

  //  ELEMENT ACCESS
  T front() const { return head->value; }

  // ITERATORS
  // before_begin // returns an iterator to the element before beginning
  // cbefore_begin
  iterator begin() { return head; }
  iterator end() { return iterator{ nullptr }; }
  const_iterator begin() const { return head; }
  const_iterator end() const { return iterator{ nullptr }; }
  const_iterator cbegin() const { return head; }
  const_iterator cend() const { return const_iterator{ nullptr }; }

  // CAPACITY
  size_type size() { return sz; }
  [[nodiscard]] bool empty() const { return ((sz == 0) && !head); }
  size_type max_size() { return std::numeric_limits<size_type>::max(); }

  // MODIFIERS
  // clear
  // insert_after
  // emplace_after
  // erase_after
  void push_front(const T t_value);
  void pop_front();
  // void resize(const size_type &count, T value = T{});// DefaultInsertable
  // void resize(const size_type &count, const T &value);// CopyInsertable
  // Type requirements
  // - T must meet the requirements of DefaultInsertable in order to use overload (1).
  // - T must meet the requirements of CopyInsertable in order to use overload (2).
  void resize(const size_type &new_size);// CopyInsertable
  // void swap(forward_list &);

  // OPERATIONS
  // merge
  // splice_after
  // remove
  // remove_if
  // reverse
  // unique
  // sort

  // OPERATORS
  forward_list &operator=(const forward_list t_l)
  {
    sz = t_l.sz;
    head = t_l.head;
    return *this;
  }
  forward_list &operator=(forward_list &&) = default;// NOLINT noexcept


private:
  size_type sz{ 0 };
  iterator head{ nullptr };
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


template<typename T> ostream &operator<<(std::ostream &os, const forward_list<T> &t_list)
{
  // for (auto it = t_list.begin(); it != t_list.end(); ++it) { os << *it << ", "; }
  for (auto &&elem : t_list) { os << elem << ", "; }
  return os;
}

}// namespace fstd

/****************************************************************************
 * IMPLEMENTATION DETAILS
 ****************************************************************************/

template<typename T> class fstd::forward_list<T>::iterator
{
  forward_node<T> *curr;

public:
  iterator(forward_node<T> *p) : curr{ p } {}
  iterator(const iterator &it) : curr{ it.curr } {}
  iterator(iterator &&) = default;// NOLINT noexcept //copy constructor
  ~iterator() = default;

  iterator &operator++()
  {
    curr = curr->next;
    return *this;
  }// forward
  T &operator*() const { return curr->value; }// dereference
  forward_node<T> *operator->() const { return curr; }// member of pointer
  iterator &operator=(const iterator &it)
  {
    curr = it.curr;
    return *this;
  }
  iterator operator=(forward_node<T> *const &it)
  {
    curr = it;
    return *this;
  }
  iterator &operator=(iterator &&) = default;// NOLINT noexcept

  operator bool() const { return curr; }
  operator forward_node<T> *() const { return curr; }
  bool operator==(const iterator &rhs) const { return curr == rhs.curr; }
  bool operator!=(const forward_node<T> *&rhs) const { return curr != rhs->curr; }
  bool operator!=(const iterator &rhs) const { return curr != rhs.curr; }
  bool operator!=(decltype(nullptr) rhs) const { return curr != rhs; }
};


// CAPACITY
// max_size //returns the maximum possible number of elements

// MODIFIERS
// clear
// insert
// emplace
// erase


template<class T> void fstd::forward_list<T>::push_front(const T t_value)
{
  forward_node<T> *new_node{ new forward_node<T>(t_value) };
  new_node->next = head;
  head = new_node;
  ++sz;
}
// emplace front

template<class T> void fstd::forward_list<T>::pop_front()
{
  iterator current{ head };
  ++head;
  delete current;
  --sz;
}


// void resize(const size_type &count, T value = T{});// DefaultInsertable
// void resize(const size_type &count, const T &value);// CopyInsertable
// Type requirements
// - T must meet the requirements of DefaultInsertable in order to use overload (1).
// - T must meet the requirements of CopyInsertable in order to use overload (2).
template<class T> void fstd::forward_list<T>::resize(const size_type &new_size)// CopyInsertable  // needs testing
{
  const auto delete_nodes = [&]() {
    auto nav_head{ begin() };
    for (size_t i = 0; i < new_size - 1; i++, ++nav_head) { ; }

    auto nav_tail{ nav_head };
    ++nav_head;
    nav_tail->next = nullptr;
    while (nav_head) {
      nav_tail = nav_head;
      ++nav_head;
      delete nav_tail;
    }
  };
  const auto create_nodes = [&]() {
    const int new_nodes_size{ new_size - sz };// value range [1, numeric_limits<int>::max() )
    forward_node<T> *new_nodes = new forward_node<T>[new_nodes_size];

    auto nav{ begin() };
    int current = 0;
    const auto until_sz = [&]() {
      std::cout << "until_sz" << std::endl;
      for (; current < sz - 1; ++current, ++nav) { new_nodes[current].next = &(new_nodes[current + 1]); }
      nav->next = &(new_nodes[0]);
      for (; current < (new_nodes_size - 1); ++current) { new_nodes[current].next = &(new_nodes[current + 1]); }
    };
    const auto until_new_nodes_size = [&]() {
      std::cout << "until_n_n_sz" << std::endl;
      for (; current < new_nodes_size - 1; ++current, ++nav) { new_nodes[current].next = &(new_nodes[current + 1]); }
      while (nav->next) { ++nav; }
      nav->next = new_nodes;
    };

    (new_nodes_size > sz) ? until_sz() : until_new_nodes_size();
    // delete[] new_nodes;
  };

  if (new_size > sz) {
    create_nodes();
    sz = new_size;
  } else if (sz > new_size) {
    delete_nodes();
    sz = new_size;
  }
}

#endif// __FORWARD_LIST_H__
