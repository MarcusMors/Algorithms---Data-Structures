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

#include "../../containers/deque.hpp"

using namespace std;


int main(int argc, char *argv[])
// int main()
{
  if (argc != 2) {
    std::cout << "Usage: deque_example <choice>" << std::endl;
    return -1;
  }
  int test_case = std::stoi(argv[1]);
  // int test_case = 0;

  switch (test_case) {
  case 0: {
    cout << "single page, no overload" << endl;
    fstd::deque<int> d{ 0, 1, 2, 3, 4 };
    for (size_t i = 0; i < d.size(); i++) { cout << d[i] << ","; }
    cout << endl;
    break;
  }
  case 1: {
    cout << "single page, both overload" << endl;
    fstd::deque<int> d{ 4, 0, 1, 2, 3, 4, 0 };
    for (size_t i = 0; i < d.size(); i++) { cout << d[i] << ","; }
    cout << endl;
    break;
  }
  case 2: {
    cout << "single page, right overload" << endl;
    fstd::deque<int> d{ 0, 1, 2, 3, 4, 5 };
    for (size_t i = 0; i < d.size(); i++) { cout << d[i] << ","; }
    cout << endl;
    break;
  }
  case 3: {
    cout << "single page, right overload quotient 0" << endl;
    fstd::deque<int> d{ 0, 1 };
    for (size_t i = 0; i < d.size(); i++) { cout << d[i] << ","; }
    cout << endl;
    break;
  }
  case 4: {
    cout << "single page, right overload quotient 0" << endl;
    fstd::deque<int> d{ 0 };
    for (size_t i = 0; i < d.size(); i++) { cout << d[i] << ","; }
    cout << endl;
    break;
  }

  default:
    break;
  }

  return 0;
}
