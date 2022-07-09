#ifndef __MINIDEQUE_H__
#define __MINIDEQUE_H__

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

// fstd
#include "./array_node.hpp"
// std
#include <initializer_list>
#include <iostream>
#include <limits>

namespace fstd {

template<typename T> struct minideque
{
  using value_type = T;
  using size_type = std::size_t;
  class iterator;
  using const_iterator = const iterator;

  // MEMBER FUNCTIONS
  minideque() = default;
  // cppcheck-suppress noExplicitConstructor ; allowing minideque A = {1,2,3} and A{1,2,3}
  minideque(std::initializer_list<T> init) : sz{ 1 }, head{ new array_node<T>(*init.begin()) }
  {
    for (auto it = init.begin() + 1; it != init.end(); ++it) { insert(*it); }
  }

  minideque(const minideque &t_l) : head{ t_l.head } {}

  ~minideque()
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
  bool find(const T &t_value, array_node<T> **&t_ptr, size_type &t_iterations)
  {
    // initialize values
    t_ptr = &head;
    t_iterations = 0;

    auto advance_ptr = [&]() { t_ptr = &((*t_ptr)->next); };
    bool flag_cero_repetition{ false };
    size_type pos;
    while (*t_ptr && t_value > (*t_ptr)->values[pos]) {
      pos = t_iterations % 3;
      if (pos == 0) {
        if (flag_cero_repetition) {
          flag_cero_repetition = false;
          advance_ptr();
        }
        flag_cero_repetition = true;
      }

      ++t_iterations;
    }
    return *t_ptr && ((*t_ptr)->values[pos] == t_value);
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
  minideque &operator=(const minideque t_l)
  {
    sz = t_l.sz;
    head = t_l.head;
    return *this;
  }

private:
  size_type sz{ 0 };
  // iterator head{ nullptr };
  array_node<T> *head{ nullptr };
};


template<typename T> class minideque<T>::iterator
{
  array_node<T> *curr;

public:
  iterator(array_node<T> *node) : curr{ node } {}
  iterator(const iterator &it) : curr{ it.curr } {}

  iterator &operator++()
  {
    curr = curr->next;
    return *this;
  }// forward
  T &operator*() const { return curr->value; }// dereference
  array_node<T> *operator->() const { return curr; }// member of pointer
  iterator &operator=(const iterator &it)
  {
    curr = it.curr;
    return *this;
  }
  iterator operator=(array_node<T> *const &it)
  {
    curr = it;
    return *this;
  }

  operator bool() const { return curr; }
  operator array_node<T> *() const { return curr; }
  bool operator==(const iterator &rhs) const { return curr == rhs.curr; }
  bool operator!=(const array_node<T> *&rhs) const { return curr != rhs->curr; }
  bool operator!=(const iterator &rhs) const { return curr != rhs.curr; }
  bool operator!=(decltype(nullptr) rhs) const { return curr != rhs; }
};

template<typename T> std::ostream &operator<<(std::ostream &os, const minideque<T> &t_list)
{
  int cont{ 0 };
  std::cout << "Head->";
  for (array_node<T> *it = t_list.begin(); it; it = it->next) {
    for (int i = 0; i < 3 && cont < t_list.size(); i++, cont++) { std::cout << it->valor[i] << "->"; }
  }
  std::cout << "NULL" << std::endl;
  return os;
}

}// namespace fstd

/****************************************************************************
 * IMPLEMENTATION DETAILS
 ****************************************************************************/

// MODIFIERS
// clear
template<class T> bool fstd::minideque<T>::insert(const T t_value)
{
  // iterator *ptr;// NOLINT not initialized
  array_node<T> **ptr;// NOLINT not initialized
  size_type iterations;// NOLINT not initialized
  if (find(t_value, ptr, iterations)) { return false; }
  // final
  // if (iterations == sz) or ;

  auto advance_ptr = [&]() { ptr = &((*ptr)->next); };
  // for (; (*ptr)->next != nullptr; advance_ptr()) {}

  if (*ptr == nullptr) {
    // not found, it should be at the tail or it's empty
    array_node<T> *new_node = new array_node<T>();
    *ptr = new_node;
    new_node->values[0] = t_value;
  } else if (true) {// it's in the middle
    // shift right;
    // arr_node<T> *nav;
    T current_value{ t_value };
    T prev_value;
    //---------------------
    while (*ptr) {
      const size_type pos{ iterations % 3 };
      T *current{ &((*ptr)->values[pos]) };
      if (iterations == sz) {

      } else {
        prev_value = *current;
        *current = current_value;
        // then, ++pos and prev_value = curr->values[pos];
        // current_value = ;
      }

      ++iterations;
      advance_ptr();
    }
  }


  ++sz;
  return true;
}

template<class T> bool fstd::minideque<T>::remove(const T &t_value)
{
  // iterator *ptr;// NOLINT not initialized
  array_node<T> **ptr;// NOLINT not initialized
  if (!find(t_value, ptr)) { return false; }
  array_node<T> *node_to_be_deleted = *ptr;
  *ptr = (*ptr)->next;
  delete node_to_be_deleted;
  --sz;
  return true;
}

#endif// __MINIDEQUE_H__
