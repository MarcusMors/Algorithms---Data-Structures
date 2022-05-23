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
#include <vector>
// user defined libraries
#include "../containers/circular_forward_sort_list.hpp"

template<class T, class O> void insert_and_print(const std::vector<T> &in, O &out)
{
  for (const auto &elem : in) { out.insert(elem); }
  std::cout << out << std::endl;
}
template<class T, class O> void remove_and_print(const std::vector<T> &in, O &out)
{
  for (const auto &elem : in) { out.remove(elem); }
  std::cout << out << std::endl;
}

int main()
{
  fstd::circular_forward_sort_list<int> list{ 10, 1, 6, 8, 3, 0, 14, 20, 21 };// NOLINT magic numbers

  std::cout << "list\t: " << list << std::endl;

  std::cout << "\niteration" << std::endl;
  for (auto it = list.begin(); it != list.end(); ++it) { std::cout << *it << ','; }// NOLINT modern range for loop

  std::cout << "\n<--- MODIFIERS --->\n";
  std::vector<int> insert_numbers{ 10, 23, 14, 16, 2, 15, 10, 20 };// NOLINT magic numbers
  std::vector<int> remove_numbers{ 5, 1, 8, 10, 11, 14, 17, 20, 15 };// NOLINT magic numbers

  std::cout << "\ninsert : ";
  for (const auto &elem : insert_numbers) { std::cout << elem << ", " << std::flush; }
  std::cout << "\n";

  insert_and_print(insert_numbers, list);

  std::cout << "\nremove : ";
  for (const auto &elem : remove_numbers) { std::cout << elem << ", " << std::flush; }
  std::cout << "\n";
  remove_and_print(remove_numbers, list);

  return 0;
}
