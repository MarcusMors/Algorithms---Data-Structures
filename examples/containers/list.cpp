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
#include <vector>
// user defined libraries
#include "../../containers/list.hpp"

using namespace std;
using namespace fstd;

template<class T, class O> void push_back_and_print(const vector<T> &in, O &out)
{
  for (const auto &elem : in) { out.push_back(elem); }
  cout << out << endl;
}
template<class T, class O> void pop_back_and_print(const T &times, O &out)
{
  for (T i = 0; i < times; ++i) { out.pop_back(); }
  cout << out << endl;
}

int main()
{
  fstd::list<int> list{ 0, 1, 2, 3, 4, 5 };// NOLINT magic numbers

  std::cout << "size\t\t: " << list.size() << '\n';
  std::cout << "list\t\t: " << list << "\n";

  std::cout << "iteration\t: ";
  for (auto i = list.begin(); i != list.end(); ++i) { std::cout << i->value << ", "; }// NOLINT modern range for loop

  std::cout << "\nreverse iteration\t: ";
  for (auto i = list.rbegin(); i != list.rend(); --i) { std::cout << i->value << ", "; }

  cout << "\nforward iteration\t: ";
  for (auto i = list.begin(); i != list.end(); i = i->next) { cout << i->value << ", "; }

  std::cout << "\n<--- MODIFIERS --->";
  std::vector<int> input_numbers{ 6, 7, 8, 9, 10, 11 };// NOLINT magic numbers
  unsigned pop_back_times{ 6 };// NOLINT magic numbers

  // std::vector<int> remove_numbers{  };// NOLINT magic numbers

  std::cout << "\npush_back\t: ";
  for (auto &&elem : input_numbers) { std::cout << elem << ", " << std::flush; }
  std::cout << "\n";

  push_back_and_print(input_numbers, list);

  std::cout << "\npop_back_times\t: " << pop_back_times << "\n";
  pop_back_and_print(pop_back_times, list);

  std::cout << "\n";
  return 0;
}
