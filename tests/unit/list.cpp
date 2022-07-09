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
#include "../../containers/list.hpp"
// #include "../containers/forward_list.hpp"
// original std
#include <array>
#include <iterator>
#include <list>
// CAPTURE to see the value of vars

template<class container_a, class container_b>
void check_value_equivalence(const container_a &t_a, const container_b &t_b)
{
  auto b_it{ t_b.begin() };
  for (auto a_it{ t_a.begin() }; a_it != t_a.end(); (++a_it, ++b_it)) { REQUIRE(*a_it == *b_it); }
}

// REQUIRE_THROWS_AS( expression, exception type )
// CHECK_THROWS_AS( expression, exception type )
// TEST_CASE("lists are containers")
TEST_CASE("list")
{
  // INFO("Testing list initialization");
  // initialization
  const std::initializer_list<int> int_init{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  auto int_init_begin{ int_init.begin() };
  auto int_init_end{ int_init.end() };
  std::list<int> std_list{ int_init };
  fstd::list<int> fstd_list{ int_init };

  /*==========================================================================
    ELEMENT ACCESS
    ==========================================================================*/
  INFO("Testing Element Access");
  SECTION("element access")
  {
    CHECK(fstd_list.front() == std_list.front());
    CHECK(fstd_list.front() == *(int_init.begin()));
    CHECK(fstd_list.back() == std_list.back());
    CHECK(fstd_list.back() == *(int_init.end() - 1));
  }
  /*==========================================================================
    SCRIPTING and ITERATORS
    ==========================================================================*/
  INFO("Testing iterators");
  SECTION("iteration")
  {
    INFO("\niterator");
    for (auto it = fstd_list.begin(); it != fstd_list.end(); (++it, ++int_init_begin)) {
      REQUIRE(*it == *(int_init_begin));
    }
  }
  SECTION("reverse iteration")
  {
    for (auto it = fstd_list.rbegin(); it != fstd_list.rend(); --it) {
      --int_init_end;
      CHECK(*it == *(int_init_end));
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
  INFO("Testing capacity");
  SECTION("size")
  {
    CHECK(fstd_list.size() == std_list.size());
    CHECK(fstd_list.size() == int_init.size());
  }
  SECTION("empty")
  {
    fstd::list<int> fstd_empty_list{};
    std::list<int> std_empty_list{};
    CHECK(fstd_empty_list.empty());
    CHECK(fstd_empty_list.empty() == std_empty_list.empty());
    CHECK(fstd_list.empty() == std_list.empty());
    CHECK(fstd_list.empty() == false);
  }

  /*==========================================================================
    MODIFIERS
    ==========================================================================*/
  SECTION("push_back")
  {
    std::array<int, 6> numbers{ 10, 11, 12, 13, 14, 15 };// NOLINT magic number
    for (auto num : numbers) {
      fstd_list.push_back(num);
      std_list.push_back(num);
    }

    check_value_equivalence(fstd_list, std_list);
  }
  SECTION("pop_back")
  {
    const std::size_t n_pop{ 3 };// NOLINT magic number
    for (std::size_t i = 0; i < n_pop; i++) {
      fstd_list.pop_back();
      std_list.pop_back();
    }

    check_value_equivalence(fstd_list, std_list);
  }
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
  SECTION("resizing bigger change size, creating nodes")
  {
    const std::list<int>::size_type new_size{ 15 };// NOLINT magic numbers
    fstd::list<int> resizable_fstd_list{ int_init };
    std::list<int> resizable_std_list{ int_init };
    resizable_fstd_list.resize(new_size);
    resizable_std_list.resize(new_size);
    CHECK(resizable_fstd_list.size() == resizable_std_list.size());
    CHECK(resizable_std_list.size() == new_size);

    check_value_equivalence(resizable_fstd_list, resizable_std_list);
  }
  SECTION("resizing smaller change size, deleting nodes")
  {
    const std::list<int>::size_type new_size{ 3 };// NOLINT magic numbers
    fstd::list<int> resizable_fstd_list{ int_init };
    std::list<int> resizable_std_list{ int_init };
    resizable_fstd_list.resize(new_size);
    resizable_std_list.resize(new_size);
    CHECK(resizable_fstd_list.size() == resizable_std_list.size());
    CHECK(resizable_std_list.size() == new_size);

    check_value_equivalence(resizable_fstd_list, resizable_std_list);
  }
  // SECTION("swap")
  // {
  //   const std::initializer_list<int> INT_SWAP_INIT{ 10, 11, 12, 13, 14, 15 };// NOLINT
  //   fstd::list<int> fstd_swap_list{ INT_SWAP_INIT };
  //   std::list<int> std_swap_list{ INT_SWAP_INIT };
  //   fstd_list.swap(fstd_swap_list);
  //   std_list.swap(std_swap_list);

  //   bool swapped{ true };
  //   const auto *const int_init_IT{ int_init.begin() };
  //   std::list<int>::size_type i{ 0 };// NOLINT magic numbers
  //   for (auto it = fstd_list.begin(); it != fstd_list.end(); ++it) {// NOLINT loop
  //     if (it->value != *(int_init_IT + i)) { swapped = false; }// NOLINT pointer arithmetic
  //     ++i;
  //   }
  //   CHECK(swapped);
  // }
}
