
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
// #include "./bin_search_node.hpp"
#include "./bin_search_node.hpp"

using namespace std;

namespace fstd {
// using fstd::bin_search_node;

template<typename T, bool sorted = false> struct bin_search_tree
{
  using value_type = T;
  // class iterator;
  // using const_iterator = const iterator;

  enum tree_rotations : short {
    left_left,// right rotation about yellow to balanced
    // left,// right rotation about yellow to balanced
    left_right,// left rotation about the left child/ green to left_left,
    // then right rotation to balanced
    // right,// left rotation about green to balanced
    right_right,// left rotation about green to balanced
    right_left,// right rotation about yellow to right_right,
    // then left notation about green to balanced
  };

  bin_search_tree() = default;
  template<bool t_sorted> friend std::ostream &operator<<(std::ostream &os, const bin_search_tree<T, t_sorted> &t_tree);
  // cppcheck-suppress noExplicitConstructor ; allowing bin_search_tree A = {1,2,3} and A{1,2,3}
  // bin_search_tree(const sort_list<T> list);
  // bin_search_tree(const forward_sort_list<T> list);
  // int count{ 0 };
  // int level_count{ 1 };

  // bin_search_node<T> *prev_node;
  // for (auto it = init.begin() + 1; it != init.end(); ++it) {
  //   bin_search_node<T> *current = new bin_search_node<T>(*it);
  //   const bool complete = (count == level_count);
  //   if (complete) {
  //     current->left = prev_node;
  //     // from 0001 to 0011, from 1 to 3, to 5, to 9, ...
  //     level_count = level_count << 1;
  //     level_count = level_count | 1;
  //   } else {
  //     prev_node->right = current;
  //   }
  //   prev_node = current;
  //   ++count;
  // }
  // bin_search_tree(const std::initializer_list<T> init)
  // {
  //   if (sorted) {
  //     const auto begin = init.begin();
  //     const auto end = init.end();
  //     const T *mid = begin + (init.size() / 2);
  //     root = new bin_search_node<T>(*mid);
  //     root->left = m_fill_branch(begin, mid);
  //     root->right = m_fill_branch(mid + 1, end);
  //   } else {
  //   }
  // }
  // bin_search_node<T> *m_fill_branch(const T *t_begin, const T *t_end)
  // {
  //   if (t_begin == t_end) { return nullptr; }
  //   if (t_end - t_begin == 1) {
  //     bin_search_node<T> *new_node = new bin_search_node<T>(*t_begin);
  //     return new_node;
  //   }

  //   T *mid = static_cast<T *>(t_begin + ((t_end - t_begin) / 2));

  //   bin_search_node<T> *new_node = new bin_search_node<T>(*mid);
  //   new_node->left = m_fill_branch(t_begin, t_begin + mid);
  //   new_node->right = m_fill_branch(mid + 1, t_end);
  //   return new_node;
  // }
  bin_search_tree(const bin_search_tree &tree) : root{ tree.root } {}


  ~bin_search_tree() { m_delete_branches(root); }
  void m_delete_branches(bin_search_node<T> *&t_parent)
  {
    if (t_parent->left) { m_delete_branches(t_parent->left); }
    if (t_parent->right) { m_delete_branches(t_parent->right); }

    delete t_parent;
  }

  // CAPACITY
  [[nodiscard]] bool empty() const { return !root; }

  // MODIFIERS
  // clear
  // insert
  // emplace
  // erase
  bool insert(const T t_value);
  bool remove(const T t_value);
  bool find(const T &t_value, bin_search_node<T> **&t_ptr);

  // void swap(bin_search_tree &);

  // OPERATIONS
  // merge
  // splice
  // remove
  // remove_if
  // reverse
  // unique
  // sortx

  // OPERATORS
  bin_search_tree &operator=(const bin_search_tree rhs)
  {
    root = rhs.root;
    return *this;
  }

private:
  bin_search_node<T> *root{ nullptr };
  enum branch : bool {
    left = false,
    right = true,
  };
  branch successor{ left };
  bin_search_node<T> **reposition(bin_search_node<T> **&t_ptr);
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


template<class T> ostream &print_node(std::ostream &os, const bin_search_node<T> &t_node)
{
  if (t_node->left) { print_node(t_node->left); }
  os << t_node->value << ", ";
  if (t_node->left) { print_node(t_node->right); }
  return os;
}

template<class T, bool t_sorted> ostream &operator<<(std::ostream &os, const bin_search_tree<T, t_sorted> &t_tree)
{
  if (t_tree.empty()) { return os; }
  // print_node(t_tree->left);
  if (t_tree.root->left) { print_node(t_tree.root->left); }
  os << t_tree.root->value << ", ";
  // print_node(t_tree->right);
  if (t_tree.root->right) { print_node(t_tree.root->right); }
  return os;
}
}// namespace fstd

/****************************************************************************
 * IMPLEMENTATION DETAILS
 ****************************************************************************/


// MODIFIERS
// clear
// insert
// emplace
// erase

template<class T, bool sorted>
bool fstd::bin_search_tree<T, sorted>::find(const T &t_value, bin_search_node<T> **&t_ptr)
{
  t_ptr = &root;

  while (*t_ptr) {
    if (t_value > (*t_ptr)->value) {
      t_ptr = &((*t_ptr)->right);
    } else if (t_value < (*t_ptr)->value) {
      t_ptr = &((*t_ptr)->left);
    } else {
      return true;
    }
  }

  return false;// Not found
}


template<class T, bool sorted> bool fstd::bin_search_tree<T, sorted>::insert(const T t_value)
{
  bin_search_node<T> **ptr;
  if (find(t_value, ptr)) { return false; }
  bin_search_node<T> *new_node = new bin_search_node<T>(t_value);
  (*ptr) = new_node;
  return true;
}
// emplace front
template<class T, bool sorted>
fstd::bin_search_node<T> **fstd::bin_search_tree<T, sorted>::reposition(bin_search_node<T> **&t_ptr)
{
  bin_search_node<T> **nav = &((*t_ptr)->nodes[successor]);
  while ((*nav)->nodes[!successor]) { nav = &((*nav)->nodes[!successor]); }
  return nav;
}


template<class T, bool sorted> bool fstd::bin_search_tree<T, sorted>::remove(const T t_value)
{
  bin_search_node<T> **ptr;
  if (!find(t_value, ptr)) { return false; }

  const bool has_right = (*ptr)->right;
  const bool has_left = (*ptr)->left;

  if (has_left && has_right) {// case 3
    bin_search_node<T> **nav = reposition(ptr);
    (*ptr)->value = (*nav)->value;
    ptr = nav;
  }
  bin_search_node<T> *d_node = *ptr;
  bool not_null_branch = (*ptr)->left == nullptr;
  *ptr = (*ptr)->nodes[not_null_branch];
  delete d_node;
  return true;
}

// template<class T> void fstd::bin_search_tree<T>::swap(bin_search_tree &t_list)
// {
//   bin_search_tree temp{ *this };
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
