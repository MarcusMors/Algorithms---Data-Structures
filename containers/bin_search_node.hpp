#ifndef __BIN_SEARCH_NODE_H__
#define __BIN_SEARCH_NODE_H__

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
namespace fstd {
template<typename T> struct bin_search_node
{
  T value{};
  T balance_factor{};
  T height{};
  bin_search_node<T> *nodes[2]{ nullptr, nullptr };// NOLINT C-style array
  bin_search_node<T> *&left{ nodes[0] };
  bin_search_node<T> *&right{ nodes[1] };

  bin_search_node() = default;
  ~bin_search_node() = default;
  explicit bin_search_node(const T v) : value{ v } {}// NOLINT
  explicit bin_search_node(const bin_search_node<T> *&n) : value{ n->value }, left{ n->left }, right{ n->right } {}
  bin_search_node(const T v, bin_search_node<T> *n[2]) : value{ v }, left{ n[0] }, right{ n[1] } {}// NOLINT
  bin_search_node(const T v, bin_search_node<T> *l, bin_search_node<T> *r)
    : value{ v }, left{ l }, right{ r } {}// NOLINT
  bin_search_node(const bin_search_node<T> &n) : value{ n.value }, left{ n.left }, right{ n.right } {}
  bin_search_node(const bin_search_node<T> &&n) noexcept : value{ n.value }, left{ n.left }, right{ n.right } {}
  bin_search_node &operator=(const bin_search_node &) = default;
  bin_search_node &operator=(bin_search_node &&) noexcept = default;
};
}// namespace fstd

#endif// __BIN_SEARCH_NODE_H__
