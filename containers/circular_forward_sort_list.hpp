#ifndef __FORWARD_SORT_LIST_H__
#define __FORWARD_SORT_LIST_H__

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
#include "forward_node.hpp"

using namespace std;

namespace fstd {

template<typename T> struct circular_forward_sort_list
{
  using value_type = T;
  // using size_type = std::size_t;
  class iterator;
  using const_iterator = const iterator;

  // MEMBER FUNCTIONS
  circular_forward_sort_list() = default;
  // cppcheck-suppress noExplicitConstructor ; allowing circular_forward_sort_list A = {1,2,3} and A{1,2,3}
  circular_forward_sort_list(std::initializer_list<T> init)
    : head{ new forward_node<T>(*init.begin()) }, sentinel_node{ T{}, head }
  {
    forward_node<T> *last_node{ head };// NOLINT not initialized
    for (auto it = init.begin() + 1; it != init.end(); ++it) {
      T value = *it;
      forward_node<T> **ptr;// NOLINT not initialized
      if (constructor_find(value, ptr)) { continue; }
      // std::cout << "found : " << (*ptr)->value << std::endl;
      forward_node<T> *new_node;// NOLINT not initialized
      new_node = new forward_node<T>(value, *ptr);
      // new_node->next = *ptr;
      if (*ptr == head) { sentinel_node.next = new_node; }
      *ptr = new_node;
      if (new_node->value > last_node->value) { last_node = new_node; }
    }
    last_node->next = &sentinel_node;
    // new_node->next = &sentinel_node;
  }

  circular_forward_sort_list(const circular_forward_sort_list &t_l) : head{ t_l.head }, sentinel_node{ T{}, head } {}

  ~circular_forward_sort_list()
  {
    iterator current_n{ begin() };
    while (current_n != static_cast<iterator>(&sentinel_node)) {
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
  bool constructor_find(const T &t_value, forward_node<T> **&t_ptr)
  {
    for (t_ptr = &head; (*t_ptr) && (t_value > (*t_ptr)->value); t_ptr = &((*t_ptr)->next)) { ; }
    return (*t_ptr) && ((*t_ptr)->value == t_value);
  }
  bool find(const T &t_value, forward_node<T> **&t_ptr)
  {
    // std::cout << "looking for : " << t_value << std::endl;
    for (t_ptr = &head; (*t_ptr != &sentinel_node) && (t_value > (*t_ptr)->value); t_ptr = &((*t_ptr)->next)) { ; }
    // std::cout << (*t_ptr != &sentinel_node) << "&&" << ((*t_ptr)->value == t_value) << std::endl;
    return (*t_ptr != &sentinel_node) && ((*t_ptr)->value == t_value);
  }

  // ITERATORS
  // before_begin // returns an iterator to the element before beginning
  // cbefore_begin
  iterator begin() { return static_cast<iterator>(head); }
  iterator begin() const { return static_cast<iterator>(head); }

  // [[nodiscard]] forward_node* end() { return &sentinel_node; }
  // [[nodiscard]] forward_node* end() const { return &sentinel_node; }

  [[nodiscard]] iterator end() { return static_cast<iterator>(sentinel_node_ptr); }
  [[nodiscard]] iterator end() const { return static_cast<iterator>(sentinel_node_ptr); }

  // const_iterator begin() const { return head; }
  // [[nodiscard]] decltype(nullptr) end() const { return nullptr; }
  // const_iterator cbegin() const { return head; }
  // [[nodiscard]] decltype(nullptr) cend() const { return nullptr; }

  // CAPACITY
  [[nodiscard]] bool empty() const { return !head; }

  // MODIFIERS

  bool insert(const T t_value);
  bool remove(const T &t_value);

  // OPERATIONS
  // merge
  // splice_after
  // remove
  // remove_if
  // reverse
  // unique
  // sort

  // OPERATORS
  circular_forward_sort_list &operator=(const circular_forward_sort_list t_l)
  {
    head = t_l.head;
    return *this;
  }

private:
  // iterator head{ nullptr };
  forward_node<T> *head{ nullptr };
  forward_node<T> sentinel_node{ T(), nullptr };
  forward_node<T> *sentinel_node_ptr{ &sentinel_node };
};


template<typename T> class circular_forward_sort_list<T>::iterator
{
  forward_node<T> *curr;

public:
  iterator(forward_node<T> *node) : curr{ node } {}
  iterator(const iterator &it) : curr{ it.curr } {}

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

  operator bool() const { return curr; }
  operator forward_node<T> *() const { return curr; }
  bool operator==(const iterator &rhs) const { return curr == rhs.curr; }
  bool operator!=(const forward_node<T> *&rhs) const { return curr != rhs->curr; }
  bool operator!=(const iterator &rhs) const { return curr != rhs.curr; }
  bool operator!=(decltype(nullptr) rhs) const { return curr != rhs; }
};

// template<typename T> ostream &operator<<(std::ostream &os, const circular_forward_sort_list<T> &t_list)
// {
//   for (auto it = t_list.begin(); it != t_list.end(); ++it) { os << *it << ", "; }
//   // for (auto &&elem : t_list) { os << elem << ", "; }
//   return os;
// }
template<typename T> ostream &operator<<(std::ostream &os, const circular_forward_sort_list<T> &t_list)
{
  for (auto it = t_list.begin(); it != t_list.end(); ++it) { os << *it << ", "; }
  // for (auto &&elem : t_list) { os << elem << ", "; }
  return os;
}

}// namespace fstd

/****************************************************************************
 * IMPLEMENTATION DETAILS
 ****************************************************************************/

// MODIFIERS
// clear
template<class T> bool fstd::circular_forward_sort_list<T>::insert(const T t_value)
{
  // iterator *ptr;// NOLINT not initialized
  forward_node<T> **ptr;// NOLINT not initialized
  if (find(t_value, ptr)) { return false; }
  // std::cout << "found" << (*ptr)->value << std::endl;
  forward_node<T> *new_node = new forward_node<T>(t_value, *ptr);
  if (*ptr == head) { sentinel_node.next = new_node; }
  *ptr = new_node;
  return true;
}

template<class T> bool fstd::circular_forward_sort_list<T>::remove(const T &t_value)
{
  // iterator *ptr;// NOLINT not initialized
  forward_node<T> **ptr;// NOLINT not initialized
  if (!find(t_value, ptr)) { return false; }
  forward_node<T> *node_to_be_deleted = *ptr;
  *ptr = (*ptr)->next;
  delete node_to_be_deleted;
  return true;
}

#endif// __FORWARD_SORT_LIST_H__
