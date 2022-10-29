#ifndef __MERGE_SORT_H__
#define __MERGE_SORT_H__

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

// Copyright (C) 2022 José Enrique Vilca Campana

// #include "../../../tests/utils/utility.hpp"
// #include <thread>
#include <vector>

namespace fstd {
template<class It> void merge(It t_begin, It t_mid, It t_end);
template<class It> void merge_sort(It t_begin, It t_end);
}// namespace fstd


template<class It> void fstd::merge(It t_begin, It t_mid, It t_end)
{
  using value_type = typename It::value_type;
  auto copy = [](It t_t_begin, It t_t_end) -> std::vector<value_type> {
    std::vector<value_type> output;
    for (auto i = t_t_begin; i != t_t_end; ++i) { output.push_back(*i); }
    return output;
  };

  std::vector<value_type> left_array = copy(t_begin, t_mid);
  std::vector<value_type> right_array = copy(t_mid, t_end);

  auto left_it = left_array.begin();
  auto right_it = right_array.begin();

  while (left_it != left_array.end() && right_it != right_array.end()) {
    if (*left_it < *right_it) {
      *t_begin = *left_it;
      ++left_it;
    } else {
      *t_begin = *right_it;
      ++right_it;
    }
    ++t_begin;
  }

  auto copy_the_remaining_values = [&](It &t_it, std::vector<value_type> &t_vec) {
    for (; t_it != t_vec.end(); ++t_it, ++t_begin) { *t_begin = *t_it; }
  };

  copy_the_remaining_values(left_it, left_array);
  copy_the_remaining_values(right_it, right_array);
}

template<class It> void fstd::merge_sort(It t_begin, It t_end)
{
  if (t_begin >= t_end - 1) { return; }// Returns recursively

  auto mid = t_begin + (t_end - t_begin) / 2;

  merge_sort(t_begin, mid);//[begin,mid)
  merge_sort(mid, t_end);//[mid,end)
  merge(t_begin, mid, t_end);
}

// void merge(std::vector<int>::iterator t_begin, std::vector<int>::iterator t_mid, std::vector<int>::iterator t_end)
// {
//   auto copy = [](std::vector<int>::iterator t_t_begin, std::vector<int>::iterator t_t_end) -> std::vector<int> {
//     std::vector<int> output;
//     for (auto i = t_t_begin; i != t_t_end; ++i) { output.push_back(*i); }
//     return output;
//   };

//   std::vector<int> leftArray = copy(t_begin, t_mid);
//   std::vector<int> rightArray = copy(t_mid, t_end);
//   // std::cout << "\nleftArray\t:" << leftArray;
//   // std::cout << "\nrightArray\t:" << rightArray << "\n";

//   auto left_begin = leftArray.begin();
//   auto right_begin = rightArray.begin();

//   while (left_begin != leftArray.end() && right_begin != rightArray.end()) {
//     if (*left_begin < *right_begin) {
//       *t_begin = *left_begin;
//       ++left_begin;
//     } else {
//       *t_begin = *right_begin;
//       ++right_begin;
//     }
//     ++t_begin;
//   }

//   // std::cout << "after while\t:";
//   // for (auto it = t_copy_begin; it != t_end; it++) { std::cout << *it << ", "; }
//   // std::cout << std::endl;


//   auto copy_the_remaining_values = [&](std::vector<int>::iterator &t_it, std::vector<int> &t_vec) {
//     for (; t_it != t_vec.end(); ++t_it, ++t_begin) { *t_begin = *t_it; }
//   };

//   copy_the_remaining_values(left_begin, leftArray);
//   copy_the_remaining_values(right_begin, rightArray);

//   // std::cout << "after remaining\t:";
//   // for (auto it = t_copy_begin; it != t_end; it++) { std::cout << *it << ", "; }
//   // std::cout << std::endl;
// }

// void merge_sort(std::vector<int>::iterator t_begin, std::vector<int>::iterator t_end, unsigned t_numCPU)
// {
//   if (t_begin >= t_end) { return; }// Returns recursively
//   if (t_numCPU == 1) {
//     std::sort(t_begin, t_end);
//     return;
//   }

//   auto mid = t_begin + (t_end - t_begin) / 2;

//   merge_sort(t_begin, mid, t_numCPU / 2);//[begin,mid)
//   std::thread thr = std::thread(merge_sort, mid, t_end, t_numCPU - t_numCPU / 2);//[mid,end)

//   thr.join();
//   merge(t_begin, mid, t_end);
// }

// namespace ranges {
//   void merge_sort(std::vector<int> &t_cont)
//   {
//     auto begin = t_cont.begin();
//     auto end = t_cont.end();
//     fstd::merge_sort(begin, end);
//   }

// }// namespace ranges

// int main()
// {
//   using int_type = int;
//   const int data_size = 4;
//   std::vector<int_type> vec = fill_vector_with_random_data<int_type>(data_size);
//   // std::vector<int> vec{ 12, 11, 13, 5, 6, 7 };// NOLINT magic number
//   // std::vector<int> vec{ 12, 11, 13 };// NOLINT magic number
//   // std::vector<int> vec{ 12, 11 };// NOLINT magic number

//   auto numCPU{ std::thread::hardware_concurrency() };
//   std::cout << "Given vec is \n" << vec << "\n";

//   merge_sort(vec.begin(), vec.end(), numCPU);

//   cout << "\nSorted vec is \n" << vec << "\n";
//   return 0;
// }
// int main()
// {
//   using int_type = int;
//   // const int data_size = 4;
//   // std::vector<int_type> vec = utils::fill_vector_with_random_data<int_type>(data_size);
//   std::vector<int> vec{ 12, 11, 13, 5, 6, 7 };// NOLINT magic number
//   // std::vector<int> vec{ 12, 11, 13 };// NOLINT magic number
//   // std::vector<int> vec{ 12, 11 };// NOLINT magic number

//   std::cout << "Given vec is \n" << vec << "\n";

//   fstd::merge_sort(vec.begin(), vec.end());

//   cout << "\nSorted vec is \n" << vec << "\n";
//   return 0;
// }

#endif// __MERGE_SORT_H__
