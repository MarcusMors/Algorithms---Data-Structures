#ifndef __FUNCTION_PTR_MERGE_SORT_H__
#define __FUNCTION_PTR_MERGE_SORT_H__


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


#include <vector>

namespace alex {
namespace function_ptr {

  bool Lesser(const short lhs, const short rhs) { return lhs < rhs; }
  bool Greater(const short lhs, const short rhs) { return lhs > rhs; }

  void merge(std::vector<short>::iterator t_begin,
    std::vector<short>::iterator t_mid,
    std::vector<short>::iterator t_end,
    bool (*t_comparison)(const short, const short))
  {
    using it = std::vector<short>::iterator;
    auto copy = [](it t_t_begin, it t_t_end) -> std::vector<short> {
      std::vector<short> output;
      for (auto i = t_t_begin; i != t_t_end; ++i) { output.push_back(*i); }
      return output;
    };

    std::vector<short> left_array = copy(t_begin, t_mid);
    std::vector<short> right_array = copy(t_mid, t_end);

    auto left_begin = left_array.begin();
    auto right_begin = right_array.begin();

    while (left_begin != left_array.end() && right_begin != right_array.end()) {
      if (t_comparison(*left_begin, *right_begin)) {
        *t_begin = *left_begin;
        ++left_begin;
      } else {
        *t_begin = *right_begin;
        ++right_begin;
      }
      ++t_begin;
    }

    auto copy_the_remaining_values = [&](it &t_it, std::vector<short> &t_vec) {
      for (; t_it != t_vec.end(); ++t_it, ++t_begin) { *t_begin = *t_it; }
    };

    copy_the_remaining_values(left_begin, left_array);
    copy_the_remaining_values(right_begin, right_array);
  }

  void merge_sort(std::vector<short>::iterator t_begin,
    std::vector<short>::iterator t_end,
    bool (*t_comparison)(const short, const short))
  {
    if (t_begin >= t_end - 1) { return; }// Returns recursively

    auto mid = t_begin + (t_end - t_begin) / 2;

    merge_sort(t_begin, mid, t_comparison);//[begin,mid)
    merge_sort(mid, t_end, t_comparison);//[mid,end)
    merge(t_begin, mid, t_end, t_comparison);
  }
}// namespace function_ptr
}// namespace alex

#endif// __FUNCTION_PTR_MERGE_SORT_H__
