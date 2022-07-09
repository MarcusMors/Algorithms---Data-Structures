#ifndef __SPARSE_MATRIX_H__
#define __SPARSE_MATRIX_H__

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

#include <cassert>
#include <cstddef>//import std::size_t
#include <iostream>
#include <limits>
// user made libs
// #include "forward_list.hpp" //not recommended: creating your own list type for the array of pointers to nodes.

namespace fstd {

template<class T> struct sparse_node
{
  using size_type = size_t;
  sparse_node() = default;
  sparse_node(T t_value,
    size_type t_h_index,
    size_type t_v_index,
    sparse_node<T> *t_down = nullptr,// NOLINT adjacent
    sparse_node<T> *t_right = nullptr)// NOLINT adjacent
    : value{ t_value }, bearings{ t_h_index, t_v_index }, down{ t_down }, right{ t_right }
  {}

  T value{};
  size_type bearings[2]{ std::numeric_limits<size_type>::max(), std::numeric_limits<size_type>::max() };
  size_type &h_index{ bearings[0] };
  size_type &v_index{ bearings[1] };

  sparse_node<T> *down{ nullptr };
  sparse_node<T> *right{ nullptr };
};


template<class T, std::size_t h_size, std::size_t v_size, T default_value = T{}> class sparse_matrix
{
public:
  using size_type = std::size_t;
  using value_type = T;
  using node_type = sparse_node<T>;
  class iterator;
  using iterator_type = iterator;

private:
  node_type *m_horizontal_array[h_size];// NOLINT C-style array
  node_type *m_vertical_array[v_size];// NOLINT C-style array

  bool horizontal_find(size_type t_h_index, size_type t_v_index, node_type **&t_ptr)
  {
    t_ptr = &(m_vertical_array[t_v_index]);
    if (m_vertical_array[t_v_index] == nullptr) { return false; }

    for (; ((*t_ptr)->right != nullptr) && ((*t_ptr)->right->h_index < t_h_index); t_ptr = &((*t_ptr)->right)) { ; }
    const bool does_the_right_node_holds_the_h_index = (*t_ptr)->right->h_index == t_h_index;
    return (*t_ptr)->right != nullptr && does_the_right_node_holds_the_h_index;
  }
  bool vertical_find(size_type t_h_index, size_type t_v_index, node_type **&t_ptr)
  {
    using namespace std;
    t_ptr = &(m_horizontal_array[t_h_index]);
    if (*t_ptr == nullptr) { return false; }
    // cout << "before crash: " << (*t_ptr)->value << endl;

    for (; ((*t_ptr)->right != nullptr) && ((*t_ptr)->right->bearings[0] < t_v_index); t_ptr = &((*t_ptr)->right)) { ; }
    const bool does_the_right_node_holds_the_v_index = (*t_ptr)->right->bearings[0] == t_v_index;
    return (*t_ptr)->right != nullptr && does_the_right_node_holds_the_v_index;
  }

public:
  // sparse_matrix() = default;

  value_type &operator()(size_type t_h_index, size_type t_v_index)
  {
    assert(t_h_index < h_size);
    assert(t_v_index < v_size);

    node_type **v_ptr_ptr;
    node_type **h_ptr_ptr;
    if (!vertical_find(t_h_index, t_v_index, v_ptr_ptr)) {
      // create the new node
      horizontal_find(t_h_index, t_v_index, h_ptr_ptr);
      // const auto connect_node = [&]() {
      node_type *new_node = new node_type(default_value, t_h_index, t_v_index);// NOLINT
      if (*h_ptr_ptr != nullptr) { new_node->right = (*h_ptr_ptr); }
      *h_ptr_ptr = new_node;
      if (*v_ptr_ptr != nullptr) { new_node->down = (*v_ptr_ptr); }
      *v_ptr_ptr = new_node;
      // };
      // connect_node();
      return new_node->value;
    }

    return (*v_ptr_ptr)->down->value;
  }

  // ~sparse_matrix();
};


}// namespace fstd

template<class T, std::size_t h_size, std::size_t v_size, T default_value>
class fstd::sparse_matrix<T, h_size, v_size, default_value>::iterator
{
public:
  using node_type = fstd::sparse_matrix<T, h_size, v_size, default_value>::node_type;
  using size_type = fstd::sparse_matrix<T, h_size, v_size, default_value>::size_type;
  using value_type = fstd::sparse_matrix<T, h_size, v_size, default_value>::value_type;

private:
  node_type **v_ptr_ptr{ nullptr };
  node_type **h_ptr_ptr{ nullptr };

public:
  iterator(node_type **t_v, node_type **t_h) : v_ptr_ptr{ t_v }, h_ptr_ptr{ t_h } {}
  // explicit iterator(node<T> *p) : curr{ p } {}
  // iterator(const iterator &it) : curr{ it.curr } {}

  // iterator &operator=(const iterator &it)
  // {
  //   //
  //   return *this;
  // }
  iterator operator=(node_type *const &it)
  {
    //
    return *this;
  }

  // unary operators
  operator value_type()
  {
    // find
    return (*v_ptr_ptr)->down->value;
  }
};

// fstd::sparse_matrix::sparse_matrix();

// sparse_matrix::~sparse_matrix() {}

#endif// __SPARSE_MATRIX_H__
