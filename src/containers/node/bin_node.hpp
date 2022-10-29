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
template<typename T> struct bin_node
{
  using value_type = T;
  T value;
  bin_node<T> *nodes[2];
  bin_node<T> *&left = nodes[0];
  bin_node<T> *&right = nodes[1];

  bin_node() = default;
  ~bin_node() = default;

  explicit bin_node(const T v) : value{ v } {}// NOLINT
  bin_node(const T v, bin_node<T> *l, bin_node<T> *r) : value{ v }, left{ l }, right{ r } {}// NOLINT
};

}// namespace fstd
