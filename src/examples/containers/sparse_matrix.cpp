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

// user made libs
#include "../../containers/sparse_matrix.hpp"


// using namespace std;
// using namespace fstd;

int main()
{
  fstd::sparse_matrix<int, 3, 3> sparse_matrix{};

  std::cout << "\nSingle Reference case\n";
  std::cout << "sparse_matrix[2,2]\t: " << sparse_matrix(2, 2) << std::endl;

  std::cout << "\nCasting case\n";
  int A{ sparse_matrix(2, 2) };
  std::cout << "A: " << A << std::endl;

  std::cout << "\nAssignment case\n";
  sparse_matrix(2, 2) = 3;
  std::cout << "sparse_matrix[2,2]\t: " << sparse_matrix(2, 2) << std::endl;

  std::cout << "\nRemove case\n";
  sparse_matrix(2, 2) = 0;
  std::cout << "sparse_matrix[2,2]\t: " << sparse_matrix(2, 2) << std::endl;

  return 0;
}
