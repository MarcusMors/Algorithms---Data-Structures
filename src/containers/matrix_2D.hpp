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

#include <array>
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
// Use (void) to silence unused warnings.
// #define assertm(exp, msg) assert(((void)msg, exp))

#include <initializer_list>
#include <iostream>


namespace fstd {

template<class T, std::size_t Rows, std::size_t Columns> struct matrix_2D
{
  using value_type = T;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = value_type *;
  using const_iterator = const value_type *;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  const static size_type columns = Columns;
  const static size_type rows = Rows;

  // No explicit construct/copy/destroy for aggregate type.

private:
  T m_root[rows][columns];

public:
  // matrix_2D(T (*t_matrix)[rows][columns]) { m_root }
  matrix_2D(std::array<std::array<T, Columns>, Rows> (*t_matrix)[rows][columns]) { m_root; }
  ~matrix_2D();
};

template<class T, std::size_t Rows, std::size_t Columns>
matrix_2D<T, Rows, Columns> operator*(matrix_2D<T, Rows, Columns> lhs, matrix_2D<T, Rows, Columns> rhs)
{
  matrix_2D<T, Rows, Columns> result;

  // return lhs;
}

// template<class T> matrix_2D<T> product_matrix_2D(matrix_2D<T>, matrix_2D<T>)
// {
//   matrix_2D<T> result;

//   return
// }

}// namespace fstd
