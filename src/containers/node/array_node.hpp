#ifndef __ARRAY_NODE_H__
#define __ARRAY_NODE_H__


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

#include <cstddef>//importing size_t

namespace fstd {
template<typename T, std::size_t Size> struct array_node
{
  using size_type = std::size_t;
  using value_type = T;

  const size_type size = Size;

  array_node<T, Size> *next{ nullptr };

  T value[Size];

  array_node() = default;
  ~array_node() = default;
  explicit array_node(const T v) : value{ v } {}// NOLINT
  array_node(const T v, array_node<T, Size> *n) : value{ v }, next{ n } {}// NOLINT
  // array_node(const array_node<T, Size> &n) : next{ n.next }, value{ n.value } {}
  // array_node(const array_node<T, Size> &&n) noexcept : next{ n.next }, value{ n.value } {}
  // explicit array_node(const array_node<T, Size> *&n) : next{ n->next }, value{ n->value } {}
};
}// namespace fstd

#endif// __ARRAY_NODE_H__
