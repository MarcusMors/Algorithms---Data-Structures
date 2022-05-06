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

#include <initializer_list>
#include <iostream>

using namespace std;

namespace fstd {
// fixed sized array
template<typename T, size_t N> struct array
{
  using size_type = std::size_t;
  array(std::initializer_list<T> init) : sz{ init.size() }
  {
    for (size_t i = 0; i < init.size(); ++i) arr[i] = *(init.begin() + i);
  }
  size_t size() const { return sz; }
  T &back() const { return arr[sz - 1]; }
  T &operator[](const size_t &i) { return arr[i]; }
  T &operator[](const size_t &i) const { return arr[i]; }
  const T *begin() const { return arr; }
  const T *end() const { return arr + sz; }

private:
  const size_t sz = N;
  T arr[N];
};

template<typename T, size_t N> ostream &operator<<(std::ostream &os, const array<T, N> &t_arr)
{
  for (const auto &e : t_arr) os << e << ", ";
  return os;
}

// heap array
// template <typename T>
// struct h_array
// {
// 	using size_type = std::size_t;
// 	h_array(std::initializer_list<T> t_arr)
// 	{
// 		arr = new T[t_arr.size()];
// 		for (auto i = t_arr.begin(); i < t_arr.end(); ++i)
// 			arr[i] = *(t_arr.begin());
// 	}
// 	h_array(h_array<T> &t_arr)
// 	{
// 		if (t_arr.size() > sz)
// 		{
// 		}

// 		for ()
// 		{
// 		}
// 	}

// 	size_type size() const { return sz; }
// 	T &back() const { return arr[sz - 1]; }
// 	T &operator[](const size_t &i) { return arr[i]; }
// 	T &operator[](const size_t &i) const { return arr[i]; }
// 	T *begin() { return arr; }
// 	T *begin() const { return arr; }
// 	T *end() { return arr + sz; }
// 	T *end() const { return arr + sz; }

// private:
// 	size_t sz;
// 	T *arr;
// };

// template <typename T, size_t N>
// ostream &operator<<(std::ostream &os, const h_array<T, N> &t_arr)
// {
// 	for (const auto &e : t_arr)
// 		os << t_arr << ", ";
// 	return os;
// }

}// namespace fstd
