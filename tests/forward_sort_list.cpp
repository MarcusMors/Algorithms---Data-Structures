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

#include "catch.hpp"// unit testing library
// fake std
#include "../containers/forward_sort_list.hpp"
// #include "../data/"
// original std
#include <algorithm>
#include <forward_list>
#include <iterator>
#include <vector>

template<class container_a, class container_b>
inline void check_value_equivalence(const container_a &a, const container_b &b)
{
  auto b_it{ b.begin() };
  for (auto a_it{ a.begin() }; a_it != a.end(); (++a_it, ++b_it)) { CHECK(*a_it == *b_it); }
}

TEST_CASE("forward sort list")
{
  // INFO("Testing list initialization");
  // initialization
  const std::initializer_list<int> ascendant_init{ -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5 };// NOLINT magic number
  SECTION("sorted initialization") { fstd::forward_sort_list<int> fstd_list{ ascendant_init }; }
  SECTION("simple random initialization")
  {
    const std::initializer_list<int> random_init{ 311449302,
      1499859198,
      1773212879,
      -1594163627,
      1780710798,
      185082726,
      1709742834,
      -1991572013,
      -547130622,
      2056519241,
      -795392717,
      -1429580941,
      670679191,
      1731757949,
      1300128375,
      -1837639644,
      -496197830,
      479826780,
      -584822073,
      2113349766,
      -1391051697,
      -328784696,
      1551533513,
      -435825118,
      -1666187149,
      -1713234813,
      840062404,
      1973546690,
      171312327,
      -526963543,
      -347740478,
      2016719531 };

    std::vector<int> random_vector_init{ random_init };
    std::sort(random_vector_init.begin(), random_vector_init.end());
    auto random_vector_it = std::unique(random_vector_init.begin(), random_vector_init.end());
    random_vector_init.erase(random_vector_it, random_vector_init.end());
    fstd::forward_sort_list<int> fstd_list{ random_init };
    check_value_equivalence(fstd_list, random_vector_init);
  }
  // SECTION("absolute random initialization")
  // {
  //   const std::initializer_list<int> sorted_init{ -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5 };
  //   fstd::forward_sort_list<int> fstd_list{ sorted_init };
  // }
  const std::initializer_list<int> descendant_init{ 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5 };
  SECTION("worst case sorted initialization")
  {
    fstd::forward_sort_list<int> fstd_list{ descendant_init };
    std::vector<int> descendant_vector{ descendant_init };
    check_value_equivalence(fstd_list, ascendant_init);
  }

  const std::initializer_list<int> int_vector{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  // const auto *int_init_begin{ int_vector.begin() };
  const auto *int_init_begin{ int_vector.begin() };

  // auto int_init_end{ int_vector.end() };
  fstd::forward_sort_list<int> fstd_list{ int_vector };

  /*==========================================================================
    ELEMENT ACCESS
    ==========================================================================*/
  // INFO("Testing Element Access");
  SECTION("element access") { CHECK(fstd_list.front() == *(int_vector.begin())); }
  /*==========================================================================
    SCRIPTING and ITERATORS
    ==========================================================================*/
  // INFO("Testing iterators");
  SECTION("iteration")
  {
    // INFO("\niterator");
    for (auto it = fstd_list.begin(); it != fstd_list.end(); (++it, ++int_init_begin)) {
      REQUIRE(*it == *(int_init_begin));
    }
  }
  SECTION("range-based-for loop")
  {
    for (const auto &elem : fstd_list) {
      CHECK(elem == *(int_init_begin));
      ++int_init_begin;
    }
  }
  /*==========================================================================
    CAPACITY
    ==========================================================================*/
  // INFO("Testing capacity");
  SECTION("size") { CHECK(fstd_list.size() == int_vector.size()); }
  SECTION("empty")
  {
    fstd::forward_sort_list<int> empty_list{};
    CHECK(empty_list.empty());
    CHECK_FALSE(fstd_list.empty());
  }

  /*==========================================================================
    MODIFIERS
    ==========================================================================*/
  SECTION("insert")
  {
    std::vector<int> numbers{ -1, -2, -3, -4, -5, -6 };// NOLINT magic number
    for (auto num : numbers) { fstd_list.insert(num); }

    // check_value_equivalence(fstd_list, std_list);
  }
  SECTION("remove")
  {
    std::vector<int> numbers{ -1, -2, -3, -4, -5, -6 };// NOLINT magic number
    for (auto num : numbers) { fstd_list.remove(num); }

    // check_value_equivalence(fstd_list, std_list);
  }
}
