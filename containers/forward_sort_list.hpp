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

template<typename T> struct forward_sort_list
{
  using value_type = T;
  using size_type = std::size_t;
  class iterator;
  using const_iterator = const iterator;

  // MEMBER FUNCTIONS
  forward_sort_list() = default;
  // cppcheck-suppress noExplicitConstructor ; allowing forward_sort_list A = {1,2,3} and A{1,2,3}
  forward_sort_list(std::initializer_list<T> init) : sz{ 1 }, head{ new forward_node<T>(*init.begin()) }
  {
    for (auto it = init.begin() + 1; it != init.end(); ++it) { insert(*it); }
  }

  forward_sort_list(const forward_sort_list &t_l) : head{ t_l.head } {}

  ~forward_sort_list()
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
  bool find(const T &t_value, forward_node<T> **&t_ptr)
  {
    // for (t_ptr = &head; *t_ptr && t_value > **t_ptr; t_ptr = &static_cast<iterator>((*t_ptr)->next)) { ; }
    for (t_ptr = &head; *t_ptr && t_value > (*t_ptr)->value; t_ptr = &((*t_ptr)->next)) { ; }
    // for (t_ptr = &static_cast<forward_node<T>>(head); *t_ptr && t_value > (*t_ptr)->value; t_ptr = &((*t_ptr)->next))
    // {;} return *t_ptr && (**t_ptr == t_value);
    return *t_ptr && ((*t_ptr)->value == t_value);
  }

  // ITERATORS
  // before_begin // returns an iterator to the element before beginning
  // cbefore_begin
  // iterator begin() { return head; }
  iterator begin() { return static_cast<iterator>(head); }
  iterator begin() const { return static_cast<iterator>(head); }
  [[nodiscard]] decltype(nullptr) end() { return nullptr; }
  [[nodiscard]] decltype(nullptr) end() const { return nullptr; }
  // const_iterator begin() const { return head; }
  // [[nodiscard]] decltype(nullptr) end() const { return nullptr; }
  // const_iterator cbegin() const { return head; }
  // [[nodiscard]] decltype(nullptr) cend() const { return nullptr; }

  // CAPACITY
  size_type size() { return sz; }
  [[nodiscard]] bool empty() const { return ((sz == 0) && !head); }
  size_type max_size() { return std::numeric_limits<size_type>::max(); }

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
  forward_sort_list &operator=(const forward_sort_list t_l)
  {
    sz = t_l.sz;
    head = t_l.head;
    return *this;
  }

private:
  size_type sz{ 0 };
  // iterator head{ nullptr };
  forward_node<T> *head{ nullptr };
};


template<typename T> class forward_sort_list<T>::iterator
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

template<typename T> ostream &operator<<(std::ostream &os, const forward_sort_list<T> &t_list)
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
template<class T> bool fstd::forward_sort_list<T>::insert(const T t_value)
{
  // iterator *ptr;// NOLINT not initialized
  forward_node<T> **ptr;// NOLINT not initialized
  if (find(t_value, ptr)) { return false; }
  forward_node<T> *new_node = new forward_node<T>(t_value, *ptr);
  *ptr = new_node;
  ++sz;
  return true;
}

template<class T> bool fstd::forward_sort_list<T>::remove(const T &t_value)
{
  // iterator *ptr;// NOLINT not initialized
  forward_node<T> **ptr;// NOLINT not initialized
  if (!find(t_value, ptr)) { return false; }
  forward_node<T> *node_to_be_deleted = *ptr;
  *ptr = (*ptr)->next;
  delete node_to_be_deleted;
  --sz;
  return true;
}

#endif// __FORWARD_SORT_LIST_H__
