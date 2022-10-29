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

using namespace std;


int main()
{
  vector<int> vec{ 1, 3, 4, 6, 7, 8, 9 };// NOLINT magic number || search 8
  const int num{ 8 };
  const int mid{ (num + 1) / 2 };

  vector<bool> flags((num + 1) / 2, false);

  for (auto &elem : vec) {
    if (elem < num && elem > 0) {
      const int index = (elem >= mid) ? (num - elem) - 1 : elem - 1;
      if (flags[index]) {
        cout << "there exists" << endl;
        break;
      }
      flags[index] = true;
    }
  }


  return 0;
}
