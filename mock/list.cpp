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
#include <list>

using namespace std;

int main()
{
  list<int> list{ 0, 1, 2, 3, 4, 5 };// NOLINT magic number
  for (auto &&elem : list) { cout << elem << ','; }
  cout << endl;

  cout << "*(list.begin()) : " << *(list.begin()) << endl;
  cout << "*(list.end()) : " << *(list.end()) << endl;


  return 0;
}
