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

#include "../containers/list.hpp"
#include <array>
#include <iostream>
#include <iterator>
#include <list>


int main()
{
  const std::initializer_list<int> int_init{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  // auto int_init_begin{ int_init.begin() };
  // auto int_init_end{ int_init.end() };
  std::list<int> std_list{ int_init };
  fstd::list<int> fstd_list{ int_init };

  const std::list<int>::size_type new_size{ 15 };// NOLINT magic numbers
  std_list.resize(new_size);
  fstd_list.resize(new_size);
  if (fstd_list.size() == std_list.size()) {//
    // std::cout << "TRUEEEEEEEE" << std::endl;
    ;
  }
  if (fstd_list.size() == new_size) {//
    // std::cout << "TRUEEEEEEEE" << std::endl;
    ;
  }
  std::cout << "TRUEEEEEEEE" << std::endl;

  return 0;
}
