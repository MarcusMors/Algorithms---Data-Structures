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


#define CATCH_CONFIG_MAIN// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include "../catch.hpp"// unit testing library


// fake std
#include "../../algorithms/Merge_sort.hpp"
// #include "../containers/forward_list.hpp"
// original std
#include <array>
#include <iterator>
#include <list>
// CAPTURE to see the value of vars

template<class T> std::istream &operator>>(std::istream &is, std::vector<T> &t_vector)
{
  std::vector<int>::size_type sz;// NOLINT initialization
  if (is >> sz) {
    t_vector.reserve(sz);

    if (char comma; is >> comma) {
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

template<class T> std::ostream &operator<<(std::ostream &os, std::vector<T> t_vector)
{
  for (auto &&elem : t_vector) { os << elem << ", "; }
  return os;
}

template<class int_type> std::string int_type_and_data_size(const unsigned t_data_size)
{
  const std::string var_size = std::to_string(sizeof(int_type));
  const std::string data_size = std::to_string(t_data_size);

  return std::string{ var_size + "b-" + data_size + "b" };
}

template<class Container_a, class Container_b>
void check_value_equivalence(const Container_a &t_a, const Container_b &t_b)
{
  auto b_it{ t_b.begin() };
  for (auto a_it = t_a.begin(); a_it != t_a.end(); (++a_it, ++b_it)) { REQUIRE(*a_it == *b_it); }
}

template<class T> std::vector<T> rand_vector(const unsigned t_size)
{
  using intType = short;
  using Seed = std::random_device;
  using Engine = std::default_random_engine;
  using Distribution = std::uniform_int_distribution<intType>;

  Seed seed;
  Engine engine{ seed() };
  const intType max = std::numeric_limits<intType>::max();
  const intType min = std::numeric_limits<intType>::min();
  Distribution distribution(min, max);
  auto generate_random_number = [&]() { return distribution(engine); };

  std::vector<T> vec;
  vec.reserve(t_size);

  for (unsigned i = 0; i < t_size; i++) { vec.push_back(generate_random_number()); }

  return vec;
}


TEST_CASE("merge_sort")
{
  using int_type = short;
  using it_type = std::vector<int_type>::iterator;

  SECTION("Make sure this sorts")
  {
    const unsigned size = 100;
    std::vector<int_type> test_vec{ rand_vector<int_type>(size) };
    std::vector<int_type> sorted_vec{ rand_vector<int_type>(size) };

    fstd::Merge_sort<int_type, it_type> merge_sort;
    merge_sort(test_vec.begin(), test_vec.end(), 1);
    std::sort(sorted_vec.begin(), sorted_vec.end());
    check_value_equivalence(test_vec, test_vec);
  }


  std::string directory_path{ "/home/marcus/+projects/Algorithms-and-Data-Structures/data" };
  std::string distribution{ "uniform_distribution" };
  std::string prefix{ "/GD_" + distribution + "__" };


  for (unsigned data_size = 1; data_size < 10; data_size++) {
    const std::string var_size_and_data_size = int_type_and_data_size<int_type>(data_size);

    const std::string source{ directory_path + prefix + var_size_and_data_size + ".csv" };

    std::ifstream ifs{ source };

    if (!ifs) { std::cerr << "couldn't open '" << source << "' for reading\n"; }

    std::vector<int_type> performance_vector;
    ifs >> performance_vector;

    fstd::Merge_sort<int_type, it_type> merge_sort;
    auto numCPU{ std::thread::hardware_concurrency() };

    // const std::string benchmark_name{ "Merge_sort " + std::to_string(data_size) };

    // BENCHMARK("Single Merge_sort")
    //{
    //   return merge_sort.single_thread_merge_sort(performance_vector.begin(), performance_vector.end());
    // };
    BENCHMARK("Multi Merge_sort") { return merge_sort(performance_vector.begin(), performance_vector.end(), numCPU); };
  }
}
