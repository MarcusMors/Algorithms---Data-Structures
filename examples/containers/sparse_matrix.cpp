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

#include "../../containers/sparse_matrix.hpp"


int main()
{
  using namespace std;
  fstd::sparse_matrix<int, 3, 3> sparse_matrix;
  sparse_matrix(2, 2) = 3;
  cout << "sparce_matrix[2,2]\t: " << sparse_matrix(2, 2) << endl;


  // cout << "sparce_matrix[2,2]\t: " << sparse_matrix(2, 2) << endl;

  return 0;
}
