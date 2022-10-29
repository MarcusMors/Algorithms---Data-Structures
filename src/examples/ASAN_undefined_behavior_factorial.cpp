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

#include <cstdlib>

#include <iostream>

using namespace std;

int factorial(int n)
{
  int result = 1;
  while (n > 1) {
    result *= n;
    n--;
  }
  return result;
}

int main()
{
  int n = 13;
  std::cerr << "computing " << n << "!\n";
  std::cout << factorial(n) << "\n";
  return (std::cout) ? 0 : 1;
}
