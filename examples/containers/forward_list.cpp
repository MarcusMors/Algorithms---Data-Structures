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
#include "../../containers/forward_list.hpp"

using namespace std;
using namespace fstd;

template<class T, class O> void push_and_print(const vector<T> &in, O &out)
{
  for (const auto &elem : in) { out.push_front(elem); }
  cout << out << endl;
}
template<class T, class O> void pop_and_print(const T &times, O &out)
{
  for (T i = 0; i < times; ++i) { out.pop_front(); }
  cout << out << endl;
}

int main()
{
  fstd::forward_list<int> list{ 6, 7, 8, 9 };// NOLINT magic numbers
  // fstd::forward_list<char> list{ 'a' };// NOLINT magic numbers
  // fstd::forward_list<int> list{ 1 };// NOLINT magic numbers

  // std::cout << "size\t: " << list.size() << '\n';
  std::cout << "list\t\t: " << list << "\n";
  std::cout << "iteration\t: ";
  for (auto it = list.begin(); it != list.end(); ++it) { std::cout << *it << ", "; }// NOLINT modern range for loop

  std::cout << "\n<--- MODIFIERS --->\n";
  // vector<int> numbers{ 5, 4, 3, 2, 1, 0 };// NOLINT magic numbers

  const std::size_t new_size{ 2 };// NOLINT magic numbers
  std::cout << "size : " << list.size() << "\tnew size : " << new_size << std::endl;
  list.resize(new_size);
  for (const auto &elem : list) { std::cout << elem << ", " << std::flush; }
  std::cout << std::endl;

  // std::cout << list << std::endl;
  // push_and_print(numbers, list);

  // int pop_front_times{ 5 };// NOLINT magic numbers
  // pop_and_print(pop_front_times, list);
  // resize


  return 0;
}
