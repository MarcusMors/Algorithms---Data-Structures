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
// user defined libraries
#include "../STD-containers/list.hpp"
using namespace std;
using namespace fstd;

int main()
{
  fstd::list<int> list{ 0, 1, 2, 3, 4, 5 };

  std::cout << "size\t: " << list.size() << '\n';
  std::cout << "list\t: " << list << std::endl;

  std::cout << "\nforward scripting" << std::endl;
  for (size_t i = 0; i < list.size(); ++i) { std::cout << "[" << i << "]" << list[i] << ", "; }

  std::cout << "\nbackward scripting" << std::endl;
  for (size_t i = list.size(); i > 0; --i) { std::cout << "[" << i - 1 << "]" << list[i - 1] << ", "; }

  std::cout << "\nforward iteration" << std::endl;
  for (auto i = list.begin(); i; ++i) { std::cout << i->value << ','; }

  std::cout << "\nbackward iteration" << std::endl;
  for (auto i = list.end(); i; --i) { std::cout << i->value << ','; }

  std::cout << "\nrange based loop" << std::endl;
  for (const auto &elem : list) { std::cout << elem << ','; }

  std::cout << "\n";

  return 0;
}
