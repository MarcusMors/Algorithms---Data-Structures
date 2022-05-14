#ifndef __CIRCULAR_FORWARD_SORT_LIST_H__
#define __CIRCULAR_FORWARD_SORT_LIST_H__

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
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <limits>
// fake library
#include "forward_node.hpp"

using namespace std;

namespace fstd {
template<class T> using node = forward_node<T>;

template<class T> struct ascendant
{
  bool operator()(T lhs, T rhs) { return lhs > rhs; }
};


template<typename T, class O> struct circular_forward_sort_list
{
  using value_type = T;
  using size_type = std::size_t;
  class iterator;
  using const_iterator = const iterator;

  circular_forward_sort_list() = default;

  // cppcheck-suppress noExplicitConstructor ; allowing circular_forward_sort_list A = {1,2,3} and A{1,2,3}
  circular_forward_sort_list(std::initializer_list<T> init) : sz{ init.size() }
  {
    // is it sorted?
    std::sort(init.begin(), init.end());
    head = new node<T>(*init.begin());// NOLINT
    iterator nav{ head };
    for (auto i = init.begin() + 1; i != init.end(); (++i, ++nav)) { nav->next = new node<T>(*i); }// NOLINT
    nav->next = static_cast<node<T> *>(head);
    // cppcheck-suppress memleak ; i know what am doing... i know
  }

  circular_forward_sort_list(const circular_forward_sort_list &scfl) : head{ scfl.head } {}

  ~circular_forward_sort_list()
  {
    iterator current_n{ begin() };
    // first case
    // do first case
    while (current_n != head) {
      iterator next_n{ current_n->next };
      delete current_n;// NOLINT
      current_n = next_n;
    }
  }

  //  ELEMENT ACCESS
  T front() const { return *head; }
  T back() const { return operator[](sz); }

  // ITERATORS
  iterator begin() { return head; }
  iterator end() { return head; }

  // CAPACITY
  size_type size() { return sz; }
  [[nodiscard]] bool empty() const { return (!head && sz == 0); }
  size_type max_size() { return std::numeric_limits<size_type>::max(); }

  // MODIFIERS
  // clear
  // insert
  // emplace
  // erase
  bool push(const T t_value = T{});
  // emplace back
  // void pop_back();
  // void pop_front();
  void resize(const size_type &new_size);// CopyInsertable
  // void swap(circular_forward_sort_list &);

  // OPERATIONS
  // merge
  // splice
  bool remove(T t_value)
  {
    iterator *current_ptr;
    if (!Find(t_value, current_ptr)) { return false; }

    iterator temp{ *current_ptr };
    *current_ptr = temp->next;
    delete temp;// NOLINT
    return true;
  }
  // remove_if
  // reverse
  // unique
  // sort

  // OPERATORS

  const T &operator[](const size_type &t_i) { return *(head + t_i); }
  const T &operator[](const size_type &t_i) const { return *(head + t_i); }

  circular_forward_sort_list &operator=(const circular_forward_sort_list rhs)
  {
    sz = rhs.sz;
    head = rhs.head;
    return *this;
  }
  circular_forward_sort_list &operator=(circular_forward_sort_list const &) = default;
  circular_forward_sort_list &operator=(circular_forward_sort_list &&) noexcept = default;
  bool find(const T &value, iterator *&nav)
  {
    // ascendant, value > *begin()
    // descendant, value < *begin()
    auto advance_to_next_ptr = [&] { nav = &((*nav)->next); };

    nav = &head;
    if (!O(value, **nav)) { return false; }

    // nav = &((*nav)->next);
    advance_to_next_ptr();
    for (; *nav && *nav != head && O(value > **nav); advance_to_next_ptr()) { ; }
    return *nav && (**nav == value);
    // when deleting, special case for Head
  }

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


template<class T, class O> class circular_forward_sort_list<T, O>::iterator
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
      ++rhs;
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

  explicit operator bool() const { return curr; }
  explicit operator node<T> *() const { return curr; }
  bool operator==(const iterator &rhs) const { return curr == rhs.curr; }
  bool operator!=(const iterator &rhs) const { return curr != rhs.curr; }
};

template<class T, class O> ostream &operator<<(std::ostream &os, const circular_forward_sort_list<T, O> &t_list)
{
  for (auto &&elem : t_list) { os << elem << ", "; }
  return os;
}


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
template<class T, class O> bool fstd::circular_forward_sort_list<T, O>::push(const T t_value)
{
  iterator *ptr;// NOLINT initialization

  if (find(t_value, ptr)) { return false; }
  iterator new_node{ new node<T>(t_value, *ptr) };
  *ptr = new_node;
  return true;
}


// template<class T, class O> void fstd::circular_forward_sort_list<T, O>::pop_back()
// {
//   const iterator current_n{ tail };
//   tail = tail->prev;
//   tail->next = nullptr;
//   delete current_n;
//   --sz;
// }

// template<class T, class O> void fstd::circular_forward_sort_list<T, O>::pop_front()
// {
//   head = head->next;
//   delete head->prev;
//   --sz;
// }


// template<class T, class O> void fstd::circular_forward_sort_list<T, O>::resize(const size_type &new_size)
// {
//   const auto delete_nodes = [&]() {
//     while (sz > new_size) { pop_back(); }
//   };
//   const auto create_nodes = [&]() {
//     while (sz < new_size) { push(T{}); }
//   };

//   (new_size < sz) ? delete_nodes() : create_nodes();
// }

// template<class T> void fstd::circular_forward_sort_list<T,O>::swap(circular_forward_sort_list &t_list)
// {
//   circular_forward_sort_list temp{ *this };
//   *this = t_list;
//   t_list = temp;
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

#endif// __CIRCULAR_FORWARD_SORT_LIST_H__
