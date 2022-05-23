#ifndef __FORWARD_NODE_H__
#define __FORWARD_NODE_H__

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
template<typename T> struct forward_node
{
  T value{};
  forward_node<T> *next{ nullptr };

  forward_node() = default;
  ~forward_node() = default;
  explicit forward_node(const T v) : value{ v } {}
  forward_node(const T v, forward_node<T> *n) : value{ v }, next{ n } {}// NOLINT

  explicit forward_node(const forward_node<T> &n) : next{ n.next }, value{ n.value } {}
  explicit forward_node(const forward_node<T> &&n) noexcept : next{ n.next }, value{ n.value } {}
  explicit forward_node(const forward_node<T> *&n) : next{ n->next }, value{ n->value } {}
  // forward_node &operator=(forward_node *&) = default;
  forward_node &operator=(forward_node const &) = default;
  forward_node &operator=(forward_node &&) noexcept = default;
};
}// namespace fstd

#endif// __FORWARD_NODE_H__
