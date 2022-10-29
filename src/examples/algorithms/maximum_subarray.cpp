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
#include <limits>
#include <vector>

using namespace std;

namespace fstd {
template<class T> using iterator = typename vector<T>::iterator;
template<class T> std::ostream &operator<<(std::ostream &os, std::vector<T> t_vector);

template<class T> void brute_force(vector<T> A);

template<class T> struct Range
{
  using iterator = typename vector<T>::iterator;
  iterator low;
  iterator high;
  T max_sum;

  Range(iterator t_l, iterator t_h, T t_max_sum) : low{ t_l }, high{ t_h }, max_sum{ t_max_sum } {}
};

// the highest or points to the higher, to it is at the left of the lowest.
// el máximo o apunta al mayor o está a la izquierda del mínimo/menor.
// el mínimo o apunta al menor o está a la derecha del máximo/mayor.

template<class T> Range<T> cross_recall(iterator<T> t_low, iterator<T> t_mid, iterator<T> t_high)
{
  T sum = 0;
  iterator<T> low;
  iterator<T> high;

  T left_max = std::numeric_limits<T>::min();

  for (auto it = t_mid - 1; it != t_low - 1; it--) {
    if (sum > left_max) {
      left_max = sum;
      low = it;
    }
  }

  sum = 0;
  T right_max = std::numeric_limits<T>::min();
  for (auto it = t_mid; it != t_high + 1; it++) {
    if (sum > right_max) {
      right_max = sum;
      high = it;
    }
  }
  return Range{ low, high, left_max + right_max };
}

template<class T> Range<T> recall(iterator<T> t_begin, iterator<T> t_end)
{
  const size_t size = t_end - t_begin;
  switch (size) {
  case 0:
    return Range<T>{ t_begin, t_begin, *t_begin };
    break;
    // case 1:
    //   // t_begin > t_end
    //   if (*t_begin < *t_end) {
    //     // pick t_end
    //   }

    //   return Range<T>{ t_begin, t_end, *t_begin + *t_end };
    //   break;

  default:
    auto mid = t_begin + ((t_end - t_begin) / 2);
    Range<T> left = recall<T>(t_begin, mid);
    Range<T> right = recall<T>(mid + 1, t_end);
    Range<T> cross = cross_recall<T>(t_begin, mid, t_end);

    if (left.max_sum >= right.max_sum && left.max_sum >= cross.max_sum) {
      return left;
    } else if (right.max_sum >= left.max_sum && right.max_sum >= cross.max_sum) {
      return right;
    }
    return cross;

    break;
  }
}

template<class T> void recursive(vector<T> A)
{
  std::cout << "RECURSIVE" << std::endl;
  Range<T> answer = recall<T>(A.begin(), (A.end() - 1));//[begin,end)
  std::cout << "low\t: " << *answer.low << std::endl;
  std::cout << "high\t: " << *answer.high << std::endl;
}

}// namespace fstd


int main()
{
  using fstd::operator<<;
  // std::vector<int> A{ 1, -4, 3, -4 };
  std::vector<int> A{ 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
  std::cout << "input\t: " << A << std::endl;

  fstd::brute_force(A);
  fstd::recursive(A);

  return 0;
}


//
//
//
//


template<class T> std::ostream &fstd::operator<<(std::ostream &os, std::vector<T> t_vector)
{
  for (auto &&elem : t_vector) { os << elem << ", "; }
  return os;
}

template<class T> void fstd::brute_force(vector<T> A)
{
  using iterator = iterator<T>;
  cout << "BRUTE FORCE" << endl;

  iterator low;
  iterator high;
  T max_sum = std::numeric_limits<T>::min();

  for (auto it = A.begin(); it != A.end(); it++) {
    T sum = 0;
    for (auto jt = it; jt != A.end(); jt++) {
      sum += *jt;
      if (sum > max_sum) {
        low = it;
        max_sum = sum;
        high = jt;
      }
    }
  }

  std::cout << "*low\t: " << *low << std::endl;
  std::cout << "*high\t: " << *high << std::endl;
}
