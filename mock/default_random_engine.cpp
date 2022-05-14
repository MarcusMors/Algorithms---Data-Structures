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
#include <random>
#include <limits>

int main()
{
	using Seed = std::random_device;
	using Engine = std::default_random_engine;
	// supported int Types // check https://en.cppreference.com/w/cpp/header/random
	// short, int, long, long long,
	// unsigned short, unsigned int, unsigned long, or unsigned long long
	using intType = long;
	using Distribution = std::uniform_int_distribution<intType>;

	Seed seed;
	Engine engine{seed()};
	const intType max = std::numeric_limits<intType>::max();
	const intType min = std::numeric_limits<intType>::min();
	Distribution distribution(min, max);

	return 0;
}
