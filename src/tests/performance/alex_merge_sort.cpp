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

#include "src/alex/basic_merge_sort.hpp"
#include "src/alex/functor_merge_sort.hpp"
#include "src/alex/polymorphism_merge_sort.hpp"
#include "src/alex/template_merge_sort.hpp"
#include "src/tests/utils/vector.hpp"
#include <benchmark/benchmark.h>
#include <string>

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
void temp_sort_n_amount_of_data(const std::size_t data_size)
{
  std::vector<Data_type> A = utils::fill_vector_with_random_data<Data_type>(data_size);
  alex::temp::merge_sort<alex::temp::Lesser>(A.begin(), A.end());
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
  for (auto &&_ : state) { temp_sort_n_amount_of_data(state.range(0)); }
}

BENCHMARK(BM_basic_merge_sort)
  ->Arg(500000)
  ->Arg(550000)
  ->Arg(600000)
  ->Arg(650000)
  ->Arg(700000)
  ->Arg(750000)
  ->Arg(800000)
  ->Arg(850000)
  ->Arg(900000)
  ->Arg(950000)
  ->Arg(1000000);

BENCHMARK(BM_functor_merge_sort)
  ->Arg(500000)
  ->Arg(550000)
  ->Arg(600000)
  ->Arg(650000)
  ->Arg(700000)
  ->Arg(750000)
  ->Arg(800000)
  ->Arg(850000)
  ->Arg(900000)
  ->Arg(950000)
  ->Arg(1000000);
BENCHMARK(BM_polymorphism_merge_sort)
  ->Arg(500000)
  ->Arg(550000)
  ->Arg(600000)
  ->Arg(650000)
  ->Arg(700000)
  ->Arg(750000)
  ->Arg(800000)
  ->Arg(850000)
  ->Arg(900000)
  ->Arg(950000)
  ->Arg(1000000);
BENCHMARK(BM_template_merge_sort)
  ->Arg(500000)
  ->Arg(550000)
  ->Arg(600000)
  ->Arg(650000)
  ->Arg(700000)
  ->Arg(750000)
  ->Arg(800000)
  ->Arg(850000)
  ->Arg(900000)
  ->Arg(950000)
  ->Arg(1000000);

BENCHMARK_MAIN();
