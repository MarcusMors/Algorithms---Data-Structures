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

#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <string>

template<typename T> T bit_number(unsigned t_bytes)
{
  // static_assert(sizeof(T) < t_bytes, "the type isn't able to hold that much t_bytes");
  // if (sizeof(T) * 4 < t_bytes) {
  //   std::cerr << "the type isn't able to hold " << t_bytes << "t_bytes\n";
  //   std::cerr << "sizeof(T)\t: " << sizeof(T) << "\n";
  //   std::cerr << "bytes\t\t: " << t_bytes << " \n";
  //   std::cerr << "bits\t\t: " << t_bytes * 4 << " \n";
  //   return 0;
  // }
  T output{ 1 };
  for (unsigned i = 0; i <= t_bytes; i++) { output <<= 1; }

  return output;
}

int main()
{
  using Seed = std::random_device;
  using Engine = std::default_random_engine;
  // supported int Types // check https://en.cppreference.com/w/cpp/header/random
  // short, int, long, long long,
  // unsigned short, unsigned int, unsigned long, or unsigned long long
  using int_type = int;
  using Distribution = std::uniform_int_distribution<int_type>;

  Seed seed;
  Engine engine{ seed() };
  const int_type max = std::numeric_limits<int_type>::max();
  const int_type min = std::numeric_limits<int_type>::min();
  Distribution distribution(min, max);
  auto generate_random_number = [&]() { return distribution(engine); };

  using it_type = unsigned long long;
  const unsigned bytes = 16;
  const it_type data_size = bit_number<it_type>(bytes);
  // const it_type data_size = std::numeric_limits<it_type>::max();

  if (data_size == 0) {
    std::cerr << "error, data_size_type can't hold that many  numbers\n";
    return 1;
  }


  std::ofstream out;
  // const std::string file_name = "GD_uniform_distribution__" + to_str(sizeof(int_type)) + '-' + to_str(data_size) +
  // ".csv";
  const std::string file_name =
    "GD_uniform_distribution__" + std::to_string(sizeof(int_type)) + "b-" + std::to_string(bytes) + "b.csv";


  out.open(file_name);
  out << data_size << ",";
  for (it_type i = 0; i < data_size; i++) { out << generate_random_number() << ','; }
  out.close();

  return 0;
}
