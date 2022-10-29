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

#include <array>
#include <cassert>
#include <cstddef>//import std::size_t
#include <iostream>
#include <limits>

namespace fstd {

template<class T> struct sparse_node
{
  using size_type = size_t;
  sparse_node() = default;
  sparse_node(T t_value,
    size_type t_h_index,
    size_type t_v_index,
    sparse_node<T> *t_down = nullptr,
    sparse_node<T> *t_right = nullptr)
    : value{ t_value }, h_index{ t_h_index }, v_index{ t_v_index }, down{ t_down }, right{ t_right }
  {}

  T value{};
  size_type h_index{ std::numeric_limits<size_type>::max() };
  size_type v_index{ std::numeric_limits<size_type>::max() };

  sparse_node<T> *down{ nullptr };
  sparse_node<T> *right{ nullptr };
};


template<class T, std::size_t h_size, std::size_t v_size, T default_value = T{}> class sparse_matrix
{
public:
  using size_type = std::size_t;
  using value_type = T;
  using node_type = sparse_node<T>;
  class reference;
  using reference_type = reference;

private:
  // std::array<node_type *, h_size> m_horizontal_array;
  node_type *m_horizontal_array[h_size]{ nullptr };
  node_type *m_vertical_array[v_size]{ nullptr };
  // std::array<node_type *, v_size> m_vertical_array;

public:
  sparse_matrix() {}
  // {
  // m_horizontal_array.fill(nullptr);
  // m_vertical_array.fill(nullptr);
  // };
  sparse_matrix(sparse_matrix &&) = default;// NOLINT noexcept //copy constructor

  ~sparse_matrix();

  bool horizontal_find(size_type t_h_index, size_type t_v_index, node_type **&t_ptr)
  {
    t_ptr = &(m_vertical_array[t_v_index]);
    if (*t_ptr == nullptr) { return false; }
    for (; (*t_ptr)->right && ((*t_ptr)->right->h_index < t_h_index); t_ptr = &((*t_ptr)->right)) { ; }
    return *t_ptr && ((*t_ptr)->h_index == t_h_index);
  }
  bool vertical_find(size_type t_h_index, size_type t_v_index, node_type **&t_ptr)
  {
    t_ptr = &(m_horizontal_array[t_h_index]);
    if (*t_ptr == nullptr) { return false; }
    for (; (*t_ptr)->down && ((*t_ptr)->down->v_index < t_v_index); t_ptr = &((*t_ptr)->down)) { ; }
    return *t_ptr && ((*t_ptr)->v_index == t_v_index);
  }

  // operators
  sparse_matrix &operator=(sparse_matrix &&) = default;// NOLINT noexcept

  reference operator()(size_type t_h_index, size_type t_v_index)
  {
    assert(t_h_index < h_size);
    assert(t_v_index < v_size);
    return reference{ this, t_h_index, t_v_index };
  }
};

}// namespace fstd

template<class T, std::size_t h_size, std::size_t v_size, T default_value>
class fstd::sparse_matrix<T, h_size, v_size, default_value>::reference
{
public:
  using node_type = fstd::sparse_matrix<T, h_size, v_size, default_value>::node_type;
  using size_type = fstd::sparse_matrix<T, h_size, v_size, default_value>::size_type;
  using value_type = fstd::sparse_matrix<T, h_size, v_size, default_value>::value_type;

private:
  sparse_matrix *origin{ nullptr };
  size_type h_index{};
  size_type v_index{};

  enum cases : int {
    erase = 0,
    insert = 1,
    get = 2,
    assign = 3,
  };

  cases check_assignment_case(node_type **&t_v_ptr_ptr, value_type rhs)
  {
    if (rhs == default_value) { return cases::erase; }
    if (!origin->vertical_find(h_index, v_index, t_v_ptr_ptr)) { return cases::insert; }
    return cases::assign;
  }

public:
  explicit reference(sparse_matrix *t_origin, const size_type t_h_index, const size_type t_v_index)
    : origin{ t_origin }, h_index{ t_h_index }, v_index{ t_v_index }
  {}

  reference &operator=(value_type rhs)
  {
    node_type **v_ptr_ptr;
    node_type **h_ptr_ptr;

    switch (check_assignment_case(v_ptr_ptr, rhs)) {
    case cases::erase: {
      if (!origin->horizontal_find(h_index, v_index, h_ptr_ptr)) { return *this; }// there is no node to erase
      node_type *tmp_ptr{ *v_ptr_ptr };
      *v_ptr_ptr = (*v_ptr_ptr)->down;
      *h_ptr_ptr = (*h_ptr_ptr)->right;
      delete tmp_ptr;
    } break;
    case cases::insert: {
      origin->horizontal_find(h_index, v_index, h_ptr_ptr);
      node_type *new_node = new node_type(rhs, h_index, v_index, *v_ptr_ptr, *h_ptr_ptr);// NOLINT
      *v_ptr_ptr = new_node;
      *h_ptr_ptr = new_node;

    } break;
    case cases::assign:
      origin->horizontal_find(h_index, v_index, h_ptr_ptr);
      (*v_ptr_ptr)->down->value = rhs;
      break;

    default:
      break;
    }
    return *this;
  }

  // unary operators
  operator value_type() const
  {
    node_type **v_ptr_ptr;
    if (!origin->vertical_find(h_index, v_index, v_ptr_ptr)) { return default_value; }
    return (*v_ptr_ptr)->value;
  }
};

template<class T, std::size_t h_size, std::size_t v_size, T default_value = T{}>
std::ostream &operator<<(std::ostream &os,
  const typename fstd::sparse_matrix<T, h_size, v_size, default_value>::reference &t_sparse_matrix_it)
{
  return os << static_cast<T>(t_sparse_matrix_it);
}

template<class T, std::size_t h_size, std::size_t v_size, T default_value>
fstd::sparse_matrix<T, h_size, v_size, default_value>::~sparse_matrix()
{
  for (node_type *node_ptr : m_horizontal_array) {
    while (node_ptr) {
      node_type *next_n{ node_ptr->down };
      delete node_ptr;
      node_ptr = next_n;
    }
  }
}

#endif// __SPARSE_MATRIX_H__
