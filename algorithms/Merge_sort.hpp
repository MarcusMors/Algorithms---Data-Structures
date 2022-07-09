#ifndef __MERGE_SORT_H__
#define __MERGE_SORT_H__

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

#include <algorithm>
#include <iostream>
#include <thread>

namespace fstd {

template<class T, class it> struct Merge_sort
{
  Merge_sort() = default;
  ~Merge_sort() = default;

  void single_thread_merge_sort(it t_begin, it t_end)
  {
    // std::cout << "\t inside single_thread_merge_sort\t\n";

    if (t_begin >= t_end) { return; }// Returns recursively

    auto mid = t_begin + (t_end - t_begin) / 2;
    single_thread_merge_sort(t_begin, mid);
    single_thread_merge_sort(mid + 1, t_end);
    // std::cout << "\t before merge\t\n";
    merge(t_begin, mid, t_end);
    // std::cout << "\t after merge\t\n";
  }

  void merge(//
    it t_begin,
    it t_mid,
    it t_end);

  void operator()(it t_begin, it t_end, unsigned t_numCPU)
  {
    if (t_begin >= t_end) { return; }// Returns recursively
    if (t_numCPU == 1) {
      single_thread_merge_sort(t_begin, t_end);
      // std::sort(t_begin, t_end);
      return;
    }

    auto mid = t_begin + (t_end - t_begin) / 2;


    Merge_sort<T, it> merge_sort;
    merge_sort(t_begin, mid, t_numCPU / 2);//[begin,mid)
    std::thread thr = std::thread(merge_sort, mid + 1, t_end, t_numCPU - t_numCPU / 2);//[mid,end)

    thr.join();
    merge(t_begin, mid, t_end);
  }
};

}// namespace fstd

template<class T, class it> void fstd::Merge_sort<T, it>::merge(it t_begin, it t_mid, it t_end)
{
  auto copy = [](std::vector<T>::iterator t_t_begin, std::vector<T>::iterator t_t_end) -> std::vector<T> {
    std::vector<T> output;
    for (auto i = t_t_begin; i != t_t_end; ++i) { output.push_back(*i); }
    return output;
  };

  std::vector<T> leftArray = copy(t_begin, t_mid);
  std::vector<T> rightArray = copy(t_mid, t_end);

  auto left_begin = leftArray.begin();
  auto right_begin = rightArray.begin();

  while (left_begin != leftArray.end() && right_begin != rightArray.end()) {
    if (*left_begin < *right_begin) {
      *t_begin = *left_begin;
      ++left_begin;
    } else {
      *t_begin = *right_begin;
      ++right_begin;
    }
    ++t_begin;
  }

  auto copy_the_remaining_values = [&](it &t_it, std::vector<T> &t_vec) {
    for (; t_it != t_vec.end(); ++t_it, ++t_begin) { *t_begin = *t_it; }
  };
  // auto copy_the_remaining_values = [&]<typename T, typename it>(it &t_it, std::vector<T> &t_vec) {
  //   for (; t_it != t_vec.end(); ++t_it, ++t_begin) { *t_begin = *t_it; }
  // };

  copy_the_remaining_values(left_begin, leftArray);
  copy_the_remaining_values(right_begin, rightArray);
}

#endif// __MERGE_SORT_H__
