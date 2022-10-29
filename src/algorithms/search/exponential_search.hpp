#ifndef __EXPONENTIAL_SEARCH_H__
#define __EXPONENTIAL_SEARCH_H__

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

#include <cstddef>//import std::size_t

namespace fstd {

// std::size_t

template<class T> T *recursive_call(T *t_begin, T *t_end, T t_wanted, std::size_t t_index = 1)
{
  // if (t_begin >= t_end) { return nullptr; }
  bool is_within_range = (t_begin + t_index < t_end);
  // if (!is_within_range) { return nullptr; }
  if (!is_within_range) {
    t_index = 1;
    is_within_range = (t_begin + t_index < t_end);
    if (!is_within_range) { return nullptr; }
  }

  // while (!is_within_range) {
  //   t_index = t_index >> 1;
  //   is_within_range = (t_begin + t_index < t_end);
  // }

  if (t_begin + t_index == t_begin) { return nullptr; }


  T *next = t_begin + t_index;
  if (t_wanted > *next) {
    return recursive_call(next, t_end, t_wanted, t_index << 1);
  } else if (t_wanted < *next) {
    return recursive_call(t_begin, next, t_wanted, 1);
  }
  return next;
}

template<class T> T *recursive_exponential_search(T *t_begin, T *t_end, T t_wanted)
{
  if (t_wanted < *t_begin || t_wanted > *(t_end - 1)) { return nullptr; }
  if (*t_begin == t_wanted) { return t_begin; }// pos 0 check
  return recursive_call(t_begin, t_end, t_wanted);
}

// template<class T> T *exponential_search(T *t_begin, T *t_end, T t_wanted)
// {
//   if (t_wanted < *t_begin || *(t_end - 1) < t_wanted) { return nullptr; }
//   if (*t_begin == t_wanted) { return t_begin; }// pos 0 check

//   T *it = t_begin + 1;
//   for (std::size_t i = 2; it < t_end; i << 1, it += i) {

//     if (t_wanted > *(t_begin - 1)) {
//       continue;
//     } else if (t_wanted < *(t_end - 1)) {

//     } else {
//       return;
//     }
//   }

//   return it < t_end;
// }

}// namespace fstd

#endif// __EXPONENTIAL_SEARCH_H__
