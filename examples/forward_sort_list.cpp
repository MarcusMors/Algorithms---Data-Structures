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
#include "../containers/forward_sort_list.hpp"

using namespace std;

template<class T, class O> void insert_and_print(const vector<T> &in, O &out)
{
  for (const auto &elem : in) { out.insert(elem); }
  cout << out << endl;
}
template<class T, class O> void remove_and_print(const vector<T> &in, O &out)
{
  for (const auto &elem : in) { out.remove(elem); }
  cout << out << endl;
}

int main()
{
  fstd::forward_sort_list<int> list{ 1, 5, 17, 5, 12, 15, 20, 32, 32 };// NOLINT magic numbers
  // fstd::forward_sort_list<int> list{ 1, 2 };// NOLINT magic numbers

  // std::cout << "size\t: " << list.size() << '\n';
  std::cout << "list\t: " << list << std::endl;

  std::cout << "\niteration" << std::endl;
  for (auto i = list.begin(); i != list.end(); ++i) { std::cout << *i << ", "; }// NOLINT modern range for loop

  std::cout << "\n<--- MODIFIERS --->\n";
  vector<int> insert_numbers{ 10, 23, 14, 16, 2, 15, 10, 20 };// NOLINT magic numbers
  vector<int> remove_numbers{ 5, 1, 8, 10, 11, 14, 17, 20, 15 };// NOLINT magic numbers

  std::cout << "insert : ";
  for (const auto &elem : insert_numbers) { std::cout << elem << ", " << std::flush; }
  std::cout << "\n";

  insert_and_print(insert_numbers, list);

  std::cout << "\n";
  std::cout << "remove : ";
  for (const auto &elem : remove_numbers) { std::cout << elem << ", " << std::flush; }
  std::cout << "\n";
  remove_and_print(remove_numbers, list);


  return 0;
}
