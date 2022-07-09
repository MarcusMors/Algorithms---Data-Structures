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
#include <string>
#include <vector>


using namespace std;

template<class T> std::istream &operator>>(std::istream &is, std::vector<T> &t_vector)
{
  std::vector<int>::size_type sz;// NOLINT initialization
  if (is >> sz) {
    // char comma;// NOLINT initialization
    t_vector.reserve(sz);

    if (char comma; is >> comma) {
      while (sz > 0) {
        T elem{ 0 };
        if (is >> elem) { t_vector.push_back(elem); }
        if (is >> comma) { ; }
        --sz;
      }

      return is;
    }
  }

  is.setstate(ios_base::failbit);
  return is;
}

template<class T> std::ostream &operator<<(std::ostream &os, std::vector<T> t_vector)
{
  for (auto &&elem : t_vector) { os << elem << ", "; }
  return os;
}

template<class int_type> std::string int_type_and_data_size(const unsigned t_data_size)
{
  const std::string var_size = std::to_string(sizeof(int_type));
  const std::string data_size = std::to_string(t_data_size);

  std::string output{ var_size + "b-" + data_size + "b" };
  return output;
}

int main()
{
  // std::string directory_path{ "/home/marcus/+projects/Algorithms-and-Data-Structures/data" };
  std::string directory_path{ "/home/marcus/+projects/Algorithms-and-Data-Structures/data" };
  std::string distribution{ "uniform_distribution" };
  std::string prefix{ "/GD_" + distribution + "__" };

  using int_type = int;
  const int data_size = 4;

  std::string var_size_and_data_size = int_type_and_data_size<int_type>(data_size);

  const std::string source{ directory_path + prefix + var_size_and_data_size + ".csv" };

  std::ifstream ifs{ source };

  if (!ifs) { std::cerr << ("couldn't open 'source' for reading\n"); }

  std::vector<int_type> vec;
  ifs >> vec;

  std::cout << "reading file\t: " << source << "\n ";
  std::cout << "The vec\t: ";
  std::cout << vec << endl;


  return 0;
}
