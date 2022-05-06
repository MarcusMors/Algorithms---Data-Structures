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
template<typename T> struct node
{
  T value;
  node<T> *prev{ nullptr };
  node<T> *next{ nullptr };

  node() = default;
  ~node() = default;
  explicit node(const T v) : value{ v } {}// NOLINT
  node(const T v, node<T> *n, node<T> *p) : value{ v }, next{ n }, prev{ p } {}// NOLINT
  node(const node<T> &n) : next{ n.next }, prev{ n.prev }, value{ n.value } {}
  node(const node<T> &&n) noexcept : next{ n.next }, prev{ n.prev }, value{ n.value } {}
  explicit node(const node<T> *&n) : next{ n->next }, prev{ n->prev }, value{ n->value } {}
};
}// namespace fstd
