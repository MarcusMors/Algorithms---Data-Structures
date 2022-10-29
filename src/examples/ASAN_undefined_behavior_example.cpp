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
#include <string>
#include <vector>

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
  if (argc != 2) {
    std::cout << "Usage: main_address_sanitize <choice>" << std::endl;
    return -1;
  }

  int choice = std::stoi(argv[1]);
  std::cout << "choice: " << choice << std::endl;

  switch (choice) {
  case 0: {
    int k = 0x7fffffff;
    k += 100;// undefined behavior
    std::cout << "k: " << k << std::endl;
    break;
  }
  case 1: {
    int x = 1;
    return x / (x - 1);// undefined behavior
  }

  case 2: {
    int x = 10;
    int arr[4] = { 0, 1, 2, 3 };
    int a = arr[x];// undefined behavior for indexing out of bounds
    std::cout << "a: " << a << std::endl;
    break;
  }

  case 3: {
    int *p = 0;
    int a = *p;// undefined behavior for dereferencing a null pointer
    std::cout << "a: " << a << std::endl;
    break;
  }

  case 4: {
    int num = -1;
    unsigned int val = 1 << num;// shifting by a negative number - undefined behavior
    std::cout << "val: " << val << std::endl;
    break;
  }

  case 5: {
    int num = 32;// or whatever number greater than 31
    int val = 1 << num;// the literal '1' is typed as a 32-bit integer - in this
                       // case shifting by more than 31 bits is undefined behavior

    std::cout << "val: " << val << std::endl;
    break;
  }

  // Can't be detected by udef sanitizer :(
  case 20: {
    int a = 0;
    int b = 0;
    return &a < &b;// undefined behavior
  }

  // Can't be detected by udef sanitizer :(
  case 21: {
    int arr[4] = { 0, 1, 2, 3 };
    int i = 0;
    arr[i] = i++;// undefined behavior
  }

  default:
    std::cout << "Error: Invalid choice value: " << choice << std::endl;
  }
}
