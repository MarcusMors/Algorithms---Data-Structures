
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
#include "./bin_node.hpp"

using namespace std;

namespace fstd {
using fstd::bin_node;

template<typename T> struct bin_tree
{
  using value_type = T;
  class iterator;
  using const_iterator = const iterator;

  bin_tree() = default;
  // cppcheck-suppress noExplicitConstructor ; allowing bin_tree A = {1,2,3} and A{1,2,3}
  bin_tree(const std::initializer_list<T> init)
  {

    int count{ 0 };
    int level_count{ 1 };

    bin_node<T> *prev_node;
    for (auto it = init.begin() + 1; it != init.end(); ++it) {
      bin_node<T> *current = new bin_node<T>(*it);
      const bool complete = (count == level_count);
      if (complete) {
        current->left = prev_node;
        // from 0001 to 0011, from 1 to 3, to 5, to 9, ...
        level_count = level_count << 1;
        level_count = level_count | 1;
      } else {
        prev_node->right = current;
      }
      prev_node = current;
      ++count;
    }
  }
  bin_tree(const bin_tree &l) : root{ l.root }, tail{ l.tail } {}


  ~bin_tree()
  {
    iterator current_n{ begin() };
    while (current_n) {
      iterator next_n{ current_n->next };
      delete current_n;
      current_n = next_n;
    }
  }

  // constructor helpers

  // constructor helpers

  //  ELEMENT ACCESS
  T front() const { return root->value; }
  T back() const { return tail->value; }

  // ITERATORS
  iterator begin() { return root; }
  iterator end() { return iterator{ nullptr }; }
  const_iterator begin() const { return root; }
  const_iterator end() const { return iterator{ nullptr }; }
  const_iterator cbegin() const { return root; }
  const_iterator cend() const { return const_iterator{ nullptr }; }
  iterator rbegin() { return tail; }
  iterator rend() { return iterator{ nullptr }; }
  const_iterator crbegin() const { return tail; }
  const_iterator crend() const { return const_iterator{ nullptr }; }

  // CAPACITY
  size_type size() { return sz; }
  [[nodiscard]] bool empty() const { return (sz == 0 && !tail && !root); }
  size_type max_size() { return std::numeric_limits<size_type>::max(); }

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
  void resize(const size_type &new_size);// CopyInsertable
  void swap(bin_tree &);

  // OPERATIONS
  // merge
  // splice
  // remove
  // remove_if
  // reverse
  // unique
  // sort

  // OPERATORS
  bin_tree &operator=(const bin_tree l)
  {
    sz = l.sz;
    root = l.root;
    tail = l.tail;
    return *this;
  }

private:
  size_type sz{ 0 };
  iterator root{ nullptr };
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


template<typename T> class bin_tree<T>::iterator
{
  bin_node<T> *curr;

public:
  explicit iterator(bin_node<T> *p) : curr{ p } {}
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
  bin_node<T> *operator->() const { return curr; }// member of pointer
  iterator &operator=(const iterator &it)
  {
    curr = it.curr;
    return *this;
  }
  iterator operator=(bin_node<T> *const &it)
  {
    curr = it;
    return *this;
  }

  operator bool() const { return curr; }
  operator bin_node<T> *() const { return curr; }
  bool operator==(const iterator &rhs) const { return curr == rhs.curr; }
  bool operator!=(const iterator &rhs) const { return curr != rhs.curr; }
};

template<typename T> ostream &operator<<(std::ostream &os, const bin_tree<T> &t_list)
{
  for (auto &&elem : t_list) { os << elem << ", "; }
  return os;
}
//
//
// template<class T> ostream &operator<<(std::ostream &os, const bin_node<T> &t_node) { return os << t_node.value; }
// template<class T> ostream &operator<<(std::ostream &os, const bin_node<T> *t_node) { return os << t_node->value; }


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
template<class T> void fstd::bin_tree<T>::push_back(const T t_value)
{
  iterator temp{ new bin_node<T>(t_value) };
  if (empty()) {
    root = tail = temp;
  } else {
    tail->next = temp;
    temp->prev = tail;
    tail = temp;
    ++sz;
  }
}


template<class T> void fstd::bin_tree<T>::pop_back()
{
  const iterator current_n{ tail };
  tail = tail->prev;
  tail->next = nullptr;
  delete current_n;
  --sz;
}

template<class T> void fstd::bin_tree<T>::push_front(const T t_value)
{
  bin_node<T> *temp{ new bin_node<T>(t_value) };
  temp->next = root;
  root->prev = temp;
  root = temp;
  ++sz;
}
// emplace front

template<class T> void fstd::bin_tree<T>::pop_front()
{
  root = root->next;
  delete root->prev;
  --sz;
}


// void resize(const size_type &count, T value = T{});// DefaultInsertable
// void resize(const size_type &count, const T &value);// CopyInsertable
// Type requirements
// - T must meet the requirements of DefaultInsertable in order to use overload (1).
// - T must meet the requirements of CopyInsertable in order to use overload (2).
template<class T> void fstd::bin_tree<T>::resize(const size_type &new_size)// CopyInsertable  // needs testing
{
  // static_assert(new_size > 0);
  const auto delete_nodes = [&]() {
    // iterator current_n{ tail };
    // while (sz > new_size) {
    //   iterator prev_n{ current_n->prev };
    //   delete current_n;
    //   current_n = prev_n;
    //   --sz;
    // }
    // tail = current_n;
    while (sz > new_size) { pop_back(); }
  };
  const auto create_nodes = [&]() {
    // while (sz < new_size) {
    //   cout << "create" << endl;
    //   tail->next = new bin_node<T>(T{}, nullptr, tail);
    //   ++tail;
    //   ++sz;
    // }
    while (sz < new_size) { push_back(T{}); }
  };

  (new_size < sz) ? delete_nodes() : create_nodes();
}
template<class T> void fstd::bin_tree<T>::swap(bin_tree &t_list)
{
  bin_tree temp{ *this };
  *this = t_list;
  t_list = temp;
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
