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
#include "../../containers/binary_search_tree.hpp"

template<class T, class O> void insert_and_print(const std::vector<T> &in, O &out)
{
  for (const auto &elem : in) { out.insert(elem); }
  // std::cout << out << std::endl;
  out.in_order_traversal();
}
template<class T, class O> void remove_and_print(const std::vector<T> &in, O &out)
{
  for (const auto &elem : in) { out.remove(elem); }
  // std::cout << out << std::endl;
  out.in_order_traversal();
}

int main()
{
  fstd::bin_search_tree<int> BST{ 0 };
  // BST.in_order_traversal();
  BST.insert(1);
  BST.in_order_traversal();
  // // fstd::bin_search_tree<int> BST{ 10, 1, 6, 8, 3, 0, 14, 20, 21 };// NOLINT magic numbers

  // // std::cout << "BST\t: " << BST << std::endl;

  // std::cout << "\n<--- MODIFIERS --->\n";
  // std::vector<int> insert_numbers{ 10, 23, 14, 16, 2, 15, 10, 20 };// NOLINT magic numbers
  // std::vector<int> remove_numbers{ 5, 1, 8, 10, 11, 14, 17, 20, 15 };// NOLINT magic numbers

  // std::cout << "\ninsert : ";
  // for (const auto &elem : insert_numbers) { std::cout << elem << ", " << std::flush; }
  // std::cout << "\n";

  // insert_and_print(insert_numbers, BST);

  // std::cout << "\nremove : ";
  // for (const auto &elem : remove_numbers) { std::cout << elem << ", " << std::flush; }
  // std::cout << "\n";
  // remove_and_print(remove_numbers, BST);

  // return 0;
}
