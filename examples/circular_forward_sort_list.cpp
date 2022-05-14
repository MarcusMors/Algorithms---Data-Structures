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
#include <iostream>
#include <ranges>
// user defined libraries
#include "../containers/circular_forward_sort_list.hpp"

using namespace std;
using namespace fstd;

int main()
{
  fstd::circular_forward_sort_list<int> list{ 0, 1, 2, 3, 4, 5 };// NOLINT magic numbers

  std::cout << "size\t: " << list.size() << '\n';
  // std::cout << "list\t: " << list << std::endl;

  std::cout << "\nforward scripting" << std::endl;
  for (size_t i = 0; i < list.size(); ++i) { std::cout << "[" << i << "]" << list[i] << ", "; }

  std::cout << "\nbackward scripting" << std::endl;
  for (size_t i = list.size(); i > 0; --i) { std::cout << "[" << i - 1 << "]" << list[i - 1] << ", "; }

  // std::cout << "\niteration" << std::endl;
  // for (auto i = list.begin(); i != list.end(); ++i) { std::cout << i->value << ','; }// NOLINT modern range for loop

  std::cout << "<--- MODIFIERS --->\n";
  auto push_and_print = [&](auto val) {
    list.push(val);
    for (const auto &elem : list) { std::cout << elem << ','; }
    std::cout << "\n";
  };
  auto remove_and_print = [&](auto val) {
    list.remove(val);
    for (const auto &elem : list) { std::cout << elem << ','; }
    std::cout << "\n";
  };

  push_and_print(6);// NOLINT magic numbers
  push_and_print(7);// NOLINT magic numbers
  push_and_print(8);// NOLINT magic numbers
  push_and_print(9);// NOLINT magic numbers
  push_and_print(10);// NOLINT magic numbers
  push_and_print(11);// NOLINT magic numbers
  remove_and_print(9);// NOLINT magic numbers
  remove_and_print(8);// NOLINT magic numbers
  remove_and_print(3);// NOLINT magic numbers

  std::cout << "<--- MODIFIERS --->\n";
  push_and_print(6);// NOLINT magic numbers
  push_and_print(7);// NOLINT magic numbers
  push_and_print(8);// NOLINT magic numbers
  push_and_print(9);// NOLINT magic numbers
  push_and_print(10);// NOLINT magic numbers
  push_and_print(11);// NOLINT magic numbers
  remove_and_print(8);// NOLINT magic numbers
  remove_and_print(6);// NOLINT magic numbers
  remove_and_print(5);// NOLINT magic numbers

  return 0;
}
