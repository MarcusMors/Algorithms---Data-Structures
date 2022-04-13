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
	fstd::list<int> list{1, 2, 3, 4, 5};
	std::cout << "size\t: " << list.size() << '\n';
	node<int> *ptr = list.begin();
	cout << "ptr : " << ptr->value << endl;
	++ptr;
	// ptr = ptr->next;
	cout << "ptr : " << ptr->value << endl;

	// std::cout << "list\t: " << list << std::endl;
	// std::cout << "list[0] : " << list[0] << '\n';
	// std::cout << "list[1] : " << list[1] << '\n';
	// std::cout << "list[2] : " << list[2] << '\n';

	return 0;
}
