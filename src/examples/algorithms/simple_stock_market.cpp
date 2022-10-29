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

template<class T> std::ostream &operator<<(std::ostream &os, std::vector<T> t_vector)
{
  for (auto &&elem : t_vector) { os << elem << ", "; }
  return os;
}

template<class T> void brute_force(vector<T> A)
{
  cout << "BRUTE FORCE" << endl;

  int diff = 0;
  size_t invest_index = 0;
  size_t sell_index = 0;

  for (size_t i = 0; i < A.size() - 1; i++) {
    int max = std::numeric_limits<int>::min();
    size_t max_index = i;
    for (size_t j = i + 1; j < A.size(); j++) {
      if (A[j] > max) {
        max = A[j];
        max_index = j;
      }
    }
    const int new_diff = max - A[i];
    if (new_diff > diff) {
      diff = new_diff;
      invest_index = i;
      sell_index = max_index;
    }
  }
  cout << "invest\t: " << A[invest_index] << endl;
  cout << "sell\t: " << A[sell_index] << endl;
}

template<class T> struct Difference_index
{
  using iterator = typename vector<T>::iterator;
  Difference_index(iterator l, iterator h) : lower{ l }, higher{ h } {}
  iterator lower;
  iterator higher;
};

template<class T> struct Range
{
  using iterator = typename vector<T>::iterator;
  Difference_index<T> difference;
  iterator total_lowest;
  iterator total_highest;

  Range(Difference_index<T> t_d, iterator t_l, iterator t_h)
    : difference{ t_d }, total_lowest{ t_l }, total_highest{ t_h }
  {}
  void join_right_range(Range right)
  {
    if (*difference.higher <= *right.total_highest) { difference.higher = right.total_highest; }
    if (*total_lowest < *right.difference.lower) { right.difference.lower = total_lowest; }

    update_difference(right);
    update_totals(right);
  }

private:
  void update_totals(Range<T> right)
  {
    if (*total_highest <= *right.total_highest) { total_highest = right.total_highest; }
    if (*total_lowest > *right.total_lowest) { total_lowest = right.total_lowest; }
  }

  void update_difference(Range<T> right)
  {
    const int total_diff = *right.total_highest - *total_lowest;
    const int left_diff = *difference.higher - *difference.lower;
    const int right_diff = *right.difference.higher - *right.difference.lower;

    if (left_diff < right_diff) {
      if (right_diff < total_diff) {
        difference.higher = right.total_highest;
        difference.lower = total_lowest;
      } else {
        difference = right.difference;
      }
    } else if (left_diff < total_diff) {
      difference.higher = right.total_highest;
      difference.lower = total_lowest;
    }
  }
};

// the highest or points to the higher, to it is at the left of the lowest.
// el máximo o apunta al mayor o está a la izquierda del mínimo/menor.
// el mínimo o apunta al menor o está a la derecha del máximo/mayor.

// template<class T>
// Range<T>
//   cross(typename vector<T>::iterator t_low, typename vector<T>::iterator t_mid, typename vector<T>::iterator t_high)
// {
//   T left_max = std::numeric_limits<T>::min();

//   for (auto it = t_mid - 1; it != t_low+ 1; it--) {
//     //
//   }

//   T right_max = std::numeric_limits<T>::min();
//   for (auto it = t_mid; it != t_high+1; it++)
//   {
//     if (m)
//     {
//       /* code */
//     }

//   }

// }

template<class T> Range<T> recall(typename vector<T>::iterator t_begin, typename vector<T>::iterator t_end)
{
  using iterator = typename vector<T>::iterator;
  const size_t size = t_end - t_begin;
  switch (size) {
  case 0:
    return Range<T>{ Difference_index<T>{ t_begin, t_begin }, t_begin, t_begin };
    break;
  case 1:
    if (*t_begin <= *t_end) { return Range<T>{ Difference_index<T>{ t_begin, t_end }, t_begin, t_end }; }
    return Range<T>{ Difference_index<T>{ t_begin, t_begin }, t_end, t_begin };
    break;

  default:
    iterator mid = t_begin + ((t_end - t_begin) / 2);
    Range<T> left = recall<T>(t_begin, mid);
    Range<T> right = recall<T>(mid + 1, t_end);
    left.join_right_range(right);
    return left;

    break;
  }
}

template<class T> void recursive(vector<T> A)
{
  cout << "RECURSIVE" << endl;
  Range<T> answer = recall<T>(A.begin(), (A.end() - 1));
  cout << "invest\t: " << *answer.difference.lower << endl;
  cout << "sell\t: " << *answer.difference.higher << endl;
}

int main()
{

  // vector<int> A{ 10, 11, 7, 10 };
  // vector<int> A{ 10, 11, 7, 10, 6, 8 };
  vector<int> A{ 100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 94, 90, 97 };
  cout << "input\t: " << A << endl;
  brute_force(A);
  recursive(A);

  return 0;
}
