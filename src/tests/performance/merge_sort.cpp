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

#include "../utils/utility.hpp"
#include <gtest/gtest.h>

using std::vector;
using namespace utils;

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions)
{
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

// int main()
// {
//   using int_type = int;
//   // const int data_size = 4;
//   // std::vector<int_type> vec = utils::fill_vector_with_random_data<int_type>(data_size);
//   std::vector<int_type> vec{ 12, 11, 13, 5, 6, 7 };// NOLINT magic number
//   // std::vector<int_type> vec{ 12, 11, 13 };// NOLINT magic number
//   // std::vector<int_type> vec{ 12, 11 };// NOLINT magic number

//   std::cout << "Given vec is \n" << vec << "\n";

//   fstd::merge_sort(vec.begin(), vec.end());

//   cout << "\nSorted vec is \n" << vec << "\n";
//   return 0;
// }
