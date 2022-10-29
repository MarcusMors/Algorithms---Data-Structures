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
#include <string>
#include <vector>

using namespace std;
template<class T> void print(T container)
{
  for (auto &&elem : container) { cout << elem << ", "; }
  cout << endl;
}

template<class T> void print(string prefix, T container)
{
  cout << prefix << endl;
  print(container);
}

template<class T> void insertion_sort(T A)
{
  for (size_t i = 1; i < A.size(); i++) {
    int key = A[i];
    int j = i;
    while (j >= 1 && key < A[j - 1]) {
      A[j] = A[j - 1];
      j--;
    }
    A[j] = key;
  }
}

struct Range
{
  int begin;
  int end;
  Range(int b, int e) : begin{ b }, end{ e } {}
};


template<class T> auto inverse_counter(vector<T> A)
{
  vector<Range> descendant_arrays;
  vector<Range> ascendant_arrays;

  int undefined_index{ 0 };
  // bool sequentiality = false;
  for (size_t i = 0; i < A.size(); i++) {
    int key = A[i];
    int j = i;
    while (j >= 1 && key < A[j - 1]) {
      A[j] = A[j - 1];
      j--;
    }
    A[j] = key;
  }
}


int main()
{
  vector<int> A{ 2, 3, 8, 6, 1 };// NOLINT magic number
  // vector<int> A{ 10, 8, 3, 4, 1 };// NOLINT magic number
  // vector<int> A{ 0, 2, 1 };// NOLINT magic number
  const int expected_value{ 6 };// NOLINT magic number

  int cont = inverse_counter(A);

  // print("before\t: ", A);
  // insertion_sort(A);
  // print("after\t: ", A);


  cout << "expected\tresult" << endl;
  cout << expected_value << "\t" << cont << endl;


  return 0;
}
