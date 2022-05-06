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
#include "../containers/list.hpp"
// original std
#include <array>
#include <iterator>
#include <list>

// TEST_CASE("lists are containers")
TEST_CASE("lists can be initialized and resized")
{
  // initialization
  const std::initializer_list<int> int_init{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  std::list<int> std_list{ int_init };
  fstd::list<int> fstd_list{ int_init };
  // auto int_init_begin_it{ int_init.begin() };
  // auto int_init_end_it{ int_init.end() };

  /*==========================================================================
    ELEMENT ACCESS
    ==========================================================================*/
  SECTION("element access")
  {
    REQUIRE(fstd_list.front() == std_list.front());
    REQUIRE(fstd_list.front() == *(int_init.begin()));
    REQUIRE(fstd_list.back() == std_list.back());
    REQUIRE(fstd_list.back() == *(int_init.end() - 1));
  }
  /*==========================================================================
    SCRIPTING and ITERATORS
    ==========================================================================*/
  SECTION("forward subscripting")
  {
    const auto *const int_init_BEGIN{ int_init.begin() };
    for (size_t i = 0; i < fstd_list.size(); ++i) {
      const auto fstd_list_i = fstd_list[i];
      const auto std_list_i = *(int_init_BEGIN + i);// NOLINT pointer arithmetic
      REQUIRE(fstd_list_i == std_list_i);
    }
  }
  SECTION("backward scripting")
  {
    const auto *const int_init_BEGIN{ int_init.begin() };
    for (int i = fstd_list.size() - 1; i >= 0; --i) {// NOLINT
      const auto fstd_list_i = fstd_list[i];
      const auto std_list_i = *(int_init_BEGIN + i);// NOLINT pointer arithmetic
      REQUIRE(fstd_list_i == std_list_i);
    }
  }
  SECTION("iteration")
  {
    std::list<int>::size_type i{ 0 };// NOLINT magic numbers
    const auto *const int_init_IT{ int_init.begin() };
    for (auto it = fstd_list.begin(); it != fstd_list.end(); ++it) {// NOLINT modern range for loop
      REQUIRE(*it == *(int_init_IT + i));// NOLINT pointer arithmetic
      ++i;
    }
  }
  SECTION("reverse iteration")
  {
    std::list<int>::size_type i{ 1 };// NOLINT magic numbers
    const auto *const int_init_IT{ int_init.end() };
    for (auto it = fstd_list.rbegin(); it != fstd_list.rend(); --it) {
      REQUIRE(*it == *(int_init_IT - i));// NOLINT pointer arithmetic
      ++i;
    }
  }

  SECTION("range-based-for loop")
  {
    std::list<int>::size_type i{ 0 };// NOLINT magic numbers
    const auto *const int_init_IT{ int_init.begin() };
    for (const auto &elem : fstd_list) {
      REQUIRE(elem == *(int_init_IT + i));// NOLINT pointer arithmetic
      ++i;
    }
  }
  /*==========================================================================
    CAPACITY
    ==========================================================================*/
  SECTION("size")
  {
    REQUIRE(fstd_list.size() == std_list.size());
    REQUIRE(fstd_list.size() == int_init.size());
  }
  SECTION("empty")
  {
    fstd::list<int> fstd_empty_list{};
    fstd::list<int> std_empty_list{};
    REQUIRE(fstd_empty_list.empty());
    REQUIRE(fstd_empty_list.empty() == std_empty_list.empty());
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

    auto STD_LIST_IT{ std_list.begin() };
    for (auto it = fstd_list.begin(); it != fstd_list.end(); (++it, ++STD_LIST_IT)) { REQUIRE(*it == *STD_LIST_IT); }
  }
  SECTION("pop_back")
  {
    const std::size_t n_pop{ 3 };// NOLINT magic number
    for (std::size_t i = 0; i < n_pop; i++) {
      fstd_list.pop_back();
      std_list.pop_back();
    }

    auto STD_LIST_IT{ std_list.begin() };
    for (auto it{ fstd_list.begin() }; it != fstd_list.end(); (++it, ++STD_LIST_IT)) { REQUIRE(*it == *(STD_LIST_IT)); }
  }
  SECTION("push_front")
  {
    std::array<int, 6> numbers{ -1, -2, -3, -4, -5, -6 };// NOLINT magic number
    for (auto num : numbers) {
      fstd_list.push_front(num);
      std_list.push_front(num);
    }

    auto STD_LIST_IT{ std_list.begin() };
    for (auto it{ fstd_list.begin() }; it != fstd_list.end(); ++it, ++STD_LIST_IT) { REQUIRE(*it == *STD_LIST_IT); }
  }
  SECTION("pop_front")
  {
    const std::size_t n_pop{ 3 };// NOLINT magic number
    for (std::size_t i = 0; i < n_pop; i++) {
      fstd_list.pop_front();
      std_list.pop_front();
    }

    auto STD_LIST_IT{ std_list.begin() };
    for (auto it{ fstd_list.begin() }; it != fstd_list.end(); (++it, ++STD_LIST_IT)) { REQUIRE(*it == *STD_LIST_IT); }
  }
  SECTION("resizing bigger change size")
  {
    const std::list<int>::size_type new_size{ 15 };// NOLINT magic numbers
    std_list.resize(new_size);
    fstd_list.resize(new_size);
    REQUIRE(fstd_list.size() == std_list.size());
    REQUIRE(fstd_list.size() == new_size);
  }
  SECTION("resizing smaller change size")
  {
    const std::list<int>::size_type new_size{ 3 };// NOLINT magic numbers
    std_list.resize(new_size);
    fstd_list.resize(new_size);
    REQUIRE(fstd_list.size() == std_list.size());
    REQUIRE(fstd_list.size() == new_size);
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
  //   REQUIRE(swapped);
  // }
}
