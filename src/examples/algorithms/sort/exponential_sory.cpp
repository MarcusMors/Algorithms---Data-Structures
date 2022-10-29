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

// #include "src/algorithms/merge_sort.hpp"
// #include "../src/algorithms/sort/merge_sort.hpp"
// #include "merge_sort.hpp"
// #include "../../algorithms/sort/merge_sort.hpp"

#include <iostream>


int main()
{
  using data_type = short;
  //
  std::vector<data_type> A{ 10, 1, 7, 3, 6, 5 };
  // fstd::merge_sort(A.begin(), A.end());
  fstd::merge_sort(A.begin(), A.end());

  for (auto &&elem : A) { std::cout << elem << ", "; }
  std::cout << std::endl;

  return 0;
}
