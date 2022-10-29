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

#include "node/array_node.hpp"
#include <initializer_list>

namespace fstd {
//

template<class T, std::size_t Arr_size> class sorted_array_list
{
public:
  using node_type = array_node<T, Arr_size>;
  using size_type = std::size_t;
  using value_type = T;
  const size_type arr_size = Arr_size;

private:
  node_type *head{ nullptr };
  node_type *tail{ nullptr };
  bool find(T t_wanted, node_type **&t_node, size_type &iterations)
  {
    t_node = &head;
    iterations = 0;

    for (; *t_node != nullptr; t_node = &((*t_node)->next)) {
      size_type remainder{};
      do {
        remainder = iterations % arr_size;
        const T elem = (*t_node)->value[remainder];
        if (elem < t_wanted) { return elem == t_wanted; }
        ++iterations;
      } while (remainder != 0);
    }
    return false;
  }

public:
  sorted_array_list() = default;
  // sorted_array_list(std::initializer_list<T> t_init)
  // {
  // size_type quotient = t_init.size() / Arr_size;
  // head = new node_type[];
  //
  // }
  bool insert(T t_value)
  {
    node_type **pos{};
    size_type iterations{ 0 };
    if (find(t_value, pos, iterations)) { return false; }

    if (*pos == nullptr) {
      *pos = new node_type;
      (*pos)->value[0] = t_value;
      return true;
    }

    // shift right and insert
    for (; *pos != nullptr; pos = &((*pos)->next)) {
      size_type remainder = iterations % arr_size;
      while (remainder != arr_size - 1) {
        remainder = iterations % arr_size;

        (*pos)->value[remainder + 1] = (*pos)->value[remainder];
        ++iterations;
      }
      if (remainder == arr_size - 1) { (*pos)->value[remainder] = (*pos)->next->value[0]; }
    }
    return true;
  }
  bool remove(T t_value)
  {
    node_type **pos{};
    size_type iterations{ 0 };
    if (!find(t_value, pos, iterations)) { return false; }
    // remove and shift left
  }
  ~sorted_array_list() = default;

  T &operator[](size_type t_index)
  {
    size_type quotient = t_index / arr_size;
    node_type *it = begin();
    for (size_type i = 0; i < quotient; ++i, it = it->next) {}

    return it->value[t_index % arr_size];
  }

  node_type *begin() { return head; }
};

}// namespace fstd
