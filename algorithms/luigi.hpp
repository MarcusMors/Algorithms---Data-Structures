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

#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <time.h>
#include <vector>

using namespace std;

void merge_sort(int *array, long long const begin, long long const end)
{
  if (begin >= end) return;// Returns recursively
  long long mid = begin + (end - begin) / 2;
  merge_sort(array, begin, mid);
  merge_sort(array, mid + 1, end);
  merge(array, begin, mid, end);
}

// Merge WITH THREADS
void merge_sort_threads(int *array, long long const end, int threads)
{

  if (end + 1 < threads) {
    merge_sort(array, 0, end);
    return;
  }

  int i;
  long long block = (long long)(end + 1) / threads;

  vector<thread> ths(threads);

  for (i = 0; i < threads - 1; i++) ths[i] = thread(merge_sort, array, block * i, (block * (i + 1)) - 1);
  ths[i] = thread(merge_sort, array, block * i, end);

  int block_number = threads, indx;
  while (true) {
    for (i = 0; i < threads; i++) { ths[i].join(); }
    if (threads == 1 && block_number == 1) { break; }

    i = 0;
    threads = std::static_cast<int>(block_number / 2);
    for (indx = 0; indx < threads; i += 2, indx++) {
      if (i + 2 == block_number) {
        ths[indx] = thread(merge, array, block * i, (block * (i + 1)) - 1, end);
      } else {
        ths[indx] = thread(merge, array, block * i, (block * (i + 1)) - 1, block * (i + 2) - 1);
      }
    }

    block *= 2;
    block_number = ((int)block_number / 2) + (block_number % 2);
  }
  return;
}

// AUX FUNCTIONS
void fill_array(int *a, long long size)
{
  for (long long i = 0; i < size; i++) a[i] = rand();
}

void print_array(int *a, long long size)
{
  for (long long i = 0; i < size; i++) cout << a[i] << " ";
  cout << "\n";
}

int main()
{

  clock_t t;
  int numCPU = thread::hardware_concurrency();
  int max = 10000000;// 10 Milllones

  int *arr = new int[max];

  int test[60];
  string test_str[60];
  string aux;


  for (i = 0; i < 10; i++) {
    test[i] = (i + 1) * 10000;
    test_str[i] = to_string((int)test[i] / 1000) + "K";
  }

  for (i = 0; i < 50; i++) {
    test[i + 10] = (i + 1) * 200000;
    if (test[i + 10] < 1000000) {
      test_str[i + 10] = to_string((int)test[i + 10] / 1000) + " K";
    } else {
      aux = to_string((float)test[i + 10] / 100000);
      test_str[i + 10] = to_string((int)test[i + 10] / 1000000) + "." + aux[1] + " M";
    }
  }


  cout << "\n\nWITH THREADS:\n\n";
  for (int i = 0; i < 10; i++) {// Cambiar a 60
    cout << "\n\t" << test_str[i] << "\t|\t";
    fill_array(arr, test[i]);

    merge_sort_threads(arr, test[i] - 1, numCPU);
  }

  delete[] arr;

  return 0;
}
