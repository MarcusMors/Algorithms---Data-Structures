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

#include "../catch.hpp"// unit testing library
// fake std
#include "../../containers/forward_list.hpp"
// original std
#include <array>
#include <cassert>
#include <forward_list>
#include <iterator>

template<class container_a, class container_b>
inline void check_value_equivalence(const container_a &t_a, const container_b &t_b)
{
  auto b_it{ t_b.begin() };
  for (auto a_it{ t_a.begin() }; a_it != t_a.end(); (++a_it, ++b_it)) { CHECK(*a_it == *b_it); }
}

TEST_CASE("forward list")
{
  // INFO("Testing list initialization");
  // initialization
  const std::initializer_list<int> int_init{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  // const auto *int_init_begin{ int_init.begin() };
  const auto *int_init_begin{ int_init.begin() };
  const auto int_init_size{ int_init.size() };

  // auto int_init_end{ int_init.end() };
  std::forward_list<int> std_list{ int_init };
  fstd::forward_list<int> fstd_list{ int_init };

  /*==========================================================================
    ELEMENT ACCESS
    ==========================================================================*/
  // INFO("Testing Element Access");
  SECTION("element access")
  {
    CHECK(fstd_list.front() == std_list.front());
    CHECK(fstd_list.front() == *(int_init.begin()));
  }
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
  SECTION("size") { CHECK(fstd_list.size() == int_init.size()); }
  SECTION("empty")
  {
    fstd::forward_list<int> fstd_empty_list{};
    std::forward_list<int> std_empty_list{};
    CHECK(fstd_empty_list.empty());
    CHECK(fstd_empty_list.empty() == std_empty_list.empty());
    CHECK(fstd_list.empty() == std_list.empty());
    CHECK_FALSE(fstd_list.empty());
  }

  /*==========================================================================
    MODIFIERS
    ==========================================================================*/
  SECTION("push_front")
  {
    std::vector<int> numbers{ -1, -2, -3, -4, -5, -6 };// NOLINT magic number
    for (auto num : numbers) {
      fstd_list.push_front(num);
      std_list.push_front(num);
    }

    check_value_equivalence(fstd_list, std_list);
  }
  SECTION("pop_front")
  {
    const std::size_t n_pop{ 3 };// NOLINT magic number
    for (std::size_t i = 0; i < n_pop; i++) {
      fstd_list.pop_front();
      std_list.pop_front();
    }

    check_value_equivalence(fstd_list, std_list);
  }
  SECTION("resizing no change")
  {
    const std::forward_list<int>::size_type new_size{ int_init.size() };// NOLINT magic numbers
    REQUIRE(new_size == int_init_size);//"new size must be equal to actual size"
    fstd::forward_list<int> resizable_fstd_list{ int_init };
    std::forward_list<int> resizable_std_list{ int_init };
    resizable_fstd_list.resize(new_size);
    resizable_std_list.resize(new_size);
    CHECK(resizable_fstd_list.size() == new_size);
    check_value_equivalence(resizable_fstd_list, resizable_std_list);
  }
  SECTION("resizing bigger change size, creating nodes")
  {
    const std::size_t new_size{ int_init.size() + 5 };// NOLINT magic numbers
    REQUIRE(new_size > int_init_size);//"new size must be bigger to actual size"
    fstd::forward_list<int> resizable_fstd_list{ int_init };
    std::forward_list<int> resizable_std_list{ int_init };
    resizable_fstd_list.resize(new_size);
    resizable_std_list.resize(new_size);
    CHECK(resizable_fstd_list.size() == new_size);
    check_value_equivalence(resizable_fstd_list, resizable_std_list);
  }
  SECTION("resizing smaller change size, deleting nodes")
  {
    const std::forward_list<int>::size_type new_size{ 3 };// NOLINT magic numbers
    REQUIRE(new_size < int_init.size());//"new size must be smaller to actual size"
    fstd::forward_list<int> resizable_fstd_list{ int_init };
    std::forward_list<int> resizable_std_list{ int_init };
    resizable_fstd_list.resize(new_size);
    resizable_std_list.resize(new_size);
    CHECK(resizable_fstd_list.size() == new_size);
    check_value_equivalence(resizable_fstd_list, resizable_std_list);
  }
}
