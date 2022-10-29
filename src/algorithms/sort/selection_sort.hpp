#ifndef __SELECTION_SORT_H__
#define __SELECTION_SORT_H__

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

#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace fstd {
template<class T> using iterator = typename std::vector<T>::iterator;

template<typename T>
concept Pointer = requires(T ptr)
{
  *ptr;
};

template<Pointer T> void m_swap(T t_a, T t_b)
{
  int tmp = *t_a;
  *t_a = *t_b;
  *t_b = tmp;
  // cout << *t_a << " - " << *t_b << endl;
}


template<class T> void selection_sort(iterator<T> t_begin, iterator<T> t_end);
}// namespace fstd

template<class T> void fstd::selection_sort(iterator<T> t_begin, iterator<T> t_end)
{
  const auto mid = t_begin + ((t_end - t_begin) / 2);

  for (auto it = t_begin; it != mid; it++) {// n/2
    auto min = it;// (n/2)-1
    for (auto jt = it; jt != t_end; jt++) {// $\sum_{j = 2}^{n} t_j$
      if (*jt < *min) {// $\sum_{j = 2}^{n} (t_j-1)$
        min = jt;// $\sum_{j = 2}^{n} (t_j-1)$
      }
    }
    m_swap(it, min);// (3n/2)-3;
  }
}

#endif// __SELECTION_SORT_H__
