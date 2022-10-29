#ifndef __INSERTION_SORT_H__
#define __INSERTION_SORT_H__

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
#include <vector>

namespace fstd {
template<class T> using iterator = typename std::vector<T>::iterator;

template<class T> void insertion_sort(iterator<T> t_begin, iterator<T> t_end);
}// namespace fstd

template<class T> void fstd::insertion_sort(iterator<T> t_begin, iterator<T> t_end)
{
  for (auto it = t_begin + 1; it != t_end; it++) {
    T key{ *it };
    auto jt{ it - 1 };
    for (; jt >= t_begin and *jt > key; --jt) { *(jt + 1) = *jt; }
    *(jt + 1) = key;
  }
}

#endif// __INSERTION_SORT_H__
