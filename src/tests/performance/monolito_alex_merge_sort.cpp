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

#include <benchmark/benchmark.h>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace alex {
namespace basic {
  void
    merge(std::vector<short>::iterator t_begin, std::vector<short>::iterator t_mid, std::vector<short>::iterator t_end)
  {
    using it = typename std::vector<short>::iterator;
    auto copy = [](it t_t_begin, it t_t_end) -> std::vector<short> {
      std::vector<short> output;
      for (auto i = t_t_begin; i != t_t_end; ++i) { output.push_back(*i); }
      return output;
    };

    std::vector<short> leftArray = copy(t_begin, t_mid);
    std::vector<short> rightArray = copy(t_mid, t_end);

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

    auto copy_the_remaining_values = [&](it &t_it, std::vector<short> &t_vec) {
      for (; t_it != t_vec.end(); ++t_it, ++t_begin) { *t_begin = *t_it; }
    };

    copy_the_remaining_values(left_begin, leftArray);
    copy_the_remaining_values(right_begin, rightArray);
  }

  void merge_sort(std::vector<short>::iterator t_begin, typename std::vector<short>::iterator t_end)
  {
    if (t_begin >= t_end - 1) { return; }// Returns recursively

    auto mid = t_begin + (t_end - t_begin) / 2;

    merge_sort(t_begin, mid);//[begin,mid)
    merge_sort(mid, t_end);//[mid,end)
    merge(t_begin, mid, t_end);
  }
}// namespace basic
}// namespace alex
namespace alex {
namespace functor {

  struct Lesser
  {
    bool operator()(const short lhs, const short rhs) { return lhs < rhs; }
  };

  struct Greater
  {
    bool operator()(const short lhs, const short rhs) { return lhs > rhs; }
  };

  template<class Comparison>
  void merge(typename std::vector<short>::iterator t_begin,
    typename std::vector<short>::iterator t_mid,
    typename std::vector<short>::iterator t_end,
    Comparison t_comparison)
  {
    using it = typename std::vector<short>::iterator;
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

  template<class Comparison>
  void merge_sort(typename std::vector<short>::iterator t_begin,
    typename std::vector<short>::iterator t_end,
    Comparison t_comparison)
  {
    if (t_begin >= t_end - 1) { return; }// Returns recursively

    auto mid = t_begin + (t_end - t_begin) / 2;

    merge_sort<Comparison>(t_begin, mid, t_comparison);//[begin,mid)
    merge_sort<Comparison>(mid, t_end, t_comparison);//[mid,end)
    merge<Comparison>(t_begin, mid, t_end, t_comparison);
  }
}// namespace functor
}// namespace alex

namespace alex {
namespace polymorphism {
  struct Comparison
  {
    bool virtual operator()(const short lhs, const short rhs) = 0;
  };

  struct Lesser : Comparison
  {
    bool operator()(const short lhs, const short rhs) override { return lhs < rhs; }
  };

  struct Greater : Comparison
  {
    bool operator()(const short lhs, const short rhs) override { return lhs > rhs; }
  };

  void merge(std::vector<short>::iterator t_begin,
    std::vector<short>::iterator t_mid,
    std::vector<short>::iterator t_end,
    Comparison *t_comparison)
  {
    using it = typename std::vector<short>::iterator;
    auto copy = [](it t_t_begin, it t_t_end) -> std::vector<short> {
      std::vector<short> output;
      for (auto i = t_t_begin; i != t_t_end; ++i) { output.push_back(*i); }
      return output;
    };

    std::vector<short> leftArray = copy(t_begin, t_mid);
    std::vector<short> rightArray = copy(t_mid, t_end);

    auto left_begin = leftArray.begin();
    auto right_begin = rightArray.begin();

    while (left_begin != leftArray.end() && right_begin != rightArray.end()) {
      if ((*t_comparison)(*left_begin, *right_begin)) {
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

    copy_the_remaining_values(left_begin, leftArray);
    copy_the_remaining_values(right_begin, rightArray);
  }

  void merge_sort(std::vector<short>::iterator t_begin,
    typename std::vector<short>::iterator t_end,
    Comparison *t_comparison)
  {
    if (t_begin >= t_end - 1) { return; }// Returns recursively

    auto mid = t_begin + (t_end - t_begin) / 2;

    merge_sort(t_begin, mid, t_comparison);//[begin,mid)
    merge_sort(mid, t_end, t_comparison);//[mid,end)
    merge(t_begin, mid, t_end, t_comparison);
  }
}// namespace polymorphism
}// namespace alex

namespace alex {
namespace temp {

  struct Lesser
  {
    bool operator()(const short lhs, const short rhs) { return lhs < rhs; }
  };

  struct Greater
  {
    bool operator()(const short lhs, const short rhs) { return lhs > rhs; }
  };

  template<class Comparison>
  void merge(typename std::vector<short>::iterator t_begin,
    typename std::vector<short>::iterator t_mid,
    typename std::vector<short>::iterator t_end)
  {
    using it = typename std::vector<short>::iterator;
    auto copy = [](it t_t_begin, it t_t_end) -> std::vector<short> {
      std::vector<short> output;
      for (auto i = t_t_begin; i != t_t_end; ++i) { output.push_back(*i); }
      return output;
    };

    std::vector<short> leftArray = copy(t_begin, t_mid);
    std::vector<short> rightArray = copy(t_mid, t_end);

    auto left_begin = leftArray.begin();
    auto right_begin = rightArray.begin();

    while (left_begin != leftArray.end() && right_begin != rightArray.end()) {
      if (Comparison()(*left_begin, *right_begin)) {
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

    copy_the_remaining_values(left_begin, leftArray);
    copy_the_remaining_values(right_begin, rightArray);
  }

  template<class Comparison>
  void merge_sort(typename std::vector<short>::iterator t_begin, typename std::vector<short>::iterator t_end)
  {
    if (t_begin >= t_end - 1) { return; }// Returns recursively

    auto mid = t_begin + (t_end - t_begin) / 2;

    merge_sort<Comparison>(t_begin, mid);//[begin,mid)
    merge_sort<Comparison>(mid, t_end);//[mid,end)
    merge<Comparison>(t_begin, mid, t_end);
  }
}// namespace temp
}// namespace alex

namespace alex {
namespace inline_ {

  struct Lesser
  {
    bool inline operator()(const short lhs, const short rhs) { return lhs < rhs; }
  };

  struct Greater
  {
    bool inline operator()(const short lhs, const short rhs) { return lhs > rhs; }
  };

  template<class Comparison>
  inline void merge(typename std::vector<short>::iterator t_begin,
    typename std::vector<short>::iterator t_mid,
    typename std::vector<short>::iterator t_end)
  {
    using it = typename std::vector<short>::iterator;
    auto copy = [](it t_t_begin, it t_t_end) -> std::vector<short> {
      std::vector<short> output;
      for (auto i = t_t_begin; i != t_t_end; ++i) { output.push_back(*i); }
      return output;
    };

    std::vector<short> leftArray = copy(t_begin, t_mid);
    std::vector<short> rightArray = copy(t_mid, t_end);

    auto left_begin = leftArray.begin();
    auto right_begin = rightArray.begin();

    while (left_begin != leftArray.end() && right_begin != rightArray.end()) {
      if (Comparison()(*left_begin, *right_begin)) {
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

    copy_the_remaining_values(left_begin, leftArray);
    copy_the_remaining_values(right_begin, rightArray);
  }

  template<class Comparison>
  inline void merge_sort(typename std::vector<short>::iterator t_begin, typename std::vector<short>::iterator t_end)
  {
    if (t_begin >= t_end - 1) { return; }// Returns recursively

    auto mid = t_begin + (t_end - t_begin) / 2;

    merge_sort<Comparison>(t_begin, mid);//[begin,mid)
    merge_sort<Comparison>(mid, t_end);//[mid,end)
    merge<Comparison>(t_begin, mid, t_end);
  }
}// namespace inline_
}// namespace alex

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


/******************************************************************************
 * UTILS
 ******************************************************************************/
namespace utils {
// template<class T> std::istream &operator>>(std::istream &is, std::vector<T> &t_vector);
template<class T> std::istream &operator>>(std::istream &is, std::vector<T> &t_vector)
{
  typename std::vector<T>::size_type sz;// NOLINT initialization
  if (is >> sz) {
    // char comma;// NOLINT initialization
    t_vector.reserve(sz);
    char comma{};
    if (is >> comma) {
      while (sz > 0) {
        T elem;// NOLINT initialization
        if (is >> elem) { t_vector.push_back(elem); }
        if (is >> comma) { ; }
        --sz;
      }

      return is;
    }
  }

  is.setstate(std::ios_base::failbit);
  return is;
}
// template<class T>std::ostream &operator<<(std::ostream &os, std::vector<T> t_vector);
template<class T> std::ostream &operator<<(std::ostream &os, std::vector<T> t_vector)
{
  for (auto &&elem : t_vector) { os << elem << ", "; }
  return os;
}
template<class int_type> std::string int_type_and_data_size(const std::size_t t_data_size);
template<class Data_type> std::vector<Data_type> fill_vector_with_random_data(const std::size_t data_size);

}// namespace utils

template<class int_type> std::string utils::int_type_and_data_size(const std::size_t t_data_size)
{
  const std::string var_size = std::to_string(sizeof(int_type));
  const std::string data_size = std::to_string(t_data_size);

  return std::string{ var_size + "b-" + data_size + "b" };
}


template<class Data_type> std::vector<Data_type> utils::fill_vector_with_random_data(const std::size_t data_size)
{
  using utils::operator>>;
  const std::string directory_path{ "/home/marcus/+projects/Algorithms-and-Data-Structures/src/tests/data" };
  const std::string distribution{ "uniform_distribution" };
  const std::string prefix{ "/GD_" + distribution + "__" };
  // std::string var_size_and_data_size = int_type_and_data_size<Data_type>(data_size);

  // const std::string source{ directory_path + prefix + var_size_and_data_size + ".csv" };
  const std::string source{ directory_path + prefix + std::to_string(data_size) + ".csv" };
  std::ifstream ifs{ source };
  if (!ifs) { std::cerr << "couldn't open " << source << " for reading\n"; }
  if (std::vector<Data_type>().max_size() <= data_size) { std::cerr << "max_size reached"; }

  std::vector<Data_type> vec;
  // std::cout << "BEFORE" << std::endl;
  ifs >> vec;
  // std::cout << "AFTER" << std::endl;

  return vec;
}
/******************************************************************************
 * BENCHMARKING
 ******************************************************************************/
// #include "src/tests/utils/vector.hpp"

using Data_type = short;

// function to benchmark
void basic_sort_n_amount_of_data(const std::size_t data_size)
{
  std::vector<Data_type> A = utils::fill_vector_with_random_data<Data_type>(data_size);
  alex::basic::merge_sort(A.begin(), A.end());
}
void functor_sort_n_amount_of_data(const std::size_t data_size)
{
  std::vector<Data_type> A = utils::fill_vector_with_random_data<Data_type>(data_size);
  alex::functor::Lesser cmp;
  alex::functor::merge_sort(A.begin(), A.end(), cmp);
}
void polymorphism_sort_n_amount_of_data(const std::size_t data_size)
{
  std::vector<Data_type> A = utils::fill_vector_with_random_data<Data_type>(data_size);
  alex::polymorphism::Comparison *ptr;
  alex::polymorphism::Lesser l;
  ptr = &l;
  alex::polymorphism::merge_sort(A.begin(), A.end(), ptr);
}
void template_sort_n_amount_of_data(const std::size_t data_size)
{
  std::vector<Data_type> A = utils::fill_vector_with_random_data<Data_type>(data_size);
  alex::temp::merge_sort<alex::temp::Lesser>(A.begin(), A.end());
}
void inline_sort_n_amount_of_data(const std::size_t data_size)
{
  std::vector<Data_type> A = utils::fill_vector_with_random_data<Data_type>(data_size);
  alex::inline_::merge_sort<alex::inline_::Lesser>(A.begin(), A.end());
}
void function_ptr_sort_n_amount_of_data(const std::size_t data_size)
{
  std::vector<Data_type> A = utils::fill_vector_with_random_data<Data_type>(data_size);
  alex::function_ptr::merge_sort(A.begin(), A.end(), &alex::function_ptr::Lesser);
}

// A wrapper used by the framework
static void BM_basic_merge_sort(benchmark::State &state)
{
  for (auto &&_ : state) { basic_sort_n_amount_of_data(state.range(0)); }
}
static void BM_functor_merge_sort(benchmark::State &state)
{
  for (auto &&_ : state) { functor_sort_n_amount_of_data(state.range(0)); }
}
static void BM_polymorphism_merge_sort(benchmark::State &state)
{
  for (auto &&_ : state) { polymorphism_sort_n_amount_of_data(state.range(0)); }
}
static void BM_template_merge_sort(benchmark::State &state)
{
  for (auto &&_ : state) { template_sort_n_amount_of_data(state.range(0)); }
}
static void BM_inline_merge_sort(benchmark::State &state)
{
  for (auto &&_ : state) { inline_sort_n_amount_of_data(state.range(0)); }
}
static void BM_function_ptr_merge_sort(benchmark::State &state)
{
  for (auto &&_ : state) { function_ptr_sort_n_amount_of_data(state.range(0)); }
}


// #define BEGIN 500'000
// #define END 1'000'000
// #define STEP 50'000

BENCHMARK(BM_basic_merge_sort)->DenseRange(500000, 1000000, 50000);
BENCHMARK(BM_functor_merge_sort)->DenseRange(500000, 1000000, 50000);
BENCHMARK(BM_polymorphism_merge_sort)->DenseRange(500000, 1000000, 50000);
BENCHMARK(BM_template_merge_sort)->DenseRange(500000, 1000000, 50000);
BENCHMARK(BM_inline_merge_sort)->DenseRange(500000, 1000000, 50000);
BENCHMARK(BM_function_ptr_merge_sort)->DenseRange(500000, 1000000, 50000);

BENCHMARK_MAIN();
