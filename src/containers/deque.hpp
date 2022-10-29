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

#include "node/page.hpp"
#include <initializer_list>

namespace fstd {
template<class T, std::size_t Page_size = 5> class deque
{
public:
  using size_type = std::size_t;
  using page_t = page<T, Page_size>;
  using iterator_type = T *;

private:
  const static size_type page_size = Page_size;

  size_type m_size{ 0 };
  size_type map_reserved_size{ Page_size * 3 };

  const static size_type default_initial_size = 7;
  const static size_type default_begin_pos = default_initial_size / 2;
  const static size_type default_end_pos = default_initial_size + 1;

  page_t *map{ new page_t[3 * Page_size] };// NOLINT
  page_t *map_reserved_end{ &map[3 * Page_size] };// map_virtual_end)

  page_t *map_virtual_begin{ &map[default_begin_pos] };// [map_virtual_begin
  page_t *map_virtual_end{ &map[default_end_pos] };// map_virtual_end)
  T *page_begin;

  enum overflow_type {
    none,
    both,
    right,
  };

  template<overflow_type Overflow_t>
  void fill_deque(std::initializer_list<T> t_init, const size_type t_quotient, const size_type t_overflow);
  size_type get_adder() { return page_begin - &(map_virtual_begin->arr[0]); }
  // size_type get_map_index(const size_type &index) {map_reserved_size}
  page_t *get_page(const size_type &index) { return *(map_virtual_begin + ((index + get_adder()) / page_size)); }

  // this implementation doesn't realloc, it always copies.
  void expand() { page_t *new_map = new page_t[map_reserved_size * 3]; }

public:
  deque() = default;// init defaults
  // deque(std::initializer_list<T> t_init) : m_size{ t_init.size() }
  deque(std::initializer_list<T> t_init);

  ~deque() { delete[] map; }

  size_type size() { return m_size; }
  size_type push_back(const T t_element)
  {
    if (end() == &((map + map_reserved_size - 1)->arr[page_size])) { expand(); }
    // insert

    return m_size;
  }
  // size_type pop_back() { return m_size; }
  // size_type push_front(const T t_element) { return m_size; }
  // size_type pop_front() { return m_size; }

  // operators
  T &operator[](const size_type &index)
  {
    page_t page = get_page(index);
    return page[(index + get_adder()) % page_size];
  }
  iterator_type end() { return (map_virtual_end - 1)->arr[page_size]; }
  iterator_type begin() { return page_begin; }
};

}// namespace fstd

template<class T, std::size_t Page_size>
fstd::deque<T, Page_size>::deque(std::initializer_list<T> t_init) : m_size{ t_init.size() }
{
  const size_type quotient = m_size / page_size;
  const size_type overflow = m_size - quotient * page_size;
  if (quotient == 0) {
    map = new page_t[3];// NOLINT

    map_virtual_begin = &map[1];
    map_virtual_end = &map[2];
    map_reserved_end = &map[2];
    fill_deque<overflow_type::right>(t_init, quotient, overflow);
    return;
  }

  map = new page_t[quotient * 3];// NOLINT
  map_reserved_end = &map[quotient * 3];

  switch (overflow) {
  case 0:
    map_virtual_begin = &map[quotient];
    map_virtual_end = &map[2 * quotient];
    fill_deque<overflow_type::none>(t_init, quotient, overflow);
    break;
  case 1:
    map_virtual_begin = &map[quotient];
    map_virtual_end = &map[(2 * quotient) + 1];
    fill_deque<overflow_type::right>(t_init, quotient, overflow);
    break;

  default:
    map_virtual_begin = &map[quotient - 1];
    map_virtual_end = &map[(2 * quotient) + 1];
    fill_deque<overflow_type::both>(t_init, quotient, overflow);
    break;
  }
}

// https://en.cppreference.com/w/cpp/language/member_template
template<class T, std::size_t Page_size>// for the enclosing class template
template<typename fstd::deque<T, Page_size>::overflow_type Overflow_t>// for the member template
void fstd::deque<T, Page_size>::fill_deque(std::initializer_list<T> t_init,
  const typename fstd::deque<T, Page_size>::size_type t_quotient,
  const typename fstd::deque<T, Page_size>::size_type t_overflow)

// typename fstd::deque<T, Page_size>::overflow_type Overflow_t
{
  auto init_it = t_init.begin();
  T *page_it;// NOLINT

  auto fill_left = [&]() {
    for (; page_it < map_virtual_begin->arr + page_size; page_it++, init_it++) { *page_it = *init_it; }
  };
  auto fill_mid = [&](const size_type incrementor) {// incrementor{0 or 1}
    for (size_t i = 0; i < t_quotient; i++) {
      T *page_it_arr = (map_virtual_begin + i + incrementor)->arr;
      page_it = page_it_arr;
      for (; page_it < page_it_arr + page_size; page_it++, init_it++) { *page_it = *init_it; }
    }// fill mid
  };
  auto fill_right = [&]() {
    for (; init_it < t_init.end(); init_it++, page_it++) { *page_it = *init_it; }
  };

  switch (Overflow_t) {
  case overflow_type::none: {
    page_begin = map_virtual_begin->arr;
    page_it = page_begin;
    fill_mid(0);
    break;
  }
  case overflow_type::both: {
    const size_type left_overflow = t_overflow / 2;
    page_begin = map_virtual_begin->arr + (page_size - left_overflow);
    page_it = page_begin;
    fill_left();
    fill_mid(1);
    page_it = (map_virtual_end - 1)->arr;
    fill_right();
    break;
  }
  case overflow_type::right: {
    page_begin = map_virtual_begin->arr;
    page_it = page_begin;

    fill_mid(0);
    page_it = (map_virtual_end - 1)->arr;
    fill_right();
    break;
  }
  }
}
