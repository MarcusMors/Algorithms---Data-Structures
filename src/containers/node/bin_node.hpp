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
struct bin_node
{
  template<typename T> struct bin_node
  {
    T value;
    bin_node<T> *prev{ nullptr };
    bin_node<T> *next{ nullptr };

    bin_node() = default;
    ~bin_node() = default;
    explicit bin_node(const T v) : value{ v } {}// NOLINT
    bin_node(const T v, bin_node<T> *n, bin_node<T> *p) : value{ v }, next{ n }, prev{ p } {}// NOLINT
    bin_node(const bin_node<T> &n) : next{ n.next }, prev{ n.prev }, value{ n.value } {}
    bin_node(const bin_node<T> &&n) noexcept : next{ n.next }, prev{ n.prev }, value{ n.value } {}
    explicit bin_node(const bin_node<T> *&n) : next{ n->next }, prev{ n->prev }, value{ n->value } {}
  };
};

}// namespace fstd
